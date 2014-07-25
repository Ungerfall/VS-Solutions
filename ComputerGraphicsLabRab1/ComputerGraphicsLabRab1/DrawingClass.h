#pragma once
#include "DrawingClass.h"
#include "LabRab1.h"
#include <utility>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <random>

typedef GLfloat glF;

enum TypeofShapes
{
	points = 0,
	lines,
	line_strip,
	line_loop,
	triangles,
	triangle_strip,
	triangle_fun,
	quads,
	quad_strip,
	polygon,
	sinusoida,
	bengal_fire
};

class DrawingClass
{
public:	
	//draw
	void dcPoint(pair <glF, glF> point, glF x, glF y, glF z);

	void dcSin(glF x, glF y, glF z, glF h, int p);

	void dcTriangleStrip(glF xi, glF yi, glF hei, glF wid);
	
};

