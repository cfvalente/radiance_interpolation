#ifndef BEZIER_QUADRATIC_APPROXIMATOR_H
#define BEZIER_QUADRATIC_APPROXIMATOR_H

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class BezierQuadraticApproximator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	BezierQuadraticApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif