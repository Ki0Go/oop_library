#include "library.h"
#include <iostream>
#include <memory>

using namespace std;

void printReader(const Reader& r) {
    r.display();
}

int main() {
    Library library1("City Library");
    Library library2("University Library");

    /*Book book1;
    cin >> book1;*/
    Book book1("book_name1", "book1_author", 1234);
    Book book2("book_name2", "book2_author", 1960);
    Book book3("book_name3", "book3_author", 1851);
    Book book4("book_name4", "book4_author", 1925);
    Book book5("book_name5", "book5_author", 1813);

    cout << book1 << endl;
    cout << book2 << endl;
    cout << book3 << endl;
    cout << book4 << endl;
    cout << book5 << endl;
    book1.print();

    cout << "============================================" << endl;

    library1.addBook(move(book1));
    library1.addBook(move(book2));
    library2.addBook(move(book3));
    library2.addBook(move(book4));
    library2.addBook(move(book5));


    cout << "============================================" << endl;

    library1.display();
    library2.display();

    cout << "============================================" << endl;

    auto reader1 = ReaderFactory::createReader("Alice", 15);
    auto reader2 = ReaderFactory::createReader("Bob", 25);
 
    reader1->display();
    reader2->display();
    /*printReader(*reader1);
    printReader(*reader2);*/

    cout << "============================================" << endl;

    library1.issueBook("book_name1", reader1->getName());
    library1.issueBook("book_name2", reader2->getName());
    library2.issueBook("book_name3", reader1->getName());
    library2.issueBook("book_name4", reader2->getName());
    library2.issueBook("book_name1", reader1->getName());

    cout << "============================================" << endl;

    library1.displayIssuedBooks();

    cout << "============================================" << endl;

    library1.returnBook("book_name1");
    library1.returnBook("book_name2");
    library2.returnBook("book_name3");
    library2.returnBook("book_name4");
    library2.returnBook("book_name1");

    cout << "============================================" << endl;

    library1.display();
    library2.display();

    cout << "============================================" << endl;
    return 0;
}
