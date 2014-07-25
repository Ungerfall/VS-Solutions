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
	static bool CheckLen(string a)		//�������� �� ����� ������
	{
		if (a.length() > 20)
			return false;
		else
			return true;
	}
};

//����������� �� ���������
Person::Person()
{
	firstname = "������";
	secondname = "����";
	Patronymic = "��������";
	age = 16;
}

//�����������
Person::Person(string a, string b, string c, int d)
{
	SetFirstname(a);
	SetSecondname(b);
	SetPatronymic(c);
	SetAge(d);
}

//��������� ��������
void Person::SetAge(int a)
{
	if (a < 0 || a > 200)
		cout << "������. ������� ������ ���� � �������� [0..200] ���.\n";
	else
		age = a;
}

//��������� �����
void Person::SetFirstname(string a)
{
	if (!CheckLen(a))
		cout << "������. ����� ������ ���� � �������� [1..20] ��������.\n";
	else
		firstname = a; 
}

//��������� �������
void Person::SetSecondname(string a)
{
	if (!CheckLen(a))
		cout << "������. ����� ������ ���� � �������� [1..20] ��������.\n";
	else
		secondname = a;
}

//��������� ��������
void Person::SetPatronymic(string a)
{
	if (!CheckLen(a))
		cout << "������. ����� ������ ���� � �������� [1..20] ��������.\n";
	else
		Patronymic = a;
}

//��������� ��������
int Person::GetAge()
{
	return this->age;
}

//��������� �����
string Person::GetFirstname()
{
	return this->firstname;
}

//��������� �������
string Person::GetSecondname()
{
	return this->secondname;
}

//��������� ��������
string Person::GetPatronymic()
{
	return this->Patronymic;
}

//����� �� �����
void Person::Print()
{
	cout << "���������� � ��������:\n";
	cout << "�������:\t" << this->firstname << endl;
	cout << "���:\t\t" << this->secondname << endl;
	cout << "��������:\t" << this->Patronymic << endl;
	cout << "�������:\t" << this->age << endl << endl;
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
	static string GetMarkAuto(int a)	//��������� ����� ���������� ��������
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

//����������� �� ���������
Auto::Auto()
{
	driver = Person();
	mark = Cadillac;
	number = "00 AAA 0000";
}

//�����������
Auto::Auto(MarkAuto a, string b)
{
	mark = a;
	number = b;
}

//��������� ��������
void Auto::SetDriver(Person &a)
{
	if (a.GetAge() < 18)
		cout << "������. ������� ��������� ������������� ������������� ������ ���� ������ 18 ���" << endl;
	else
		driver = a;
}

//������ ������ � ��������
void Auto::Print()
{
	cout << "������ � ��������:" << endl;
	cout << "�������:\t\t" << driver.GetFirstname() << endl;
	cout << "���:\t\t\t" << driver.GetSecondname() << endl;
	cout << "��������:\t\t" << driver.GetPatronymic() << endl;
	cout << "�������:\t\t" << driver.GetAge() << endl;
	cout << "����� ����������:\t" << GetMarkAuto(mark) << endl;
	cout << "����� ����������:\t" << number << endl << endl;
}

//������� �����
int main()
{
	setlocale(LC_ALL, "Russian");
	Person person_one;
	Person person_two("������", "������", "���������", 19);
	person_one.Print();
	person_two.Print();
	Auto voditel(Dodge, "12 ��� 7342");
	voditel.SetDriver(person_two);
	voditel.Print();

	getchar();
	return 0;
}

