#include <cmath>
#include <iostream>

#include "bezier.h"
#include "beziercubapproximator.h"
#include "bezierquadapproximator.h"
#include "define.h"
#include "math2.h"

BezierCubicApproximator::BezierCubicApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}



HdrImage BezierCubicApproximator::calculateInterpolationOn(float observation) {
	int count = 0;
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	std::vector<int> bezierObservations;
	std::vector<HdrImage> bezierValues;
	HdrImage approximation(width, height);
	
	double t = 0;

	if ((observation >= observations_.front()) && (observation <= observations_.back()) && (observations_.size() >= 4)) {
		if (observations_[0] == observation) return values_[0];
		if (observations_[observations_.size()-1] == observation) return values_[observations_.size()-1];
		
		bool end = false;
		while(!end)
		{
			if(count+3 < observations_.size())
			{
				if(observation < observations_[count+3])
				{
					bezierObservations.push_back(observations_[count]);
					bezierObservations.push_back(observations_[count+1]);
					bezierObservations.push_back(observations_[count+2]);
					bezierObservations.push_back(observations_[count+3]);
					bezierValues.push_back(values_[count]);
					bezierValues.push_back(values_[count+1]);
					bezierValues.push_back(values_[count+2]);
					bezierValues.push_back(values_[count+3]);

					if (observation == bezierObservations[0])
					{
						approximation = bezierValues[0];
						return approximation;
					}
					if (observation == bezierObservations[3])
					{
						approximation = bezierValues[3];
						return approximation;
					}

					end = true;
					double a = -bezierObservations[0]+3*bezierObservations[1]-3*bezierObservations[2]+bezierObservations[3]; 
					double b = 3*bezierObservations[0]-6*bezierObservations[1]+3*bezierObservations[2];
					double c = -3*bezierObservations[0]+3*bezierObservations[1];
					double d = bezierObservations[0]-observation;
					if(fabs(a) > Epsilon)
					{
						t = cubicRootBetween0And1(a,b,c,d);
					}
					else t = (observation-bezierObservations[0])/(bezierObservations[3]-bezierObservations[0]);
					BezierApproximator bez(bezierObservations, bezierValues);
					approximation = bez.calculateInterpolationOn(t);
				}
				else count+=3;
			}
			else
			{
				for(;count < observations_.size(); count++)
				{
					bezierObservations.push_back(observations_[count]);
					bezierValues.push_back(values_[count]);
				}
				approximation = BezierQuadraticApproximator(bezierObservations,bezierValues).calculateInterpolationOn(observation);
				end = true;
			}
		}
	}

	return approximation;
}