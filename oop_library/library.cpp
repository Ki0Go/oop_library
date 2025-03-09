#include "library.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

int Library::totalIssuedBooks = 0;
unordered_map<string, pair<Book, Library*>> Library::issuedBooks;

Library::Library() : Library("Nn libr") {}

Library::Library(string n) : name(n) {
    books.reserve(10);
}

Library::Library(const Library& other) : name(other.name), books(other.books) {
    cout << "Copy Constructor: Library " << name << endl;
}

Library::Library(Library&& other) noexcept : name(move(other.name)), books(move(other.books)) {
    cout << "Move Constructor: Library " << name << endl;
}

Library& Library::operator=(const Library& other) {
    if (this != &other) {
        name = other.name;
        books = other.books;
    }
    return *this;
}

Library& Library::operator=(Library&& other) noexcept {
    if (this != &other) {
        name = move(other.name);
        books = move(other.books);
    }
    return *this;
}

Library::~Library() {
    cout << "Destructor: " << name << endl;
    issuedBooks.clear();
}

void Library::display() const {
    cout << "Library Name: " << name << ", Number of Books: " << books.size() << endl;
}

void Library::addBook(Book&& book) {
    books.push_back(move(book));
    cout << "Book added: " << books.back().getTitle() << " by " << books.back().getAuthor() << endl;
}

void Library::issueBook(const string& title, const string& readerName) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            cout << "Book issued: " << title << " to " << readerName << endl;
            issuedBooks[title] = { move(*it), this };
            books.erase(it);
            totalIssuedBooks++;
            return;
        }
    }
    cout << "Book not found: " << title << endl;
}

void Library::returnBook(const string& title) {
    auto it = issuedBooks.find(title);
    if (it != issuedBooks.end()) {
        Library* lib = it->second.second;
        lib->books.push_back(move(it->second.first));
        cout << "Book returned to " << lib->name << ": " << title << endl;
        issuedBooks.erase(it);
        totalIssuedBooks--;
    }
    else {
        cout << "Book not found in issued books list: " << title << endl;
    }
}

void Library::displayIssuedBooks() {
    cout << "Total issued books: " << totalIssuedBooks << endl;
    if (issuedBooks.empty()) {
        cout << "No books currently issued." << endl;
        return;
    }
    cout << "Issued Books List:" << endl;
    for (const auto& entry : issuedBooks) {
        cout << "- " << entry.first << " (From: " << entry.second.second->name << ")" << endl;
    }
}
