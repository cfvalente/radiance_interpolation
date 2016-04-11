#ifndef PROJCG_GAUSSIANBACKWARDINTERPOLATOR_H_
#define PROJCG_GAUSSIANBACKWARDINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"
#include "hdrimage.h"

class GaussianBackwardInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	GaussianBackwardInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);

private:
};

#endif