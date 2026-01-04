#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>
#include <vector>
#include "member.hpp"
#include "librarian.hpp"

    //    std::string title, bookID, category, dateAdded, lastUpdated, borrowCount, status;

//temp book file (or should we use a class)
struct Book
{
    std::string ISBN;
    std::string title;
    std::string author;
    std::string genre; // or category
    std::string dateAdded;
    std::string lastUpdated;
    int borrowCount;
    bool is_borrowed;
};

class LibraryService
{
    private:
    std::vector<Book> books; //temp
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