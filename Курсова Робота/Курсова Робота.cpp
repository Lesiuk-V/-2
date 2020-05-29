#include "Play.h"
#include "Actor.h"
#include "windows.h"
#include <iostream>
using namespace std;
void print_menu() {
    system("cls");
    cout << "          Театр\n" << endl;
    cout << "1.  Додати актора" << endl;
    cout << "2.  Переглянути акторів" << endl;
    cout << "3.  Пошук акторів" << endl;
    cout << "4.  Редугування даних актора" << endl;
    cout << "5.  Видалення актора" << endl << endl;

    cout << "6.  Додати п'єсу" << endl;
    cout << "7.  Переглянути п'єси" << endl;
    cout << "8.  Пошук п'єс" << endl;
    cout << "9.  Редагування даних п'єси" << endl;
    cout << "10. Видалення п'єси" << endl;
    cout << "11. Вихід" << endl;
    cout << ">";
}

void printSearchActorMenu()
{
    cout << "Пошук за полем: \n";
    cout << "1. Ім'я" << endl;
    cout << "2. Прізвище" << endl;
    cout << "3. По батькові" << endl;
    cout << "4. Дата народження" << endl;
    cout << "5. Стать(чоловік(0), жінка(1)" << endl;
    cout << "6. id" << endl;
}

void printSearchPlayMenu()
{
    cout << "Пошук за полем: \n";
    cout << "1. Назва п'єси" << endl;
    cout << "2. Жанр" << endl;
    cout << "3. Письменник" << endl;
    cout << "4. Опис" << endl;
    cout << "6. id" << endl;
}

int get_variant(int max) {
    double input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
            if (input > 0 && input < max)
                return input;
            else
            {
                valid = false;
                cout << "Помилка вводу. Введіть ще раз" << endl;
            }
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
int main()
{
    system("chcp 1251>nul");
    int variant;
    string str;
    Actor actor;
    Play play;
    int n;
    do {
        print_menu();
        char ch;
        variant = get_variant(11);
        switch (variant) {
        case 1: 
            do
            {   
                cout << "Введіть дані актора: ";
                actor.create();
                actor.write();
                cout << "Продовжити ввід?(т/н)?";
                cin >> ch;
            } while (ch == 'т');
            break;

        case 2:
            n = Actor::count();
            cout << "У файлі " << n << " акторів\n";
            for (int j = 1; j < n + 1; j++)
            {
                cout << "\n Актор " << j << endl;
                actor.read(j-1);
                actor.showData();
                cout << endl;
            }
            cout << endl;
            break;

        case 3:
            do
            {
                printSearchActorMenu();
                variant = get_variant(7);
                actor.search(variant);
                break;
                system("pause");
            } while (variant != 8);
            break;
            break;
        case 4:
            //play.setId();
            actor.edit();
            break;
        case 5:
            actor.deleted();
            break;
        case 6:
            do
            {
                cout << "Введіть дані п'єси: ";
                play.create();
                play.write();
                cout << "Продовжити ввід?(т/н)?";
                cin >> ch;
            } while (ch == 'т');
            break;
        case 7:
          
            n = Play::count();
            cout << "У файлі " << n << " п'єс\n";
            for (int j = 1; j < n + 1; j++)
            {
                cout << "\n П'єса " << j << endl;
                play.read(j - 1);
                play.showData();
                cout << endl;
            }
            cout << endl;
            break;
        case 8:
            
            do
            {
                printSearchActorMenu();
                variant = get_variant(7);
                play.search(variant);
                break;
                system("pause");
            } while (variant != 8);
            break;
        case 9:
            play.edit();
            break;
        case 10:
            play.deleted();
            break;
        default:
            cout << "Неправильнний ввід. Спробуйте ще раз";
            break;
        }
        if (variant != 11)
            system("pause");
    } while (variant != 11);
    return 0;
}
