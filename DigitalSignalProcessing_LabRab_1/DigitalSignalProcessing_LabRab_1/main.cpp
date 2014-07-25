#include "main.h"

//global vars

int Fop; //частота опроса
short *x; //массив дельта импульса

int main()
{
	LoadData("SIGNAL.dat");

	getchar();


	return 0;
}

void LoadData(char *name)
{

	FILE *input;
	input = fopen(name, "r");

	__int32 f_op;
	fread(&f_op, 1, sizeof(f_op), input);

	fscanf(input, "%d", &Fop);
	rewind(input);
	char a;
	fscanf(input, "%c", &a);
	rewind(input);
	short b;
	fscanf(input, "%hd", &b);
	void *dd;
	dd = (char*)malloc(sizeof(char));
	rewind(input);
	fread(dd, sizeof(char), 1, input);
	char aa = (char)dd;
	printf("end");
}
