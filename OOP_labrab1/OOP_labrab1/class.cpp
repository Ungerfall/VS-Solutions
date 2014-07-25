#include<iostream>
#include<string>

using namespace std;

class Person
{
private:
	string firstname;
	string secondname;
	string Patronymic;
	unsigned int age;

public:
	Person();
	Person(string, string, string, int);
	void SetAge(int);
	void SetFirstname(string);
	void SetSecondname(string);
	void SetPatronymic(string);
	int GetAge();
	string GetFirstname();
	string GetSecondname();
	string GetPatronymic();
	void Print();
	static bool CheckLen(string a)		//проверка на длину строки
	{
		if (a.length() > 20)
			return false;
		else
			return true;
	}
};

//конструктор по умолчанию
Person::Person()
{
	firstname = "Иванов";
	secondname = "Иван";
	Patronymic = "Иванович";
	age = 16;
}

//конструктор
Person::Person(string a, string b, string c, int d)
{
	SetFirstname(a);
	SetSecondname(b);
	SetPatronymic(c);
	SetAge(d);
}

//установка возраста
void Person::SetAge(int a)
{
	if (a < 0 || a > 200)
		cout << "Ошибка. Возраст должен быть в пределах [0..200] лет.\n";
	else
		age = a;
}

//установка имени
void Person::SetFirstname(string a)
{
	if (!CheckLen(a))
		cout << "Ошибка. Слово должно быть в пределах [1..20] символов.\n";
	else
		firstname = a; 
}

//установка фамилии
void Person::SetSecondname(string a)
{
	if (!CheckLen(a))
		cout << "Ошибка. Слово должно быть в пределах [1..20] символов.\n";
	else
		secondname = a;
}

//установка отчества
void Person::SetPatronymic(string a)
{
	if (!CheckLen(a))
		cout << "Ошибка. Слово должно быть в пределах [1..20] символов.\n";
	else
		Patronymic = a;
}

//получение возраста
int Person::GetAge()
{
	return this->age;
}

//получение имени
string Person::GetFirstname()
{
	return this->firstname;
}

//получение фамилии
string Person::GetSecondname()
{
	return this->secondname;
}

//получение отчества
string Person::GetPatronymic()
{
	return this->Patronymic;
}

//вывод на экран
void Person::Print()
{
	cout << "Информация о человеке:\n";
	cout << "Фамилия:\t" << this->firstname << endl;
	cout << "Имя:\t\t" << this->secondname << endl;
	cout << "Отчество:\t" << this->Patronymic << endl;
	cout << "Возраст:\t" << this->age << endl << endl;
}

enum MarkAuto
{
	Cadillac,
	Chevrolet,
	Dodge,
	Ford,
	Jeep
};

class Auto
{
private:
	Person driver;
	MarkAuto mark;
	string number;

public:
	Auto();
	Auto(MarkAuto, string);
	void SetDriver(Person&);
	void Print();
	static string GetMarkAuto(int a)	//получение марки автомобиля текстово
	{
		char *Marks[] = 
		{
			"Cadillac",
			"Chevrolet",
			"Dodge",
			"Ford",
			"Jeep"
		};

		return Marks[a];
	}
};

//конструктор по умолчанию
Auto::Auto()
{
	driver = Person();
	mark = Cadillac;
	number = "00 AAA 0000";
}

//конструктор
Auto::Auto(MarkAuto a, string b)
{
	mark = a;
	number = b;
}

//Установка водителя
void Auto::SetDriver(Person &a)
{
	if (a.GetAge() < 18)
		cout << "Ошибка. Возраст владельца водительского удостоверения должен быть старше 18 лет" << endl;
	else
		driver = a;
}

//печать данных о водителе
void Auto::Print()
{
	cout << "Данные о водителе:" << endl;
	cout << "Фамилия:\t\t" << driver.GetFirstname() << endl;
	cout << "Имя:\t\t\t" << driver.GetSecondname() << endl;
	cout << "Отчество:\t\t" << driver.GetPatronymic() << endl;
	cout << "Возраст:\t\t" << driver.GetAge() << endl;
	cout << "Марка автомобиля:\t" << GetMarkAuto(mark) << endl;
	cout << "Номер автомобиля:\t" << number << endl << endl;
}

//главный метод
int main()
{
	setlocale(LC_ALL, "Russian");
	Person person_one;
	Person person_two("Петров", "Леонид", "Сергеевич", 19);
	person_one.Print();
	person_two.Print();
	Auto voditel(Dodge, "12 ПЛС 7342");
	voditel.SetDriver(person_two);
	voditel.Print();

	getchar();
	return 0;
}

