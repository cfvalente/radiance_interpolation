#include <cmath>
#include <iostream>

#include "lagrangeinterpolator.h"

LaGrangeInterpolator::LaGrangeInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage LaGrangeInterpolator::calculateInterpolationOn(float observation) {
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage interpolation(width, height);
	unsigned int step = 0;
	if ((observation >= observations_.front()) && (observation <= observations_.back())) 
	{
		for (unsigned int i = 0; i < observations_.size(); i++, step++) {
			int currentX = observations_[step];
			double numerator = 1.0, denominator = 1.0;
			for (unsigned int j = 0; j < observations_.size(); j++) {
				if (j == step) continue;
				numerator *= (observation - observations_[j]);
				denominator *= (currentX - observations_[j]);
			}
			interpolation = interpolation + values_[step] * float((numerator / denominator));
		}
		interpolation = interpolation.clamp();
	}
	return interpolation;
}