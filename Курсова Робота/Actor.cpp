#include "Actor.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void Actor::create(int v)
{
    char number[12];
    cin.ignore(10, '\n');
    cout << "\nІм'я: "; cin >> name;
    cout << "Прізвище: "; cin >> surname;
    cout << "По батькові: "; cin >> patronymic;
    cout << "Дата народження: "; cin >> dateOfBirth;
    setSex();
    if (v == 0)
        id = setId();
    else id = v;
}

int Actor::valiidation()
{
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Помилка вводу. Введіть ще раз" << endl;
        }
    } while (!valid);
    return input;
}

void Actor::setSex()
{
    int s;
    cout << "Стать - чоловік(1), жінка(2)\n";
    for (;;) {
        s = valiidation();
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
    cout << "id: " << id << endl;
    cout << "Ім'я: " << name << endl;
    cout << "Прізвище: " << surname << endl;
    cout << "По батькові: " << patronymic << endl;
    cout << "Дата народження: " << dateOfBirth << endl;
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

int Actor::setId()
{
    int tempId;
    string str;
    fstream idfile;
    idfile.open("ActorId.txt", fstream::out | fstream::in);
    while (!idfile.eof())
    {
        getline(idfile, str);
        tempId = atoi(str.c_str());
    }
    ++tempId;
    idfile.close();
    idfile.open("ActorId.txt", fstream::out | fstream::in);
    idfile << tempId;
    idfile.close();
    return tempId;
}
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

            if (atoi(str)== actor.id)
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
    cout << "Введіть id для редагування: ";
    cin >> str;
    ifstream file;
    file.open("Actor.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    while (!file.eof())
    {

        if (atoi(str) != actor.id)
        {
            temp.write(reinterpret_cast<char*>(&actor), sizeof(Actor));
        }

        else
        {
            actor.create(actor.id);
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
    int str;
    cout << "Введіть id для видалення: ";
    cin >> str;
    ifstream file;
    file.open("Actor.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&actor), sizeof(Actor));
    while (!file.eof())
    {

        if (str != actor.id)
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