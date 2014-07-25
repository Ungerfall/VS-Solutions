#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
//#include <depthlib.h>

struct _list
{
	int value;
	struct _list *next;
};


_list *spisok, *start;
int n;

void _PrintList(_list *start)
{
	for (;;)
	{
		printf("%d\n", start->value);
		if (start->next == NULL)
			break;
		start = start->next;
	}
}

void _Add(_list *start, int k, int x)
{
	int i = 0, tek;
	while (i != k - 1)
	{
		start = start->next;
		i++;
	}
	while (start->next != NULL)
	{
		start = start->next;
		tek = x;
		x = start->value;
		start->value = tek;
	}
	start->next = new _list;
	start->next->value = x;
	start->next->next = NULL;
}

void _Delete(_list *_start, int k)
{
	if (k == 1)
	{
		start = _start->next;
	}
	else
	{
		int i = 1;
		while (i != k - 1)
		{
			_start = _start->next;
			i++;
		}
		if (_start->next->next == NULL)
			_start->next = NULL;
		else
			_start->next = _start->next->next;
	}
}

_list *_Reverse(_list *_start)
{
	_list *new_root = 0;
	while (_start)
	{
		_list *next = _start->next;
		_start->next = new_root;
		new_root = _start;
		_start = next;
	}
	return new_root;
}

int main()
{	
	spisok = new _list;
	start = new _list;
	start = spisok;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &spisok->value);
		spisok->next = NULL;
		if (i != n - 1)
		{
			spisok->next = new _list;
			spisok = spisok->next;
		}
	}
	
	_PrintList(start);
	start = _Reverse(start);
	_PrintList(start);

	return 0;
}