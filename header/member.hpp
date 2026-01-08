#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include "person.hpp"

<<<<<<< Updated upstream
class member: public person
=======
// Forward declaration
class LibraryService;

// Forward declaration
class LibraryService;

// Forward declaration
class LibraryService;

// Forward declaration
class LibraryService;

class Member: public Person
>>>>>>> Stashed changes
{
    private:
    int borrow_count;

    public:
    member(std::string, std::string, std::string);

    void borrowIncrement();
    void borrowDecrement();

    void setBorrowCount(int);
    int getBorrowCount();

    //overriding virtual functions derived in basd class
    std::string getRole() const override;
    void displayInformation() const override;
};

#endif