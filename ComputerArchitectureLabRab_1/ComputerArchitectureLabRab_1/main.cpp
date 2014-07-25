#include <cstdio>
#include <stdlib.h>
#include <time.h>

const int RANGE = 100;
const int MAX_LENGTH = 100000000;
const int START = 1000;

void CreateArrays();
double MMX_sum(int*, int*, int);
double MVS_sum(int*, int*, int);

int arr_1[MAX_LENGTH], arr_2[MAX_LENGTH], ranges[6];
int s;

int main()
{
	srand(time_t(NULL));

	CreateArrays();
	printf("iterations\tc++\t\tmmx\n-----------------------------------\n");
	for (int i = 0; i < 6; i++)
	{
		double mvs = MVS_sum(arr_1, arr_2, ranges[i]);
		double mmx = MMX_sum(arr_1, arr_2, ranges[i]);
		printf("%d\t%f\t\t%f\t\t%d\n", ranges[i], mvs, mmx, s);
	}

	getchar();
	return 0;
}

void CreateArrays()
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		arr_1[i] = rand() % RANGE;
		arr_2[i] = rand() % RANGE;
	}

	int multi = 1;
	for (int i = 0; i < 6; i++)
	{
		ranges[i] = START * multi;
		multi *= 10;
	}
}

double MVS_sum(int *arr_1, int *arr_2, int length)
{
	clock_t start = clock();
	clock_t end;
	s = 0;
	for (int j = 0; j < length; j++)
	{
		s += arr_1[j] + arr_2[j];
	}
	end = clock();
	return (((double)end - (double)start) / (double)CLOCKS_PER_SEC);
}

double MMX_sum(int *arr_1, int *arr_2, int length_)
{
	clock_t start = clock();
	clock_t end;
	length_ /= 2;
	__asm
	{
		xor ecx, ecx
		mov edi, arr_1
		mov esi, arr_2
		mov edx, length_
cycle:	
		movq mm0, [edi +  8 * ecx]
		movq mm1, [esi +  8 * ecx]
		paddd mm0, mm1
		add ecx, 1
		cmp ecx, edx
		jl	cycle

		emms
	}
	end = clock();
	return (((double)end - (double)start) / (double)CLOCKS_PER_SEC);
}