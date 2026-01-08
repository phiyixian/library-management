#ifndef LIBRARY_SERVICE_HPP
#define LIBRARY_SERVICE_HPP

#include <string>
#include <vector>
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream

//temp book file 
struct Book
{
    std::string id;
    std::string title;
    std::string author;
    std::string genre;
    bool is_borrowed;
};
=======
#include "borrow_records.hpp"
#include "books.hpp"

// Forward declarations to avoid circular dependency
class Member;
class Librarian;
>>>>>>> Stashed changes
=======
#include "borrow_records.hpp"
#include "books.hpp"

// Forward declarations to avoid circular dependency
class Member;
class Librarian;
>>>>>>> Stashed changes
=======
#include "borrow_records.hpp"
#include "books.hpp"

// Forward declarations to avoid circular dependency
class Member;
class Librarian;
>>>>>>> Stashed changes
=======
#include "borrow_records.hpp"
#include "books.hpp"

// Forward declarations to avoid circular dependency
class Member;
class Librarian;
>>>>>>> Stashed changes

class LibraryService
{
    private:
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    std::vector<Book> books; //temp

=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    BookList books; // Linked list of books loaded from database
    // the list that stores all members and librarians should also be added here
    
>>>>>>> Stashed changes
    public:
    LibraryService(); //temp

    // guest + member + librarian
    void searchByTitle();
    void searchByAuthor();
    void searchByGenre();

    //member + librarian
<<<<<<< Updated upstream
    bool borrowBook();
    bool returnBook();
=======
    bool borrowBook(Member &);
    bool returnBook(linkedRecords &borrowlist, Member &user);
    bool returnBook(Member &);
>>>>>>> Stashed changes
    void checkBorrowed();

    //librarian only features;
    bool addBook();
    bool removeBook();
    bool registerMember();
    bool removeMember();

    double calculateFine();
};

#endif