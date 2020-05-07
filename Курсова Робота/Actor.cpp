#include "Actor.h"
#include <iostream>
#include <fstream>
using namespace std;
void Actor::create()
{
    cin.ignore(10, '\n');
    cout << "\n��'�: "; cin >> name;
    cout << "�������: "; cin >> surname;
    cout << "�� �������: "; cin >> patronymic;
    cout << "���� ����������: "; cin >> dateOfBirth;
    setSex();
    setId(count());
}

void Actor::setSex()
{
    int s;
    cout << "����� - ������(1), ����(2)\n";
    for (;;) {
        cin >> s;
        if (s != 1 &&
            s != 2) cout << "������������ ���! ��������� �� ���\n";

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
        cout << "�������";
    else
        cout << "�����";
}
void Actor::showData()
{
    cout << "ID: " << id << endl;
    cout << "��'�: " << name << endl;
    cout << "�������: " << surname << endl;
    cout << "�� �������: " << patronymic << endl;
    cout << "���� ����������: " << dateOfBirth << endl;
    cout << "�����: "; getSex(); cout << endl;
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