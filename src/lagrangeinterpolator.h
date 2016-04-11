#ifndef PROJCG_LAGRANGEINTERPOLATOR_H_
#define PROJCG_LAGRANGEINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class LaGrangeInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	LaGrangeInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif