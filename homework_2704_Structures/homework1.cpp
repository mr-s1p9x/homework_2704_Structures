#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

struct student
{
    char* surname;
    char* group;
    int academicPerformance;
};

void init(student& obj)
{
    char buff[100]; // динамический буффер

    cout << "\nEnter surname: ";
    // Ввод фамилии 
    fgets(buff, sizeof(buff), stdin);
    // Очистка символа новой строки
    buff[strcspn(buff, "\n")] = 0;
    // Выделение памяти для объекта surname
    obj.surname = new char[30];
    // Копирование введенных данных
    strncpy(obj.surname, buff, strlen(buff) + 1);

    // Ввод группы
    cout << "Enter group [5 simbols]: ";
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = 0;
    obj.group = new char[7];
    strncpy(obj.group, buff, strlen(buff) + 1);

    // Ввод успеваемости
    cout << "Enter academic performance [1 - 5]: ";
    cin >> obj.academicPerformance;
    // Очистка буфера
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void print(student& obj)
{
    cout << "\nSurname:\t\t" << obj.surname << endl;
    cout << "Group:\t\t\t" << obj.group << endl;
    cout << "Academic Performance:\t" << obj.academicPerformance << endl;
}

void deleteMem(student& obj)
{
    delete[] obj.surname;
    delete[] obj.group;
}

int main()
{
    int studentCount;
    cout << "Enter students amount: ";
    cin >> studentCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    student* students = new student[studentCount];

    // Инициализация
    for (int i = 0; i < studentCount; i++)
    {
        init(students[i]);
    }

    // Вывод студентов
    cout << "==========================\n";
    cout << "All students:\n";
    for (int i = 0; i < studentCount; i++)
    {
        print(students[i]);
    }

    // Вывод отличников
    cout << "\n\n==========================\n";
    cout << "Excellent students:\n";
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].academicPerformance >= 4)
        {
            cout << "Surname:\t\t" << students[i].surname << endl;
            cout << "Group:\t\t\t" << students[i].group << endl;
            cout << "Academic Performance:\t" << students[i].academicPerformance << endl;
        }
        cout << endl;
    }

    // Вывод двоечников
    cout << "==========================\n";
    cout << "Failing students:";
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].academicPerformance <= 3)
        {
            cout << "Surname:\t\t" << students[i].surname << endl;
            cout << "Group:\t\t\t" << students[i].group << endl;
            cout << "Academic Performance:\t" << students[i].academicPerformance << endl;
        }
        cout << endl;
    }

    // Очистка памяти
    for (int i = 0; i < studentCount; i++)
    {
        deleteMem(students[i]);
    }
    delete[] students;

    return 0;
}