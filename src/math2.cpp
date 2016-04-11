#include <cmath>
#include <iostream>

#include <complex>
#include "math2.h"
#include "define.h"

using namespace std;

void solveTriDiagonalSystem(int imgWidth, int imgHeight, std::vector<float> m, std::vector<float> h, std::vector<HdrImage> &dy2, std::vector<HdrImage> p)
{
	int n = p.size();
	double **Matrix;
	Matrix = (double **)malloc(sizeof(double *)*n);
	for(int i = 0; i < n; i++)
	{
		Matrix[i] = (double *)malloc(sizeof(double)*n);
		for(int j = 0; j < n; j++)
		{
			if(i == j) Matrix[i][j] = m[i];
			else if(i == (j+1)) Matrix[i][j] = h[i];
			else if(i == (j-1) && i+1 < n) Matrix[i][j] = h[i+1];
			else Matrix[i][j] = 0;
		}
	}
	for(int i = 0; i < n-1; i++)
	{
		double r;
		r = Matrix[i+1][i]/Matrix[i][i];
		p[i+1] = p[i+1]-p[i]*r;
		Matrix[i+1][i] = Matrix[i+1][i]-Matrix[i][i]*r;
		Matrix[i+1][i+1] = Matrix[i+1][i+1]-Matrix[i][i+1]*r;
	}
	for(int i = n-1; i >= 0; i--)
	{
		double r;
		r = 1.0f/Matrix[i][i];
		p[i] = p[i]*r;
		Matrix[i][i] = Matrix[i][i]*r;
		if(i > 0)
		{
			r = Matrix[i-1][i];
			Matrix[i-1][i] = Matrix[i-1][i]-Matrix[i][i]*r;
			p[i-1] = p[i-1]-p[i]*r;
		} 
	}

	for(int i = 0; i < n; i++)
	{
		free(Matrix[i]);
	}
	free(Matrix);

	dy2.clear();
	dy2.push_back(HdrImage(imgWidth, imgHeight));
	for(int i = 0; i < n; i++)
	{
		dy2.push_back(p[i]);
	}
	dy2.push_back(HdrImage(imgWidth,imgHeight));
}

double quadraticRootBetween0And1(double a, double b, double c)
{
	double delta = b*b-4*a*c;
	double ret = (-b+sqrt(delta))/(2.0*a);
	if(!(ret > 0 && ret < 1))  ret = (-b-sqrt(delta))/(2.0*a);
	return ret;
}


// http://stackoverflow.com/questions/4269069/finding-cube-root-in-c
double curt(double x) {
  if (x == 0) {
    // would otherwise return something like 4.257959840008151e-109
    return 0;
  }
  double b = 1; // use any value except 0
  double last_b_1 = 0;
  double last_b_2 = 0;
  while (last_b_1 != b && last_b_2 != b) {
    last_b_1 = b;
    b = (2 * b + x / b / b) / 3;
    last_b_2 = b;
    b = (2 * b + x / b / b) / 3;
  }
  return b;
}


// https://proofwiki.org/wiki/Cardano%27s_Formula
double cubicRootBetween0And1(double a,double b,double c, double d)
{
	complex<double> Q,R,S,T,X1,X2,X3,D;
	double theta, cos_theta, x;
	Q = (3.0*a*c-b*b)/(9.0*a*a);
	R = (9.0*a*b*c-27.0*a*a*d-2.0*b*b*b)/(54.0*a*a*a);
	D = Q*Q*Q+R*R;


	// D == 0
	if(fabs(D.real()) < Epsilon) 
	{
		T = S = complex<double>(curt(R.real()),0);
		X1 = S.real()+T.real()-b/(3.0*a);
		X2 = X3 = (-1.0/2.0)*(S.real()+T.real())-b/(3.0*a);
	}


	// SE D < 0 --> FORMA TRIGONOMETRICA
	else if(D.real() < 0.0)
	{
		cos_theta = R.real()/sqrt(-Q.real()*Q.real()*Q.real());
		theta = acos(cos_theta);
		X1 = 2*sqrt(-Q.real())*cos(theta/3.0)-b/(3.0*a);
		X2 = 2*sqrt(-Q.real())*cos(theta/3.0+2*Pi/3.0)-b/(3.0*a);
		X3 = 2*sqrt(-Q.real())*cos(theta/3.0+4*Pi/3.0)-b/(3.0*a);
	}

	// D > 0
	else
	{
		S = curt(R.real()+sqrt(D).real());
		T = curt(R.real()-sqrt(D).real());
		X1 = S.real()+T.real()-b/(3.0*a);
		X2 = (-1.0/2.0)*(S+T)-b/(3.0*a)+(S-T)*complex<double>(0,sqrt(3.0)/2);
		X3 = (-1.0/2.0)*(S+T)-b/(3.0*a)-(S-T)*complex<double>(0,sqrt(3.0)/2);
	}

	if(X1.real() >= -Epsilon && X1.real() <= (1.0 + Epsilon) && fabs(X1.imag()) < Epsilon) x = X1.real();
	else if(X2.real() >= 0.0 && X2.real() <= (1.0 + Epsilon) && fabs(X2.imag()) < Epsilon) x = X2.real();
	else x = X3.real();
	if (x < 0.0) x = 0.0;
	return x;
}