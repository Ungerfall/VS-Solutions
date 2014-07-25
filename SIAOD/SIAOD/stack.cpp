/*#include <cstdio>
#include <conio.h>
int a[30];
int top = 0;
void push (int elem)
{
	if (top < 30)
		a[top++] = elem;
}

void pop ()
{
	if (top > 0)
		top --;
}

int main ()
{
	push ( 1 );
	push ( 2 );
	printf ("%d\n", a[top - 1]);
	pop();
	printf ("%d\n", a[top - 1]);
	getch();
	return 0;
}*/
#include <stdio.h>
#include <conio.h>

const int MAX = 1000;

int main()
{
	int a[MAX][MAX], n, i, j;
	int s1 = 0, s2 = 0, s3 = 0;

	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[j]);	
	for(i = 0; i < n; i++)
	{
		s2 += a[i][i];
		for(j = 0; j < n; j++)
		{
			if (i < j)
				s1 += a[i][j];
			else
				s3 += a[i][j];
		}
	}		
	printf("%d\n%d\n%d", s1, s2, s3 - s2);

	getch();
	return 0;
}