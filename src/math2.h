#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <iostream>
#include <vector>
#include "hdrimage.h"

void solveTriDiagonalSystem(int imgWidth, int imgHeight, std::vector<float> m, std::vector<float> h, std::vector<HdrImage> &dy2, std::vector<HdrImage> p);
double quadraticRootBetween0And1(double a, double b, double c);
double cubicRootBetween0And1(double a,double b,double c, double d);
double curt(double x);

#endif