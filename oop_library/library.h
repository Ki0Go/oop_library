#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <Windows.h>

#undef max
#undef min

using namespace std;

class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() = default;
};

class Book : public Printable {
private:
    string title;
    string author;
    int year;

public:
    Book(string t = "Unknown", string a = "Unknown", int y = 0)
        : title(t), author(a), year(y) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    void display() const {
        cout << "Назва: " << title << ", Автор: " << author << ", Рік: " << year << endl;
    }

    void print() const override {
        display();
    }

    friend istream& operator>>(istream& is, Book& b) {
        cout << "Назва: ";
        getline(is, b.title);
        cout << "Автор: ";
        getline(is, b.author);
        cout << "Рік: ";
        is >> b.year;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        if (b.year < 0 || b.year > 2100) {
            throw runtime_error("Недопустиме значення року: " + to_string(b.year));
        }

        return is;
    }
};

class Library {
private:
    string name;
    vector<Book> books;
    unordered_map<string, pair<Book, string>> issuedBooks;

    void logHistory(const string& user, const string& action, const string& bookTitle) const {
        ofstream history("history.txt", ios::app);
        time_t now = time(0);
        tm* dt = localtime(&now);
        char timeString[20];
        strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", dt);
        history << timeString << " | " << user << " | " << action << " | " << bookTitle << endl;
    }

public:
    Library(string n = "Library") : name(n) {
        books.reserve(20);
    }

    string getName() const {
        return name;
    }

    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Книгу \"" << book.getTitle() << "\" додано до бібліотеки.\n";
    }

    void removeBook(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) {
            return b.getTitle() == title;
            });
        if (it != books.end()) {
            books.erase(it);
            cout << "Книгу \"" << title << "\" видалено з бібліотеки.\n";
        }
        else {
            cout << "Книгу \"" << title << "\" не знайдено.\n";
        }
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "У бібліотеці \"" << name << "\" немає книг.\n";
            return;
        }
        cout << "Книги у бібліотеці \"" << name << "\":\n";
        for (const auto& book : books) {
            book.display();
        }
    }

    void displayIssuedBooks() const {
        if (issuedBooks.empty()) {
            cout << "Немає виданих книг у бібліотеці \"" << name << "\".\n";
            return;
        }
        cout << "Видані книги в бібліотеці \"" << name << "\":\n";
        for (const auto& pair : issuedBooks) {
            const auto& book = pair.second.first;
            const auto& reader = pair.second.second;
            cout << "\"" << book.getTitle() << "\" - читач: " << reader << endl;
        }
    }

    void issueBook(const string& title, const string& reader) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) {
            return b.getTitle() == title;
            });
        if (it != books.end()) {
            issuedBooks[title] = { *it, reader };
            books.erase(it);
            cout << "Книгу \"" << title << "\" видано читачеві \"" << reader << "\".\n";
            logHistory(reader, "взяв книгу", title);
        }
        else {
            throw runtime_error("Книга \"" + title + "\" не знайдена у бібліотеці.");
        }
    }

    void returnBook(const string& title, const string& reader) {
        auto it = issuedBooks.find(title);
        if (it != issuedBooks.end()) {
            books.push_back(it->second.first);
            issuedBooks.erase(it);
            cout << "Книгу \"" << title << "\" повернуто.\n";
            logHistory(reader, "повернув книгу", title);
        }
        else {
            throw runtime_error("Книга \"" + title + "\" не була видана або не знайдена.");
        }
    }

    void saveToFile() const {
        ofstream booksFile(name + "_books.txt");
        ofstream issuedFile(name + "_issued_books.txt");

        for (const auto& book : books) {
            booksFile << book.getTitle() << "|" << book.getAuthor() << "|" << book.getYear() << endl;
        }

        for (const auto& pair : issuedBooks) {
            const auto& book = pair.second.first;
            const auto& reader = pair.second.second;
            issuedFile << book.getTitle() << "|" << book.getAuthor() << "|" << book.getYear() << "|" << reader << endl;
        }
    }

    void loadFromFile() {
        books.clear();
        issuedBooks.clear();

        ifstream booksFile(name + "_books.txt");
        if (!booksFile.is_open())
            throw runtime_error("Не вдалося відкрити файл з книгами: " + name + "_books.txt");

        ifstream issuedFile(name + "_issued_books.txt");
        if (!issuedFile.is_open())
            throw runtime_error("Не вдалося відкрити файл з виданими книгами: " + name + "_issued_books.txt");
        string line;

        while (getline(booksFile, line)) {
            stringstream ss(line);
            string title, author, year;
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, year, '|');
            books.emplace_back(title, author, stoi(year));
        }

        while (getline(issuedFile, line)) {
            stringstream ss(line);
            string title, author, year, reader;
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, year, '|');
            getline(ss, reader, '|');

            issuedBooks[title] = { Book(title, author, stoi(year)), reader };
        }
    }
};
