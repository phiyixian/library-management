#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>

class LibraryService
{
    public:
    void searchByTitle();
    void searchByAuthor();
    void searchByGenre();

    bool borrowBook();
    bool returnBook();

    //librarian only features;
    bool addBook();
    bool removeBook();
    bool registerMember();
    bool removeMember();

    double calculateFine();
};

#endif