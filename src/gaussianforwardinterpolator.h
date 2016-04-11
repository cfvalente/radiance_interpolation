#ifndef PROJCG_GAUSSIANFORWARDINTERPOLATOR_H_
#define PROJCG_GAUSSIANFORWARDINTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "interpolator.h"
#include "hdrimage.h"

class GaussianForwardInterpolator : public Interpolator {
using Interpolator::Interpolator;
public:
	HdrImage calculateInterpolationOn(float observation);
	GaussianForwardInterpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values);

private:
};

#endif