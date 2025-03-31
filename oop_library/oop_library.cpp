#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <Windows.h>
#include <ctime>
#include <limits>
#include "library.h"

#undef max
#undef min

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Library cityLibrary("City Library");
    Library universityLibrary("University Library");

    try {
        cityLibrary.loadFromFile();
        universityLibrary.loadFromFile();
    }
    catch (const exception& e) {
        cout << "Помилка при завантаженні файлів: " << e.what() << endl;
    }

    string currentUser;
    cout << "Введіть ваше прізвище та ініціали: ";
    getline(cin, currentUser);

    int mainChoice;
    string adminPassword = "0", inputPassword;

    while (true) {
        cout << "\n=== Головне меню ===\n";
        cout << "1. Адміністратор\n";
        cout << "2. Користувач\n";
        cout << "3. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> mainChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (mainChoice) {
        case 1: {
            cout << "Введіть пароль: ";
            getline(cin, inputPassword);
            if (inputPassword != adminPassword) {
                cout << "Неправильний пароль.\n";
                break;
            }

            int adminChoice, libChoice;
            Library* selectedLib;

            cout << "Виберіть бібліотеку:\n1. City Library\n2. University Library\nВаш вибір: ";
            cin >> libChoice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            selectedLib = (libChoice == 1) ? &cityLibrary : &universityLibrary;

            do {
                cout << "\n--- Адміністратор (" << selectedLib->getName() << ") ---\n"
                    << "1. Додати книгу\n"
                    << "2. Видалити книгу\n"
                    << "3. Взяти книгу\n"
                    << "4. Повернути книгу\n"
                    << "5. Переглянути список книг\n"
                    << "6. Переглянути видані книги\n"
                    << "7. Назад\n"
                    << "Ваш вибір: ";

                cin >> adminChoice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                string title;
                switch (adminChoice) {
                case 1: {
                    Book b;
                    cin >> b;
                    try {
                        selectedLib->addBook(b);
                    }
                    catch (const exception& e) {
                        cout << "Помилка: " << e.what() << endl;
                    }
                    break;
                }
                case 2:
                    cout << "Назва книги: ";
                    getline(cin, title);
                    selectedLib->removeBook(title);
                    break;
                case 3:
                    cout << "Назва книги: ";
                    getline(cin, title);
                    try {
                        selectedLib->issueBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "Помилка: " << e.what() << endl;
                    }
                    break;
                case 4:
                    cout << "Назва книги: ";
                    getline(cin, title);
                    try {
                        selectedLib->returnBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "Помилка: " << e.what() << endl;
                    }
                    break;
                case 5:
                    selectedLib->displayBooks();
                    break;
                case 6:
                    selectedLib->displayIssuedBooks();
                    break;
                }
            } while (adminChoice != 7);
            break;
        }
        case 2: {
            int userChoice, libChoice;
            Library* selectedLib;

            cout << "Виберіть бібліотеку:\n1. City Library\n2. University Library\nВаш вибір: ";
            cin >> libChoice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            selectedLib = (libChoice == 1) ? &cityLibrary : &universityLibrary;

            do {
                cout << "\n--- Користувач (" << selectedLib->getName() << ") ---\n"
                    << "1. Взяти книгу\n"
                    << "2. Повернути книгу\n"
                    << "3. Переглянути список книг\n"
                    << "4. Назад\n"
                    << "Ваш вибір: ";
                cin >> userChoice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                string title;
                switch (userChoice) {
                case 1:
                    cout << "Назва книги: ";
                    getline(cin, title);
                    try {
                        selectedLib->issueBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "Помилка: " << e.what() << endl;
                    }
                    break;
                case 2:
                    cout << "Назва книги: ";
                    getline(cin, title);
                    try {
                        selectedLib->returnBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "Помилка: " << e.what() << endl;
                    }
                    break;
                case 3:
                    selectedLib->displayBooks();
                    break;
                }
            } while (userChoice != 4);
            break;
        }
        case 3:
            cityLibrary.saveToFile();
            universityLibrary.saveToFile();

            cout << "До побачення!\n";
            return 0;
        }
    }
}
