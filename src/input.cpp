#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include "input.h"

#ifdef _MSC_VER 
#include <direct.h> 
#else
#include <sys/stat.h>
#include <string.h>
#endif

using namespace std;
char separator[2];



void interpolationsTypesVerifier(char *type, bool &lagrange, bool &linear, bool &quadratic, bool &gaussforward, bool &gaussbackward, bool &stirling, bool &ncspline, bool &bezier, bool &bezierquad, bool &beziercub, bool &bsplinecub)
{
	if(strcmp(type, "lagrange")==0) lagrange = true;
	else if(strcmp(type, "linear")==0) linear = true;
	else if(strcmp(type, "quadratic")==0) quadratic = true;
	else if(strcmp(type, "gaussforward")==0) gaussforward = true;
	else if(strcmp(type, "gaussbackward")==0) gaussbackward = true;
	else if(strcmp(type, "stirling")==0) stirling = true;
	else if(strcmp(type, "ncspline")==0) ncspline = true;
	else if(strcmp(type, "bezier")==0) bezier = true;
	else if(strcmp(type, "bezierquad")==0) bezierquad = true;
	else if(strcmp(type, "beziercub")==0) beziercub = true;
	else if(strcmp(type, "bsplinecub")==0) bsplinecub = true;
	else cout << "Undefined interpolation.\n";
}

