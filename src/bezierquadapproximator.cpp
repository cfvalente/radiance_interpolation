#include <cmath>
#include <iostream>

#include "bezier.h"
#include "bezierquadapproximator.h"
#include "math2.h"
#include "define.h"

BezierQuadraticApproximator::BezierQuadraticApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}



HdrImage BezierQuadraticApproximator::calculateInterpolationOn(float observation) {
	int count = 0;
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	std::vector<int> bezierObservations;
	std::vector<HdrImage> bezierValues;
	HdrImage approximation(width, height);
	
	double t = 0;

	if ((observation >= observations_.front()) && (observation <= observations_.back()) && (observations_.size() >= 3)) 
	{
		if (observations_[0] == observation) return values_[0];
		if (observations_[observations_.size() - 1] == observation) return values_[observations_.size() - 1];

		bool end = false;
		while (!end)
		{
			if (count + 2 < observations_.size())
			{
				if (observation < observations_[count + 2])
				{
					bezierObservations.push_back(observations_[count]);
					bezierObservations.push_back(observations_[count + 1]);
					bezierObservations.push_back(observations_[count + 2]);
					bezierValues.push_back(values_[count]);
					bezierValues.push_back(values_[count + 1]);
					bezierValues.push_back(values_[count + 2]);
					end = true;
					double a = bezierObservations[0] - 2 * bezierObservations[1] + bezierObservations[2];
					double b = -2 * bezierObservations[0] + 2 * bezierObservations[1];
					double c = bezierObservations[0] - observation;
					if (fabs(a) > Epsilon)
					{
						t = quadraticRootBetween0And1(a, b, c);
					}
					else t = (observation - bezierObservations[0]) / (bezierObservations[2] - bezierObservations[0]);
				}
				else count += 2;
			}
			else if (count + 1 < observations_.size())
			{
				bezierObservations.push_back(observations_[count]);
				bezierObservations.push_back(observations_[count + 1]);
				bezierValues.push_back(values_[count]);
				bezierValues.push_back(values_[count + 1]);
				end = true;
				t = (observation - bezierObservations[0]) / (bezierObservations[1] - bezierObservations[0]);
			}
		}
		BezierApproximator bez(bezierObservations, bezierValues);
		approximation = bez.calculateInterpolationOn(t);

		
	}
	return approximation;
}