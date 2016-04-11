#include <cmath>
#include <iostream>

#include "bsplineapproximator.h"
#include "math2.h"
#include "define.h"

BSplineApproximator::BSplineApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

double B0(double t)
{
	return (1.0-t)*(1.0-t)*(1.0-t)/6.0;
}

double B1(double t)
{
	return (4.0-6.0*t*t+3.0*t*t*t)/6.0;
}

double B2(double t)
{
	return (1.0+3.0*t+3.0*t*t-3.0*t*t*t)/6.0;
}

double B3(double t)
{
	return t*t*t/6.0;
}

double BSpline(double t, double p0, double p1, double p2, double p3)
{
	return p0*B0(t)+p1*B1(t)+p2*B2(t)+p3*B3(t);
}

HdrImage BSpline(double t, HdrImage p0, HdrImage p1, HdrImage p2, HdrImage p3)
{
	return p0*B0(t)+p1*B1(t)+p2*B2(t)+p3*B3(t);
}

HdrImage BSplineApproximator::calculateInterpolationOn(float observation) {
	double t;
	int count = 0;
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage approximation(width, height);
	std::vector<float> newObservations;
	std::vector<HdrImage> newValues;
	if ((observation >= observations_.front()) && (observation <= observations_.back()) && observations_.size() >= 2) {
		
		if (observation == observations_[0])
		{
			approximation = values_[0];
			return approximation;
		}
		if (observation == observations_[observations_.size() - 1])
		{
			approximation = values_[observations_.size() - 1];
			return approximation;
		}

		newValues.push_back(values_[0]);
		newValues.push_back(values_[0]);
		newObservations.push_back(observations_[0]);
		newObservations.push_back(observations_[0]);
		for(int i = 0; i < observations_.size(); i++)
		{
			newValues.push_back(values_[i]);
			newObservations.push_back(observations_[i]);
		}
		newValues.push_back(values_[observations_.size()-1]);
		newValues.push_back(values_[observations_.size()-1]);
		newObservations.push_back(observations_[observations_.size()-1]);
		newObservations.push_back(observations_[observations_.size()-1]);

		int j = -1;
		double tip;
		do
		{
			j++;
			tip = BSpline(1.0, newObservations[j],newObservations[j+1],newObservations[j+2],newObservations[j+3]);
		} while(observation > tip );


		double a,b,c,d;
		a = (-newObservations[j]+3.0*newObservations[j+1]-3.0*newObservations[j+2]+newObservations[j+3])/6.0;
		b = (3.0*newObservations[j]-6.0*newObservations[j+1]+3.0*newObservations[j+2])/6.0;
		c = (-3.0*newObservations[j]+3.0*newObservations[j+2])/6.0;
		d = ((newObservations[j]+4.0*newObservations[j+1]+newObservations[j+2])/6.0)-observation;
		if(fabs(a) < Epsilon)
		{
			if(fabs(b) < Epsilon)
			{
				t = -d/c;
			}
			else std::cout << "Wtf bbq\n";
		}
		else t = cubicRootBetween0And1(a,b,c,d);


		approximation = BSpline(t, newValues[j], newValues[j+1], newValues[j+2], newValues[j+3]);

	}
	
	return approximation;
}