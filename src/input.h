#ifndef INPUT
#define INPUT

#ifdef _WIN32
#define sep '\\'
#else
#define sep '/'
#endif


#include "linearinterpolator.h"
#include "lagrangeinterpolator.h"
#include "gaussianforwardinterpolator.h"
#include "gaussianbackwardinterpolator.h"
#include "stirlinginterpolator.h"
#include "quadraticinterpolator.h"
#include "naturalcubicsplineinterpolator.h"
#include "bezier.h"
#include "beziercubapproximator.h"
#include "bezierquadapproximator.h"
#include "bsplineapproximator.h"


int fileRead(char *fname);

#endif