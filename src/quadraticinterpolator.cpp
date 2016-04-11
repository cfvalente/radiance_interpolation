#include <cmath>
#include <iostream>

#include "quadraticinterpolator.h"
#include "lagrangeinterpolator.h"

QuadraticInterpolator::QuadraticInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage QuadraticInterpolator::calculateInterpolationOn(float observation) {
	int count = 0;
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	std::vector<int> quadraticObservations;
	std::vector<HdrImage> quadraticValues;
	HdrImage interpolation(width, height);
	if ((observation >= observations_.front()) && (observation <= observations_.back()) && (observations_.size() >= 3)) {
		if (observations_[0] == observation) return values_[0];
		if (observations_[observations_.size()-1] == observation) return values_[observations_.size()-1];
		
		bool end = false;
		while(!end)
		{
			if(count+2 < observations_.size())
			{
				if(observation < observations_[count+2])
				{
					quadraticObservations.push_back(observations_[count]);
					quadraticObservations.push_back(observations_[count+1]);
					quadraticObservations.push_back(observations_[count+2]);
					quadraticValues.push_back(values_[count]);
					quadraticValues.push_back(values_[count+1]);
					quadraticValues.push_back(values_[count+2]);
					end = true;
				}
				else count+=2;
			}
			else if(count+1 < observations_.size())
			{
				quadraticObservations.push_back(observations_[count-1]);
				quadraticObservations.push_back(observations_[count]);
				quadraticObservations.push_back(observations_[count+1]);
				quadraticValues.push_back(values_[count-1]);
				quadraticValues.push_back(values_[count]);
				quadraticValues.push_back(values_[count+1]);
				end = true;
			}
		}

		LaGrangeInterpolator la(quadraticObservations, quadraticValues);

		interpolation = la.calculateInterpolationOn(observation);
	}


	interpolation = interpolation.clamp();
	return interpolation;
}