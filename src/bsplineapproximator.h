#ifndef PROJCG_BSPLINEAPPROXIMATOR_H_
#define PROJCG_BSPLINEAPPROXIMATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class BSplineApproximator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	BSplineApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif