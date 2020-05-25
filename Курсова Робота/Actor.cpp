#include "Actor.h"
#include <iostream>
#include <fstream>
using namespace std;
int Actor::create()
{
    char number[12];
    cin.ignore(10, '\n');
    cout << "\nІм'я: "; cin >> name;
    cout << "Прізвище: "; cin >> surname;
    cout << "По батькові: "; cin >> patronymic;
    cout << "Дата народження: "; cin >> dateOfBirth;
    setSex();
    cout << "Номер телефону: "; cin >> number;
    
    if (phoneValidation(number) == 0)
        return 0;
}
void Actor::setSex()
{
    int s;
    cout << "Стать - чоловік(1), жінка(2)\n";
    for (;;) {
        cin >> s;
        if (s != 1 &&
            s != 2) cout << "Неправильний ввід! Спробуйте ще раз\n";

        else {
            switch (s)
            {
            case 1:
                sex = male;
                break;
            case 2:
                sex = female;
                break;
            default:
                break;
            }
            break;
        }
    }
}

void Actor::getSex()
{
    if (sex == male)
        cout << "чоловік";
    else
        cout << "жінка";
}
void Actor::showData()
{
    cout << "Ім'я: " << name << endl;
    cout << "Прізвище: " << surname << endl;
    cout << "По батькові: " << patronymic << endl;
    cout << "Дата народження: " << dateOfBirth << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Стать: "; getSex(); cout << endl;
}

int Actor::count()
{
    ifstream ifile;
    ifile.open("Actor.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    int v= (int)ifile.tellg() / sizeof(Actor);
    return v;
    ifile.close();
}
int  Actor::phoneValidation(char number[12])
{
    Actor actor;
    ifstream ifile;
    ifile.open("Actor.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Actor));
        ifile.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
        if (0 == strcmp(number, actor.phone))
        {
            cout << "ткий номер телефону уже існує";
            return 0;
        }
    }
    strcpy_s(phone, number);
}
//
//int Actor::setId()
//{
//    ifstream ifile;
//    ifile.open("Actor.dat", ios::binary | ios::out | ios::in);
//    Actor actor;
//    int ok = 0;
//    idCount = 1;//(int)ifile.tellg() / sizeof(Actor);
//    //ifile.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
//    while(ok !=1)
//    {
//        ifile.seekg(0);
//        
//        for (int i = 0; i <= count() ; i++)
//        {
//            ifile.seekg(i * sizeof(Actor));
//            ifile.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
//            if (idCount != phone)
//            {
//                ok = 1;
//                return idCount;
//                //
//                //break;
//            }
//            else
//                ok = 0;
//        }
//            idCount++;
//    }
//    ifile.close();
//}
//
void Actor::write()
{
    ofstream ofile;
    ofile.open("Actor.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

void Actor::read(int p)
{
    ifstream ifile;
    ifile.open("Actor.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(p * sizeof(Actor));
    ifile.read((char*)this, sizeof(*this));
    //idCount = id;
    ifile.close();
}


int Actor::search(int variant)
{
    if (variant == 0)
        return 0;
    Actor actor;
    ifstream ifile;
    char str[40];
    ifile.open("Actor.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "Введіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Actor));
        ifile.read(reinterpret_cast<char*>(&actor), sizeof(Actor));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, actor.name))
            {
                actor.showData();
                cout << endl;
            }
            break;

        case 2:
            if (0 == strcmp(str, actor.surname))
            {
                actor.showData();
                cout << endl;
            }
            break;
        case 3:
            if (0 == strcmp(str, actor.patronymic))
            {
                actor.showData();
                cout << endl;
            }
            break;
        case 4:
            if (0 == strcmp(str, actor.dateOfBirth))
            {
                actor.showData();
                cout << endl;
            }
            break;
        case 5:
            if (atoi(str) == actor.sex)
            {
                
                actor.showData();
                cout << endl;
            }
            break;
        case 6:

            if (0 == strcmp(str, actor.phone))
            {
                cout << endl;
                actor.showData();
            }
            break;
        default:
            break;
        }
    }
    ifile.close();
}

void Actor::edit()
{
    Actor actor;
    char str[40];
    cout << "Введіть номер телефону для редагування: ";
    cin >> str;
    ifstream file;
    file.open("Actor.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    while (!file.eof())
    {

        if (0 != strcmp(str, actor.phone))
        {
            temp.write(reinterpret_cast<char*>(&actor), sizeof(Actor));
        }

        else
        {
            actor.create();
            temp.write(reinterpret_cast<char*>(&actor), sizeof(Actor));
        }
        file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    }
    temp.close();
    file.close();
    if (remove("Actor.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "Actor.dat") != 0)
    {
        cout << "file do not rename";
    }
}

void Actor::deleted()
{
    Actor actor;
    char str[40];
    cout << "Введіть номер телефона для видалення: ";
    cin >> str;
    ifstream file;
    file.open("Actor.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    while (!file.eof())
    {

        if (0 != strcmp(str, actor.phone))
        {
            temp.write(reinterpret_cast<char*>(&actor), sizeof(Actor));
        }

        else
        {
            cout << "\nЗапис видалено\n";
        }
        file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    }
    temp.close();
    file.close();
    if (remove("Actor.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "Actor.dat") != 0)
    {
        cout << "file do not rename";
    }
}