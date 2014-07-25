#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <bitset>

const int MAX = 8;
const int RAZ = 3;

char max_koef;
int max_index1;
int max_index2;
int ind[MAX-1] = {1, 2, 3, 12, 13, 23, 123};
int f[MAX];
int i, j;

using namespace std;

struct neo_ko
{
	char koef;		//коэффициент
	int index1;		//верхний индекс коэффициента (будет хранитс€ в 10й сс)
	int index2;		//нижний индекс коэффициента
}	tabl[MAX][MAX-1];

//перевод из 10-й в 2-ую сс + печать
void dvoic(int a, int b)		
{
	bitset<RAZ>bi;

	bi = a;
	for (int i = b - 1; i >= 0; i--)
		cout << bi[i];
}

//создание верхнего индекса (почти ручной ввод...не нашел закономерность дл€ заполнени€ в цикле)
void sozd_ind1(int i)
{
	switch(i)
	{
	case 0:
		{
			for(j = 0; j < MAX - 1; j++)
				tabl[i][j].index1 = 0;
			break;
		}
	case 1:
		{
			tabl[1][0].index1 = 0;
			tabl[1][1].index1 = 0;
			tabl[1][2].index1 = 1;
			tabl[1][3].index1 = 0;
			tabl[1][4].index1 = 1;
			tabl[1][5].index1 = 1;
			tabl[1][6].index1 = 1;
			break;
		}
	case 2:
		{
			tabl[2][0].index1 = 0;
			tabl[2][1].index1 = 1;
			tabl[2][2].index1 = 0;
			tabl[2][3].index1 = 1;
			tabl[2][4].index1 = 0;
			tabl[2][5].index1 = 2;
			tabl[2][6].index1 = 2;
			break;
		}
	case 3:
		{
			tabl[3][0].index1 = 0;
			tabl[3][1].index1 = 1;
			tabl[3][2].index1 = 1;
			tabl[3][3].index1 = 1;
			tabl[3][4].index1 = 1;
			tabl[3][5].index1 = 3;
			tabl[3][6].index1 = 3;
			break;
		}
	case 4:
		{
			tabl[4][0].index1 = 1;
			tabl[4][1].index1 = 0;
			tabl[4][2].index1 = 0;
			tabl[4][3].index1 = 2;
			tabl[4][4].index1 = 2;
			tabl[4][5].index1 = 0;
			tabl[4][6].index1 = 4;
			break;
		}
	case 5:
		{
			tabl[5][0].index1 = 1;
			tabl[5][1].index1 = 0;
			tabl[5][2].index1 = 1;
			tabl[5][3].index1 = 2;
			tabl[5][4].index1 = 3;
			tabl[5][5].index1 = 1;
			tabl[5][6].index1 = 5;
			break;
		}
	case 6:
		{
			tabl[6][0].index1 = 1;
			tabl[6][1].index1 = 1;
			tabl[6][2].index1 = 0;
			tabl[6][3].index1 = 3;
			tabl[6][4].index1 = 2;
			tabl[6][5].index1 = 2;
			tabl[6][6].index1 = 6;
			break;
		}
	case 7:
		{
			tabl[7][0].index1 = 1;
			tabl[7][1].index1 = 1;
			tabl[7][2].index1 = 1;
			tabl[7][3].index1 = 3;
			tabl[7][4].index1 = 3;
			tabl[7][5].index1 = 3;
			tabl[7][6].index1 = 7;
			break;
		}
	}
}

//поиск одинаковых элементов
void look_for_elem()
{
	for(int i2 = 0; i2 < MAX; i2++)
		for(int j2 = 0; j2 < MAX - 1; j2++)
			if(tabl[i][j].index1 == tabl[i2][j2].index1 && tabl[i][j].index2 == tabl[i2][j2].index2)
				tabl[i2][j2].koef = '0';
}

//количество неизвестных K
int kol_k()
{
	int count = 0;
	for(int i2 = 0; i2 < MAX; i2++)
		for(int j2 = 0; j2 < MAX - 1; j2++)
			if(tabl[i2][j2].koef == 'K')
				count++;
	return count;
}

