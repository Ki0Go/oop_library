#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

class Book {
private:
	string title;
	string author;
	int year;
public:
	Book()
		: Book{ "Unknown", "Unknown", 0 } {}

	Book(string t, string a, int y)
		: title{ t }, author{ a }, year{ y } {}

	Book(const Book& other)
		: title(other.title), author(other.author), year(other.year) {
		cout << "Copy Constructor: " << title << endl;
	}

	Book(Book&& other) noexcept
		: title(move(other.title)), author(move(other.author)), year(other.year) {
		cout << "Move Constructor: " << title << endl;
	}

	Book& operator=(const Book& other) {
		if (this != &other) {
			this->title = other.title;
			this->author = other.author;
			this->year = other.year;
		}
		return *this;
	}

	Book& operator=(Book&& other) noexcept {
		if (this != &other) {
			this->title = move(other.title);
			this->author = move(other.author);
			this->year = other.year;
		}
		return *this;
	}

	~Book() {
		if (!title.empty()) {
			cout << "Destructor: " << title << endl;
		}
		else {
			cout << "Destructor: [Moved book]" << endl;
		}
	}

	const string& getTitle() const {
		return title;
	}
	const string& getAuthor() const {
		return author;
	}
	int getYear() const {
		return year;
	}
	friend ostream& operator<<(ostream& os, const Book& b) {
		os << "Book[Title: " << b.title << ", Author: " << b.author << ", Year: " << b.year << "]";
		return os;
	}
	friend istream& operator>>(istream& is, Book& b) {
		cout << "Enter title: ";
		getline(is, b.title);
		cout << "Enter author: ";
		getline(is, b.author);
		cout << "Enter year: ";
		while (!(is >> b.year) || b.year < 0) {
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Enter a valid year: ";
		}
		is.ignore();
		return is;
	}
};

class Reader {
protected:
	string name;
	int age;
public:
	Reader(string n, int a)
		: name(n), age(a) {}

	Reader(const Reader& other)
		: name(other.name), age(other.age) {
		cout << "Copy Constructor: " << name << endl;
	}

	Reader(Reader&& other) noexcept
		: name(move(other.name)), age(other.age) {
		cout << "Move Constructor: " << name << endl;
	}

	Reader& operator=(const Reader& other) {
		if (this != &other) {
			this->name = other.name;
			this->age = other.age;
		}
		return *this;
	}

	Reader& operator=(Reader&& other) noexcept {
		if (this != &other) {
			this->name = move(other.name);
			this->age = other.age;
		}
		return *this;
	}

	virtual ~Reader() {
		cout << "Destructor: " << name << endl;
	}

	const string& getName() const {
		return name;
	}
	int getAge() const {
		return age;
	}
	virtual void display() const = 0;
};

class ChildReader : public Reader {
public:
	ChildReader(string n, int a)
		: Reader(n, a) {}

	void display() const override {
		cout << "ChildReader[Name: " << name << ", Age: " << age << "]" << endl;
	}
};

class AdultReader : public Reader {
public:
	AdultReader(string n, int a)
		: Reader(n, a) {}

	void display() const override {
		cout << "AdultReader[Name: " << name << ", Age: " << age << "]" << endl;
	}
};

class ReaderFactory {
public:
	static unique_ptr<Reader> createReader(const string& name, int age) {
		if (age < 18) {
			return make_unique<ChildReader>(name, age);
		}
		else {
			return make_unique<AdultReader>(name, age);
		}
	}
};

class Library {
private:
	string name;
	vector<Book> books;
	static int totalIssuedBooks;
	static unordered_map<string, pair<Book, Library*>> issuedBooks;
public:
	Library();
	Library(string n);
	Library(const Library& other);
	Library(Library&& other) noexcept;
	Library& operator=(const Library& other);
	Library& operator=(Library&& other) noexcept;
	~Library();

	void display() const;
	void addBook(Book&& book);
	void issueBook(const string& title, const string& readerName);
	void returnBook(const string& title);
	void displayIssuedBooks();
};


