#include "Play.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int Play::setId()
{
    int tempId;
    string str;
    fstream idfile;
    idfile.open("id.txt", fstream::out | fstream::in);
    ifstream temp;
    while (!idfile.eof())
    {
        getline(idfile, str);
        tempId = atoi(str.c_str());
    }
    ++tempId;
    idfile.close();
    idfile.open("id.txt", fstream::out | fstream::in);
    idfile << tempId;
    idfile.close();
    return tempId;
}

void Play::create()
{
    cin.ignore(10, '\n');
    cout << "\nНазва п'єси: "; cin >> name;
    cout << "Жанр: "; cin >> ganre;
    cout << "Письменник: "; cin >> writer;
    cout << "Опис: "; cin >> description;
    id=setId();
}

int Play::count()
{
    ifstream ifile;
    ifile.open("Play.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    int v = (int)ifile.tellg() / sizeof(Play);
    return v;
    ifile.close();
}


void Play::showData()
{
    cout << "id: " << id << endl;
    cout << "Назва п'єси: " << name << endl;
    cout << "Жанр: " << ganre << endl;
    cout << "Письменник: " << writer << endl;
    cout << "Опис: " << description << endl;
}

void Play::write()
{
    Play play;
    ofstream ofile;
    ofile.open("Play.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

void Play::read(int p)
{
    Play play;
    ifstream ifile;
    ifile.open("Play.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(p * sizeof(Play));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}


int Play::search(int variant)
{
    if (variant == 0)
        return 0;
    Play play;
    ifstream ifile;
    char str[40];
    ifile.open("Play.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "Введіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(Play));
        ifile.read(reinterpret_cast<char*>(&play), sizeof(Play));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, play.name))
            {
                play.showData();
                cout << endl;
            }
            break;

        case 2:
            if (0 == strcmp(str, play.ganre))
            {
                play.showData();
                cout << endl;
            }
            break;
        case 3:
            if (0 == strcmp(str, play.writer))
            {
                play.showData();
                cout << endl;
            }
            break;
        case 4:
            if (0 == strcmp(str, play.description))
            {
                play.showData();
                cout << endl;
            }
            break;
        case 5:
            if (atoi(str) == play.id)
            {
                play.showData();
                cout << endl;
            }
            break;
        default:
            break;
        }
    }
    ifile.close();
}



void Play::edit()
{
    Play play;
    int str;
    cout << "Введіть id для редагування: ";
    cin >> str;
    ifstream file;
    file.open("Play.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&play), sizeof(Play));
    while (!file.eof())
    {

        if (str != play.id)
        {
            temp.write(reinterpret_cast<char*>(&play), sizeof(Play));
        }

        else
        {
            play.create();
            temp.write(reinterpret_cast<char*>(&play), sizeof(Play));
        }
        file.read(reinterpret_cast<char*>(&play), sizeof(Play));
    }
    temp.close();
    file.close();
    if (remove("Play.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "Play.dat") != 0)
    {
        cout << "file do not rename";
    }
}

void Play::deleted()
{
    Play play;
    int str;
    cout << "Введіть id для видалення: ";
    cin >> str;
    ifstream file;
    file.open("Play.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&play), sizeof(Play));
    while (!file.eof())
    {

        if (str != play.id)
        {
            temp.write(reinterpret_cast<char*>(&play), sizeof(Play));
        }

        else
        {
            cout << "\nЗапис видалено\n";
        }
        file.read(reinterpret_cast<char*>(&play), sizeof(Play));
    }
    temp.close();
    file.close();
    if (remove("Play.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "Play.dat") != 0)
    {
        cout << "file do not rename";
    }
}