//вывод на экран минимальной формы 
void print_min_form()
{
	cout << "ћ»Ќ»ћјЋ№Ќјя ‘ќ–ћј:\n";
	for(int i2 = 0; i2 < MAX; i2++)
		for(int j2 = 0; j2 < MAX - 1; j2++)
			if(tabl[i2][j2].koef == '1')
			{
				switch(ind[j2])
				{
				case 1:
					{
						if(tabl[i2][j2].index1 == 1)
							cout << "x1 ";
						else
							cout << "not x1 ";
						break;
					}
				case 2:
					{
						if(tabl[i2][j2].index1 == 1)
							cout << "x2 ";
						else
							cout << "not x2 ";
						break;
					}
				case 3:
					{
						if(tabl[i2][j2].index1 == 1)
							cout << "x3 ";
						else
							cout << "not x3 ";
						break;
					}
				case 12:
					{
						if(tabl[i2][j2].index1 == 0)
							cout << "not x1 & not x2 ";
						else
							if(tabl[i2][j2].index1 == 1)
								cout << "not x1 & x2 ";
							else
								if(tabl[i2][j2].index1 == 2)
									cout << "x1 & not x2 ";
								else
									cout << "x1 & x2 ";
						break;
					}
				case 13:
					{
						if(tabl[i2][j2].index1 == 0)
							cout << "not x1 & not x3 ";
						else
							if(tabl[i2][j2].index1 == 1)
								cout << "not x1 & x3 ";
							else
								if(tabl[i2][j2].index1 == 2)
									cout << "x1 & not x3 ";
								else
									cout << "x1 & x3 ";
						break;
					}
				case 23:
					{
						if(tabl[i2][j2].index1 == 0)
							cout << "not x2 & not x3 ";
						else
							if(tabl[i2][j2].index1 == 1)
								cout << "not x2 & x3 ";
							else
								if(tabl[i2][j2].index1 == 2)
									cout << "x2 & not x3 ";
								else
									cout << "x2 & x3 ";
						break;
					}
				case 123:
					{
						switch(tabl[i2][j2].index1)
						{
						case 0:
							{
								cout << "not x1 & not x2 & not x3 ";
								break;
							}
						case 1:
							{
								cout << "not x1 & not x2 & x3 ";
								break;
							}
						case 2:
							{
								cout << "not x1 & x2 & not x3 ";
								break;
							}
						case 3:
							{
								cout << "not x1 & x2 & x3 ";
								break;
							}
						case 4:
							{
								cout << "x1 & not x2 & not x3 ";
								break;
							}
						case 5:
							{
								cout << "x1 & not x2 & x3 ";
								break;
							}
						case 6:
							{
								cout << "x1 & x2 & not x3 ";
								break;
							}
						case 7:
							{
								cout << "x1 & x2 & x3 ";
								break;
							}
						}

						break;
					}
				}
				cout << "+ ";
			};			
}

//поиск самого частого коэффициента
void look_for_koef()
{
	neo_ko arr[MAX * (MAX - 1)];
	for(i = 0; i < MAX; i++)
		for(j = 0; j < MAX - 1; j++)
			if (tabl[i][j].koef == 'K')
			{
				arr[i+j].index1 = tabl[i][j].index1;
				arr[i+j].index2 = tabl[i][j].index2;
				arr[i+j].koef = tabl[i][j].koef;
			}
			else;
	int maxcount(1), nn(-1);
	for(i = 0; i < MAX + MAX - 1; i++)
	{
		int count(0);
		for(j = i; j < MAX + MAX - 1; j++)
			if (arr[i].index1 == arr[j].index1 && arr[i].index2 == arr[j].index2 && arr[i].koef == 'K')
				count++;
		if (maxcount < count)
		{
			maxcount = count;
			nn = i;
		}
	}
	if (nn > -1)
	{
		max_index1 = arr[nn].index1;
		max_index2 = arr[nn].index2;
	}			
}

