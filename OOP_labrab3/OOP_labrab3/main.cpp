#include <iostream>

using namespace std;

//элемент
template <class T>
class Element
{
public:
	Element();
	Element(T);
	T Data;
	Element *pNextData;
};

template <class T>
Element<T>::Element()
{
	pNextData = 0;
}

template <class T>
Element<T>::Element(T _data)
{
	Data = _data;
	pNextData = 0;
}
//очерерь FIFO
template <class T>
class Q_OFIF
{
public:
	Q_OFIF();
	void Add(T);
	void pop();
	void Clear();
	T GetFirst();
	T GetLast();
	int size();
	void Show();
	static Q_OFIF ToQ_OFIF(T *a)
	{
		Q_OFIF<T> q;
		for (int i = 0; i < (sizeof(a) / sizeof(*a)); i++)
		{
			q.Add(a[i]);
		}
		return q;
	}

private:
	Element<T> *pFirst;
	Element<T> *pLast;
};
//конструктор
template <class T>
Q_OFIF<T>::Q_OFIF()
{
	this->pFirst = 0;
	this->pLast = 0;
}
//добавление элемента в контейнер
template <class T>
void Q_OFIF<T>::Add(T elem)
{
	Element<T> *pAdd = new Element<T>(elem);
	if (this->pFirst == 0)
	{
		pFirst = pAdd;
		pLast = pAdd;
	}
	else
	{
		this->pLast->pNextData = pAdd;
		this->pLast = pAdd;
	}
}
//поп
template <class T>
void Q_OFIF<T>::pop()
{
	try
	{
		if (!this->pFirst)
			throw 1;
		Element<T> *elem = this->pFirst;
		if (this->pFirst == this->pLast)
		{
			this->pFirst = 0; 
			this->pLast = 0;
		}
		else
			this->pFirst = this->pFirst->pNextData;
		delete elem;
	}
	catch (int)
	{
		cout << "Ошибка. Контейнер пуст\n";
	}
}
//очистка контейнера
template <class T>
void Q_OFIF<T>::Clear()
{
	while (!(this->pFirst == 0))
		this->pop();
}
//получение первого элемента
template <class T>
T Q_OFIF<T>::GetFirst()
{
	try
	{
		if (!this->pFirst)
			throw 1;
		return this->pFirst->Data;
	}
	catch (int)
	{
		cout << "Ошибка. Контейнер пуст\n";
	}
}
//получение последнего элемента
template <class T>
T Q_OFIF<T>::GetLast()
{
	try
	{
		if (!this->pFirst)
			throw 1;
		return this->pLast->Data;
	}
	catch (int)
	{
		cout << "Ошибка. Контейнер пуст\n";
	}
}
//размер контейнера
template <class T>
int Q_OFIF<T>::size()
{
	int size = 0;
	Element<T> *elem = this->pFirst();
	while (elem != 0)
	{
		size++;
		elem = elem->pNextData;
	}
	return size;
}
//вывод на экран
template <class T>
void Q_OFIF<T>::Show()
{
	try
	{
		if (!this->pFirst)
			throw 1;
		Element<T> *pCurr = this->pFirst;
		do
		{
			cout << pCurr->Data << endl;
		}
		while ((pCurr = pCurr->pNextData) != NULL);
	}
	catch (int)
	{
		cout << "Ошибка. Контейнер пуст\n";
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Q_OFIF<int> q;
	q.pop();
	q.Add(1);
	q.Add(2);
	q.Add(3);
	q.Show();
	q.Clear();

	int a[3] = {1, 2, 3};
	q = Q_OFIF<int>::ToQ_OFIF(a);
	q.Show();

	return 0;
}