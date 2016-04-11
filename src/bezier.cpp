#include <cmath>
#include <iostream>

#include "bezier.h"

BezierApproximator::BezierApproximator(const std::vector<int> &observations, const std::vector<HdrImage> &values) :
	Interpolator(observations, values){}

HdrImage lerp(HdrImage a, HdrImage b, double t)
{
	return a+(b-a)*t;
}

HdrImage BezierApproximator::calculateInterpolationOn(float t) {
	int count = values_.size();
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage approximation(width, height);
	std::vector<std::vector<HdrImage>> tempValues;

	for (int i = 0; i < count - 1; i++)
	{
		std::vector<HdrImage> temp;
		tempValues.push_back(temp);
	}
	for (int j = 0; j < count - 1; j++)
	{
		tempValues[0].push_back(lerp(values_[j], values_[j + 1], t));
	}
	for (int i = 1; i < count - 1; i++)
	{
		for (int j = 0; j < count - 1 - i; j++)
		{
			tempValues[i].push_back(lerp(tempValues[i - 1][j], tempValues[i - 1][j + 1], t));
		}
	}
	approximation = tempValues[count - 2][0];

	return approximation;
}

HdrImage BezierApproximator::calculateContinuousInterpolationOn(float t) {
	int count = values_.size();
	int width = values_[0].getWidth();
	int height = values_[0].getHeight();
	HdrImage approximation(width, height);
	if ((t >= observations_.front()) && (t <= observations_.back()))
	{
		std::vector<std::vector<HdrImage>> tempValues;
		t = (t - observations_[0]) / (observations_[count - 1] - observations_[0]);
		for (int i = 0; i < count - 1; i++)
		{
			std::vector<HdrImage> temp;
			tempValues.push_back(temp);
		}
		for (int j = 0; j < count - 1; j++)
		{
			tempValues[0].push_back(lerp(values_[j], values_[j + 1], t));
		}
		for (int i = 1; i < count - 1; i++)
		{
			for (int j = 0; j < count - 1 - i; j++)
			{
				tempValues[i].push_back(lerp(tempValues[i - 1][j], tempValues[i - 1][j + 1], t));
			}
		}
		approximation = tempValues[count - 2][0];
	}
	return approximation;
}