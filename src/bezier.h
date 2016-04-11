#ifndef BEZIER_H_
#define BEZIER_H_

#include <vector>
#include <FreeImage.h>

#include "interpolator.h"

class BezierApproximator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	HdrImage calculateContinuousInterpolationOn(float observation);
	BezierApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif