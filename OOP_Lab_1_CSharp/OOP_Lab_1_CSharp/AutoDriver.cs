using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OOP_Lab_1_CSharp
{
    class Person
    {
        private String Firstname;
        private String Secondname;
        private String Patronymic;
        private int Age;

        //конструктор
        Person()
        {
            Firstname = "Иван";
            Secondname = "Иванов";
            Patronymic = "Иванович";
            Age = 16;
        }

        //конструктор
        Person(String fname, String sname, String patro, int _age)
        {
            Firstname = fname;
            Secondname = sname;
            Patronymic = patro;
            Age = _age;
        }

        public void SetAge(int a)
        {
            
        }
    }
}