//полна€ система
void poln_forma()
{
	//печать полной системы
	cout << "ѕќЋЌјя —»—“≈ћј:\n";
	for(i = 0; i < MAX; i++)
	{
		dvoic(i, 3);
		cout << " | ";
		for(j = 0; j < MAX - 1; j++)
		{
			cout << tabl[i][j].koef << ".";
			dvoic(tabl[i][j].index1, j / 3 + 1);
			cout << "." << tabl[i][j].index2 << " | ";
		}
		cout << "= " << f[i];
		cout << "\n";
	}
}
//сокращенна€ система
void sokr_forma()
{
	//создание сокращенной формы
	for(i = 0; i < MAX; i++)
	{
		if (f[i] == 0)//значение функции == 0
			for(j = 0; j < MAX - 1; j++)
			{
				tabl[i][j].koef = '0';
				look_for_elem();
			};
	}
	//печать сокращенной системы
	cout << "—ќ –јў≈ЌЌјя —»—“≈ћј:\n";
	for(i = 0; i < MAX; i++)
	{
		if (f[i] == 1)
		{
			dvoic(i, 3);
			cout << " | ";
			for(j = 0; j < MAX - 1; j++)
				if (tabl[i][j].koef != '0')
				{
					cout << tabl[i][j].koef << ".";
					dvoic(tabl[i][j].index1, j / 3 + 1);
					cout << "." << tabl[i][j].index2 << " | ";
				};
			cout << "= " << f[i];
			cout << "\n";
		};
	}
}

//минимизаци€
void minimazition()
{
	if (kol_k() == 1)
	{
		for(i = 0; i < MAX; i++)
			for(j = 0; j < MAX - 1; j++)
				if (tabl[i][j].koef == 'K')
					tabl[i][j].koef = '1';
		print_min_form();
	}
	else
	{
		int k_count;
		for(i = 0; i < MAX; i++)
		{
			k_count = 0;
			for(j = 0; j < MAX - 1; j++)
			{				
				if (tabl[i][j].koef == 'K')
					k_count++;
			}
			if (k_count == 2)		//случай, когда 1 V A = 1
			{
				int cheak = -1;
				for(j = 0; j < MAX - 1; j++)
					if (tabl[i][j].koef == 'K' && cheak == -1)//приравниваем 1 из коэф 1
					{
						cheak--;
						tabl[i][j].koef = '1';
						for(int i2 = 0; i2 < MAX; i2++)
							for(int j2 = 0; j2 < MAX - 1; j2++)
								if(tabl[i][j].index1 == tabl[i2][j2].index1 && 
								   tabl[i][j].index2 == tabl[i2][j2].index2 &&
								   i2 != i)
									tabl[i2][j2].koef = '0';
					}
					else										//другой - обнул€ем
						if (tabl[i][j].koef == 'K')
						{
							tabl[i][j].koef = '0';
							look_for_elem();
						};
			};
		}
		//поиск одинаковых элементов
		look_for_koef();
		for(i = 0; i < MAX; i++)
			for(j = 0; j < MAX - 1; j++)
				if (tabl[i][j].index1 == max_index1 && tabl[i][j].index2 == max_index2)
				{
					tabl[i][j].koef = '1';
					for(int j2 = 0; j2 < MAX - 1; j2++)
						if (tabl[i][j2].koef != '1')
							tabl[i][j2].koef = '0';
					;
				};
		for(i = 0; i < MAX; i++)
			for(j = 0; j < MAX - 1; j++)
				if (tabl[i][j].koef == 'K')
					tabl[i][j].koef = '1';
		for(i = 0; i < MAX; i++)
			for(j = 0; j < MAX - 1; j++)
				if (tabl[i][j].koef == '1')
				{
					look_for_elem();
					tabl[i][j].koef = '1';
				}
		print_min_form();
	}
}
int main()
{
	setlocale(LC_ALL,"Russian");

	cout << "¬ведите функцию, заданную вектором (через пробел)\n";
	for (i = 0; i < MAX; i++)
		cin >> f[i];
	cout << "\n";
	//заполнение системы
	for(i = 0; i < MAX; i++)
	{
		for(j = 0; j < MAX - 1; j++)
		{
			tabl[i][j].koef = 'K';	//K - неизвестен			
			tabl[i][j].index2 = ind[j];
		}
		sozd_ind1(i);
	}
	poln_forma();
	sokr_forma();
	minimazition();
	
	getch();
	return 0;
}