#ifndef PROJCG_QUADRATICINTERPOLATOR_H_
#define PROJCG_QUADRATICINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"

class QuadraticInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	QuadraticInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);
};

#endif