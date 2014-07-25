#include "DrawingClass.h"

const float PI = 3.14159265f;

void DrawingClass::dcPoint(pair <glF, glF> point, glF x, glF y, glF z)
{
	glTranslatef(x, y, z);
	glBegin(GL_POINTS);
	glVertex2d(point.first, point.second);
	glEnd();
}

void DrawingClass::dcSin(glF x, glF y, glF z, glF h, int p)
{
	glTranslatef(x, y, z);
	int k = (int)((p * 2 * PI) / h);
	glF xi = 0;
	glF yi = 0;
	glBegin(GL_POINTS);
	for (int i = 0; i < k; i++)
	{
		xi = (i * h) / (p * PI) - 1;
		yi = (float)(sin(i * h) * 0.5);
		glVertex2d(xi, yi);
	}
	glEnd();

}

void DrawingClass::dcTriangleStrip(glF xi, glF yi, glF hei, glF wid)
{
	float _x = (xi - (wid / 2)) / (wid / 2);
	float _y = ((hei / 2) - yi) / (hei / 2);
	glColor3f(GetRand(), GetRand(), GetRand());
	glVertex2f(_x, _y);
}



