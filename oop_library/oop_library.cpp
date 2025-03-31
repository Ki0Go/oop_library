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
        cout << "������� ��� ����������� �����: " << e.what() << endl;
    }

    string currentUser;
    cout << "������ ���� ������� �� �������: ";
    getline(cin, currentUser);

    int mainChoice;
    string adminPassword = "0", inputPassword;

    while (true) {
        cout << "\n=== ������� ���� ===\n";
        cout << "1. �����������\n";
        cout << "2. ����������\n";
        cout << "3. �����\n";
        cout << "��� ����: ";
        cin >> mainChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (mainChoice) {
        case 1: {
            cout << "������ ������: ";
            getline(cin, inputPassword);
            if (inputPassword != adminPassword) {
                cout << "������������ ������.\n";
                break;
            }

            int adminChoice, libChoice;
            Library* selectedLib;

            cout << "������� ��������:\n1. City Library\n2. University Library\n��� ����: ";
            cin >> libChoice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            selectedLib = (libChoice == 1) ? &cityLibrary : &universityLibrary;

            do {
                cout << "\n--- ����������� (" << selectedLib->getName() << ") ---\n"
                    << "1. ������ �����\n"
                    << "2. �������� �����\n"
                    << "3. ����� �����\n"
                    << "4. ��������� �����\n"
                    << "5. ����������� ������ ����\n"
                    << "6. ����������� ����� �����\n"
                    << "7. �����\n"
                    << "��� ����: ";

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
                        cout << "�������: " << e.what() << endl;
                    }
                    break;
                }
                case 2:
                    cout << "����� �����: ";
                    getline(cin, title);
                    selectedLib->removeBook(title);
                    break;
                case 3:
                    cout << "����� �����: ";
                    getline(cin, title);
                    try {
                        selectedLib->issueBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "�������: " << e.what() << endl;
                    }
                    break;
                case 4:
                    cout << "����� �����: ";
                    getline(cin, title);
                    try {
                        selectedLib->returnBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "�������: " << e.what() << endl;
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

            cout << "������� ��������:\n1. City Library\n2. University Library\n��� ����: ";
            cin >> libChoice;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            selectedLib = (libChoice == 1) ? &cityLibrary : &universityLibrary;

            do {
                cout << "\n--- ���������� (" << selectedLib->getName() << ") ---\n"
                    << "1. ����� �����\n"
                    << "2. ��������� �����\n"
                    << "3. ����������� ������ ����\n"
                    << "4. �����\n"
                    << "��� ����: ";
                cin >> userChoice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                string title;
                switch (userChoice) {
                case 1:
                    cout << "����� �����: ";
                    getline(cin, title);
                    try {
                        selectedLib->issueBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "�������: " << e.what() << endl;
                    }
                    break;
                case 2:
                    cout << "����� �����: ";
                    getline(cin, title);
                    try {
                        selectedLib->returnBook(title, currentUser);
                    }
                    catch (const exception& e) {
                        cout << "�������: " << e.what() << endl;
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

            cout << "�� ���������!\n";
            return 0;
        }
    }
}
