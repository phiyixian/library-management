#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>
#include <vector>

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

    //member + librarian
    bool borrowBook();
    bool returnBook();
    void checkBorrowed();

    //librarian only features;
    bool addBook();
    bool removeBook();
    bool registerMember();
    bool removeMember();

    double calculateFine();
};

#endif