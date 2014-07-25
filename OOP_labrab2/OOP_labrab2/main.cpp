#include "CEllipse.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CShape.h"
#include "CPoint.h"
#include <time.h>
#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(NULL));

	CShape* p[2];

	for (int i = 0; i < 2; i++)
	{
		int rng = rand() % 3;
		switch (rng)
		{
		case 0:
			{
				CPoint a(1 + rand() % 20, 1 + rand() % 20);
				CPoint b(1 + rand() % 20, 1 + rand() % 20);
				CPoint c(1 + rand() % 20, 1 + rand() % 20);
				p[i] = new CRectangle(a, b, c);
				break;
			}
		case 1:
			{
				CPoint a(1 + rand() % 20, 1 + rand() % 20);
				CPoint b(1 + rand() % 20, 1 + rand() % 20);
				CPoint c(1 + rand() % 20, 1 + rand() % 20);
				p[i] = new CTriangle(a, b, c);
				break;
			}
		case 2:
			{
				CPoint a(1 + rand() % 20, 1 + rand() % 20);
				CPoint b(1 + rand() % 20, 1 + rand() % 20);
				CPoint c(1 + rand() % 20, 1 + rand() % 20);
				p[i] = new CEllipse(a, b, c);;
				break;
			}
		}
	}

	p[0]->About();
	p[1]->About();

	cout << endl << endl;
	if (p[0]->Square() > p[1]->Square())
		cout << p[0]->Name() << " больше " << p[1]->Name() << " :" << p[0]->Square() << " > " << p[1]->Square() << endl;
	else
		if (p[0]->Square() == p[1]->Square())
			cout << p[0]->Name() << " равен " << p[1]->Name() << " :" << p[0]->Square() << " == " << p[1]->Square() << endl;
		else
			cout << p[0]->Name() << " меньше " << p[1]->Name() << " :" << p[0]->Square() << " < " << p[1]->Square() << endl;

	return 0;
}