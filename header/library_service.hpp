#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>
#include <vector>
#include "member.hpp"
#include "librarian.hpp"

//temp book file 
struct Book
{
    std::string id;
    std::string title;
    std::string author;
    std::string genre;
    bool is_borrowed;
};

class LibraryService
{
    private:
    std::vector<Book> books; //temp
    
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
};

#endif