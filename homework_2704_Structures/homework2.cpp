#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

struct man
{
    char* name;
    char* surname;
    char* bDay;
    int age;
};

void init(man& person)
{
    char buff[100];

    cout << "\nEnter name: ";
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = 0;
    person.name = new char[30];
    strncpy(person.name, buff, strlen(buff) + 1);

    cout << "Enter surname: ";
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = 0;
    person.surname = new char[30];
    strncpy(person.surname, buff, strlen(buff) + 1);

    cout << "Enter birthday (DD-MM-YYYY): ";
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = 0;
    person.bDay = new char[20];
    strncpy(person.bDay, buff, strlen(buff) + 1);

    cout << "Enter age: ";
    cin >> person.age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void print(man& person)
{
    cout << "\nName:\t\t" << person.name << endl;
    cout << "Surname:\t" << person.surname << endl;
    cout << "Date of birth:\t" << person.bDay << endl;
    cout << "Age:\t\t" << person.age << endl;
}

void deleteMem(man& person)
{
    delete[] person.name;
    delete[] person.surname;
    delete[] person.bDay;
}

// Функция редактирования записи
void edit(man* peoples, int peopleAmount)
{
    int index;
    // Считаем кол-во индексов (людей), отображаем
    cout << "Enter index of the person you want to edit (from 0 to " << peopleAmount - 1 << " ): ";
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем символ конца строки, дабы не забивать след ввод

    // Небольшая проверка, если индекс вне числа людей
    if (index < 0 || index >= peopleAmount)
    {
        cout << "Invalid index!\n";
        return;
    }

    // 
    man& person = peoples[index];
    int choice;
    char buff[100];

    cout << "Enter parameter you want to edit: \n";
    cout << "1. Name\n";
    cout << "2. Surname\n";
    cout << "3. Date of birth\n";
    cout << "4. Age\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Тут все по классике, исходя из выбора - решаем что будем менять
    switch (choice)
    {
    case 1:
        cout << "Enter new name: ";
        fgets(buff, sizeof(buff), stdin); // запрашиваем ввод 
        buff[strcspn(buff, "\n")] = 0; // удаляем символ конца строки
        delete[] person.name; // очищаем память (прошлую запись)
        person.name = new char[strlen(buff) + 1]; // выделяем память под ввод строки + 1 для нуль терминатора
        strncpy(person.name, buff, strlen(buff) + 1); // копируем ввод через функцию
        break; // выходим из кейса
    case 2:
        cout << "Enter new surname: ";
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;
        delete[] person.surname;
        person.surname = new char[strlen(buff) + 1];
        strncpy(person.surname, buff, strlen(buff) + 1);
        break;
    case 3:
        cout << "Enter new date of birth: ";
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;
        delete[] person.bDay;
        person.bDay = new char[strlen(buff) + 1];
        strncpy(person.bDay, buff, strlen(buff) + 1);
        break;
    case 4:
        cout << "Enter new age: ";
        cin >> person.age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    default:
        cout << "Invalid chocie!\n";
    }
}

// Функция поиска по имени или фамилии
void searchByNameAndSurname(man* peoples, int peopleAmount)
{
    char searchSurname[30], searchName[30];

    cout << "Enter surname to search: ";
    cin.getline(searchSurname, 30);
    cout << "Enter name to search: ";
    cin.getline(searchName, 30);

    bool found = false; // флаг для отслеживания хотя бы одного совпадения

    for (int i = 0; i < peopleAmount; i++)
    {
        // Сравнение имени и фамилии с уже введенными данными
        if (strcmp(peoples[i].surname, searchSurname) == 0 && strcmp(peoples[i].name, searchName) == 0)
        {
            cout << "\nFound person: \n";
            print(peoples[i]);
            cout << "========================\n";
            found = true;
        }
    }
    if (!found)
    {
        cout << "\nNo person found with a given name and surname\n";
    }
}

// Функция добавления человека
man* addPerson(man* peoples, int& peopleAmount)
{
    man* newPeoples = new man[peopleAmount + 1]; // создаем новый массив на 1 человека больше

    for (int i = 0; i < peopleAmount; i++)
    {
        newPeoples[i] = peoples[i]; // копирование существующих данных в новый массив
    }

    init(newPeoples[peopleAmount]); // инициализация новой записи

    delete[] peoples;
    peopleAmount++;
    return newPeoples;
}

// Функция удаления человека
man* deletePerson(man* peoples, int& peopleAmount, int index)
{
    if (index < 0 || index >= peopleAmount)
    {
        cout << "Invalid index!\n";
        return peoples;
    }

    man* newPeoples = new man[peopleAmount - 1]; // создаем массив на одного человека меньше

    for (int i = 0, j = 0; i < peopleAmount; i++)
    {
        if (i != index)
        {
            newPeoples[j++] = peoples[i]; // Копирование всех кроме удаляемого
        }
    }

    delete[] peoples;
    peopleAmount--;
    return newPeoples;
}

// Функция вывода именинников месяца
void printBirthdays(man* peoples, int peopleAmount, const string& month) {
    bool found = false;  // Флаг для проверки наличия именинников
    for (int i = 0; i < peopleAmount; i++) {
        string bDay = peoples[i].bDay;
        if (bDay.length() >= 5) {
            string birthMonth = bDay.substr(3, 2); // Извлекаем месяц из строки даты
            if (birthMonth == month) {
                cout << peoples[i].surname << " " << peoples[i].name << " - " << peoples[i].bDay << endl;
                found = true;
            }
        }
    }
    if (!found) {
        cout << "No birthday found for month " << month << ".\n";
    }
}

// Функция сортировки по имени или фамилии
void sortPeoples(man* peoples, int peopleAmount, bool sortBySurname)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < peopleAmount - 1; i++)
        {
            if (sortBySurname)
            {
                if (strcmp(peoples[i].surname, peoples[i + 1].surname) > 0)
                {
                    swap(peoples[i], peoples[i + 1]);
                    swapped = true;
                }
            }
            else {
                if (strcmp(peoples[i].name, peoples[i + 1].name) > 0)
                {
                    swap(peoples[i], peoples[i + 1]);
                    swapped = true;
                }
            }
        }
    } while (swapped);
}

