#include "Actor.h"
#include <iostream>
#include <fstream>
using namespace std;
void Actor::create()
{
    cin.ignore(10, '\n');
    cout << "\nІм'я: "; cin >> name;
    cout << "Прізвище: "; cin >> surname;
    cout << "По батькові: "; cin >> patronymic;
    cout << "Дата народження: "; cin >> dateOfBirth;
    setSex();
    setId(count());
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
    if (sex == 1)
        cout << "чоловіча";
    else
        cout << "жіноча";
}
void Actor::showData()
{
    cout << "ID: " << id << endl;
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
    return (int)ifile.tellg() / sizeof(Actor);
    ifile.close();
}

void Actor::setId(int n)
{
    if (n < 1000)
        id = 1;
    else
        id = n + 1;
}