#ifndef PROJCG_STIRLINGINTERPOLATOR_H_
#define PROJCG_STIRLINGINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"
#include "hdrimage.h"

class StirlingInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	StirlingInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);

private:
	HdrImage calculateForwardInterpolationOn(float observation);
	HdrImage calculateBackwardInterpolationOn(float observation);
};

#endif