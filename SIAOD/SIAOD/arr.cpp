/*#include <stdio.h>
#include <conio.h>

int main()
{
	int arr[10][10];						
	int i, j;
	for (i = 1; i <= 10; i++)			//заполнение массива
		for (j = 1; j <= 10; j++)
			arr[i][j] = 0;
	for (i = 1; i <= 10; i++)
	{
		if (i % 2 == 1)		//нечетные строки
		{
			for (j = 1; j <= 5; j++)	
				arr[i][2 * j - 1] = 1;		//нечентые столбцы
		}
		else				//четные строки
		{
			for (j = 1; j <= 5; j++)		//четные столбцы
				arr[i][2 * j] = 1;
		}
	}
	for (i = 1; i <= 10; i++)			//вывод массива
	{
		for (j = 1; j <= 10; j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
	getch();
	return 0;
}*/