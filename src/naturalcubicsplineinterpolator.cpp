#include <cmath>
#include <iostream>
#include <omp.h>
#include "naturalcubicsplineinterpolator.h"
#include "minmax.h"
#include "math2.h"


NaturalCubicSplineInterpolator::NaturalCubicSplineInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}




HdrImage NaturalCubicSplineInterpolator::calculateInterpolationOn(float observation) {
	int numberOfObservations = observations_.size();
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage interpolation(width, height);

	std::vector<HdrImage> k, p, dy2;
	std::vector<float> h,m; 
	if ((observation >= observations_.front()) && (observation <= observations_.back())) 
	{

		for (int i = 0; i < numberOfObservations - 1; i++)
		{
			HdrImage tempImg(width, height);
			tempImg = values_[i + 1] - values_[i];

			h.push_back(observations_[i + 1] - observations_[i]);
			k.push_back(tempImg);
		}

		for (int i = 0; i < numberOfObservations - 2; i++)
		{
			HdrImage tempImg(width, height);
			tempImg = ((k[i + 1] / h[i + 1]) - (k[i] / h[i]))*6.0f;

			m.push_back(2.0*(h[i] + h[i + 1]));
			p.push_back(tempImg);
		}


		solveTriDiagonalSystem(width, height, m, h, dy2, p);

		int count = 0;
		if ((observation >= observations_.front()) && (observation <= observations_.back()) && (observations_.size() >= 4))
		{
			while (observation > observations_[count + 1]) count++;
		}


		float temp = (observations_[count + 1] - observation)*(observations_[count + 1] - observation)*(observations_[count + 1] - observation) / (6.0*h[count]);
		interpolation = dy2[count] * temp;

		temp = (observation - observations_[count])*(observation - observations_[count])*(observation - observations_[count]) / (6.0*h[count]);
		interpolation = interpolation + dy2[count + 1] * temp;

		temp = (observations_[count + 1] - observation);
		interpolation = interpolation + ((values_[count] / h[count]) - (dy2[count] * h[count]) / 6.0)*temp;

		temp = (observation - observations_[count]);
		interpolation = interpolation + ((values_[count + 1] / h[count]) - (dy2[count + 1] * h[count]) / 6.0)*temp;


		interpolation = interpolation.clamp();
	}

	return interpolation;
}