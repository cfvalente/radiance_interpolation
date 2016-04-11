#ifndef PROJCG_LINEARINTERPOLATOR_H_
#define PROJCG_LINEARINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class LinearInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	LinearInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif