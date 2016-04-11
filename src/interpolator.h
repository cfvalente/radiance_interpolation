#ifndef PROJCG_INTERPOLATOR_H_
#define PROJCG_INTERPOLATOR_H_

#include <vector>
#include <FreeImage.h>
#include "hdrimage.h"

class Interpolator {
public:
	Interpolator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
		observations_(observations),
		values_(values) {}
	virtual HdrImage calculateInterpolationOn(float observation) = 0;
protected:
	std::vector<int> observations_;
	std::vector<HdrImage> values_;
};

#endif