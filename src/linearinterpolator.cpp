#include <cmath>
#include <iostream>

#include "linearinterpolator.h"

LinearInterpolator::LinearInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage LinearInterpolator::calculateInterpolationOn(float observation) {
	int count = 0;
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage interpolation(width, height);
	if ((observation >= observations_.front()) && (observation <= observations_.back())) 
	{
		while (observations_[count] < observation) count++;
		if (observations_.front() == observation) return values_.front();
		if (observations_.back() == observation) return values_.back();
		float denominator = 1.0*(observation-observations_[count-1])/(observations_[count]-observations_[count-1]);

		interpolation = values_[count-1]+(values_[count] - values_[count-1])*denominator;
	}
	return interpolation;
}