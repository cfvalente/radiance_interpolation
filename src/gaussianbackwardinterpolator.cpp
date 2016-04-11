#include <cmath>
#include <iostream>
#include "gaussianbackwardinterpolator.h"
#include "minmax.h"

GaussianBackwardInterpolator::GaussianBackwardInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage GaussianBackwardInterpolator::calculateInterpolationOn(float observation) {
	int interval_ = observations_[1]-observations_[0];

	int numberOfObservations = observations_.size();
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage interpolation(width, height);
	if ((observation >= observations_.front()) && (observation <= observations_.back()))
	{
		if (observation == observations_[0])
		{
			interpolation = values_[0];
			return interpolation;
		}
		if (observation == observations_[numberOfObservations - 1])
		{
			interpolation = values_[numberOfObservations - 1];
			return interpolation;
		}
		int x0 = 0;
		int xpos = numberOfObservations;
		int xneg = -1;
		for (int i = 0; (i < numberOfObservations && observations_[i] <= observation); i++)
		{
			x0 = i;
			xpos--;
			xneg++;
		}
		x0 = x0 + 1;
		xpos--;
		xneg++;

		double p = (observation - observations_[x0]) / (1.0*interval_);

		if (xpos > xneg) xpos = xneg;
		if (xneg > xpos) xneg = xpos + 1;

		std::vector<std::vector<HdrImage>> dy;
		for (int i = 0; i < xpos + xneg + 1; i++)
		{
			std::vector<HdrImage> v;
			dy.push_back(v);
			for (int j = 0; j < xpos + xneg + 1 - i; j++)
			{
				dy[i].push_back(HdrImage(width, height));
				if (i == 0)	dy[i][j] = values_[x0 - xneg + j];
				else dy[i][j] = dy[i - 1][j + 1] - dy[i - 1][j];
			}
		}
		int denominator = 1;
		double numerator = p;
		int sign = -1;
		int counter = 0;
		interpolation = values_[x0];
		for (int i = 1; i < xpos + xneg + 1; i++)
		{
			denominator = denominator*i;
			interpolation = interpolation + (dy[i][(int)abs(floor((2 * xneg - i) / 2.0))] * (numerator / denominator));
			sign = -sign;
			if (sign == 1) counter++;
			numerator = numerator*(p + sign*counter);
		}
		interpolation = interpolation.clamp();
	}
	return interpolation;
}