// Функция для обмена значениями двух объектов man
void swap(man& a, man& b)
{
    man temp = a;
    a = b;
    b = temp;
}


int main()
{
    int peopleAmount;
    cout << "Enter people amount: ";
    cin >> peopleAmount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Выделяем память под кол-во людей
    man* peoples = new man[peopleAmount];

    // Инициализируем через цикл
    for (int i = 0; i < peopleAmount; i++)
    {
        init(peoples[i]);
    }

    // ============
    // Тк функций получается много, делаем свитч кейсы
    bool done = false;

    while (!done)
    {
        char actionChoise;
        cout << "Chose preferred option:\n";
        cout << "'e' or 'E' to edit someone's data:\n";
        cout << "'s' or 'S' to search someone:\n";
        cout << "'a' or 'A' to add person:\n";
        cout << "'r' or 'R' to remove person:\n";
        cout << "'b' or 'B' to show birthday:\n";
        cout << "'o' or 'O' to sort by name or surname:\n";
        cout << "'q' or 'Q' to continue\n";
        cout << "Make your choice: ";
        cin >> actionChoise;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (actionChoise)
        {
        case 'e': case 'E':
            edit(peoples, peopleAmount);
            break;
        case 's': case 'S':
            searchByNameAndSurname(peoples, peopleAmount);
            break;
        case 'a': case 'A':
            peoples = addPerson(peoples, peopleAmount);
            break;
        case 'r': case 'R': {
            int index;
            cout << "Enter index to remove: ";
            cin >> index;
            peoples = deletePerson(peoples, peopleAmount, index);
            break;
        }
        case 'b': case 'B': {
            string month;
            cout << "Enter MM month to list birthdays: ";
            cin >> month;
            printBirthdays(peoples, peopleAmount, month);
            break;
        }
        case 'o': case 'O': {
            char sortChoice;
            cout << "Sort by (n)ame or (s)urname? ";
            cin >> sortChoice;
            sortPeoples(peoples, peopleAmount, sortChoice == 's' || sortChoice == 'S');
            for (int i = 0; i < peopleAmount; i++) {
                print(peoples[i]);
            }
            break;
        }
        case 'q': case 'Q':
            done = true;
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }
    // ============

    // Выводим через цикл
    cout << "\n========================\n";
    cout << "All peoples:\n";
    for (int i = 0; i < peopleAmount; i++)
    {
        print(peoples[i]);
    }

    // Чистим память через цикл
    for (int i = 0; i < peopleAmount; i++)
    {
        deleteMem(peoples[i]);
    }
    delete[] peoples;

    return 0;
}