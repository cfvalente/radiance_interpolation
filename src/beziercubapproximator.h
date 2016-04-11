#ifndef BEZIER_CUBIC_APPROXIMATOR_H
#define BEZIER_CUBIC_APPROXIMATOR_H

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class BezierCubicApproximator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	BezierCubicApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif