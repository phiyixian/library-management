#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>
#include <vector>
#include "borrow_records.hpp"
#include "books.hpp"

// Forward declarations to avoid circular dependency
class Member;
class Librarian;

class LibraryService
{
    private:
    BookList books; // Linked list of books loaded from database
    // the list that stores all members and librarians should also be added here
    
    public:
    LibraryService(); //temp

    // guest + member + librarian
    void searchByTitle();
    void searchByAuthor();
    void searchByGenre();
    void displayCatalogue();

    //member + librarian
    bool borrowBook(Member &);
    bool returnBook(linkedRecords &borrowlist, Member &user);
    bool returnBook(Member &);
    void checkBorrowed();

    //librarian only features;
    bool addBook();
    bool removeBook();
    bool registerMember();
    bool removeMember();

    double calculateFine();
    double payFine(double, Member &);
    double payFine(double, Librarian &);

    // Helper functions
    void loadBooksFromFile();
    void saveBooksToFile();
    void loadPeopleFromFile();
    void savePeopleToFile();
};

#endif