void interpolate(char *seriesName, vector<HdrImage> images, vector<int> observations, int observationTime, bool &lagrange, bool &linear, bool &quadratic, bool &gaussforward, bool &gaussbackward, bool &stirling, bool &ncspline, bool &bezier, bool &bezierquad, bool &beziercub, bool &bsplinecub)
{
	string sfname;
	if(lagrange) 
	{
		sfname.erase();
		LaGrangeInterpolator la(observations, images);
		sfname.append(seriesName).append(separator).append("lagrange").append(to_string(observationTime)).append(".tif");
		la.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(linear)
	{
		sfname.erase();
		LinearInterpolator li(observations, images);
		sfname.append(seriesName).append(separator).append("linear").append(to_string(observationTime)).append(".tif");
		li.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(quadratic)
	{
		sfname.erase();
		QuadraticInterpolator qua(observations, images);
		sfname.append(seriesName).append(separator).append("quadratic").append(to_string(observationTime)).append(".tif");
		qua.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(gaussforward)
	{
		sfname.erase();
		GaussianForwardInterpolator gaf(observations, images);
		sfname.append(seriesName).append(separator).append("gaussforward").append(to_string(observationTime)).append(".tif");
		gaf.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(gaussbackward)
	{
		sfname.erase();
		GaussianBackwardInterpolator gab(observations, images);
		sfname.append(seriesName).append(separator).append("gaussbackward").append(to_string(observationTime)).append(".tif");
		gab.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(stirling)
	{
		sfname.erase();
		StirlingInterpolator stir(observations, images);
		sfname.append(seriesName).append(separator).append("stirling").append(to_string(observationTime)).append(".tif");
		stir.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(ncspline)
	{
		sfname.erase();
		NaturalCubicSplineInterpolator ncs(observations, images);
		sfname.append(seriesName).append(separator).append("ncspline").append(to_string(observationTime)).append(".tif");
		ncs.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(bezier)
	{
		sfname.erase();
		BezierApproximator bez(observations, images);
		sfname.append(seriesName).append(separator).append("bezier").append(to_string(observationTime)).append(".tif");
		bez.calculateContinuousInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(bezierquad)
	{
		sfname.erase();
		BezierQuadraticApproximator bezq(observations, images);
		sfname.append(seriesName).append(separator).append("bezierquad").append(to_string(observationTime)).append(".tif");
		bezq.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(beziercub)
	{
		sfname.erase();
		BezierCubicApproximator bezc(observations, images);
		sfname.append(seriesName).append(separator).append("beziercub").append(to_string(observationTime)).append(".tif");
		bezc.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
	if(bsplinecub)
	{
		sfname.erase();
		BSplineApproximator bsc(observations, images);
		sfname.append(seriesName).append(separator).append("bsplinecub").append(to_string(observationTime)).append(".tif");
		bsc.calculateInterpolationOn(observationTime).saveImageAsTif(sfname);
	}
}

void difference(char *seriesName, char *imageFile, char *imageFile2, char *description)
{
	string sfname;
	sfname.erase();
	sfname.append(seriesName).append(separator).append("dif_").append(description).append(".tif");
	HdrImage im1(imageFile);
	HdrImage im2(imageFile2);
	float d = im1.calcDist(im2);
	float d2 = im1.calcDist_L1(im2);
	HdrImage diff = im1.diffAbs(im2);
	diff.saveImageAsTif(sfname);
	printf("L2, L1 - %15s: %10.1f\t%10.1f\n", description, d, d2);
}


int fileRead(char *fname)
{
	int interpolationTypes;
	int observationTime;
	char inputType[260];
	char seriesName[260];
	char imageFile[260];
	char imageFile2[260];
	char imageFile3[260];
	char imageFile4[260];
	char description[260];
	char interpolationType[260];
	bool lagrange,linear,quadratic,gaussforward,gaussbackward,stirling,ncspline,bezier,bezierquad,beziercub,bsplinecub;
	int imageTime;
	vector<HdrImage> images;
	vector<int> observations;

	separator[0] = sep;
	separator[1] = '\0';
	string line;
	fstream file;
	int i = 0;
	lagrange=linear=quadratic=gaussforward=gaussbackward=stirling=ncspline=bezier=bezierquad=beziercub=bsplinecub=false;

	file.open(fname, fstream::in);
	if (!file.is_open())
	{
		cout << "Error opening file: " << fname << "\n";
		return 1;
	}

	getline(file,line);

	sscanf(line.c_str(), "%s \"%[^\"]\"", inputType, seriesName);

	#ifdef _WIN32
		_mkdir(seriesName);
	#else 
		mkdir(seriesName, 0777);
	#endif

	if((strcmp(inputType, "interpolate") == 0) || strcmp(inputType, "interpolate_loop") == 0)
	{
		getline(file,line);
		sscanf(line.c_str(), "%d %d", &interpolationTypes, &observationTime);
		while (getline(file,line))
		{
			if(i < interpolationTypes)
			{
				sscanf(line.c_str(), "%s", interpolationType);
				interpolationsTypesVerifier(interpolationType, lagrange, linear, quadratic, gaussforward, gaussbackward, stirling, ncspline, bezier, bezierquad, beziercub, bsplinecub);
				i++;
			}
			else
			{
				sscanf(line.c_str(), "\"%[^\"]\" %d", imageFile, &imageTime );
				images.push_back(HdrImage(imageFile));
				observations.push_back(imageTime);
			}
		}
		if(strcmp(inputType, "interpolate") == 0)
		{
			interpolate(seriesName, images, observations, observationTime, lagrange, linear, quadratic, gaussforward, gaussbackward, stirling,ncspline, bezier, bezierquad, beziercub, bsplinecub);
		}
		else
		{
			int timeDiff = observationTime;
			for(observationTime = observations[0]; observationTime <= observations[observations.size()-1]; observationTime = observationTime+timeDiff)
			{
				interpolate(seriesName, images, observations, observationTime, lagrange, linear, quadratic, gaussforward, gaussbackward, stirling,ncspline, bezier, bezierquad, beziercub, bsplinecub);
			}
		}
	}
	else if (strcmp(inputType, "difference") == 0)
	{
		while (getline(file, line))
		{
			description[0] = '\0';
			sscanf(line.c_str(), "\"%[^\"]\" \"%[^\"]\" %s", imageFile, imageFile2, description);
			difference(seriesName, imageFile, imageFile2, description);
		}
	}
	file.close();
	return 0;
}