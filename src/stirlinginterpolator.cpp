#include <cmath>
#include <iostream>
#include "stirlinginterpolator.h"
#include "gaussianbackwardinterpolator.h"
#include "gaussianforwardinterpolator.h"
#include "minmax.h"


StirlingInterpolator::StirlingInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage StirlingInterpolator::calculateInterpolationOn(float observation) {
	int numberOfObservations = observations_.size();
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage interpolation(width, height);
	if ((observation >= observations_.front()) && (observation <= observations_.back()))
	{
		HdrImage gf(width, height);
		HdrImage gb(width, height);
		GaussianForwardInterpolator gfi(observations_, values_);
		GaussianBackwardInterpolator gbi(observations_, values_);
		gf = gfi.calculateInterpolationOn(observation);
		gb = gbi.calculateInterpolationOn(observation);
		interpolation = gf*0.5 + gb*0.5;
		interpolation = interpolation.clamp();
	}
	return interpolation;
}