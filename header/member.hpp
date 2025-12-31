#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include "library_service.hpp"
#include "person.hpp"

class Member: public Person
{
    private:
    int borrow_count;

    public:
    Member(std::string, std::string, std::string);

    void borrowIncrement();
    void borrowDecrement();

    void setBorrowCount(int);
    int getBorrowCount();

    //overriding virtual functions derived in basd class
    std::string getRole() const override;
    void displayInformation() const override;
    void showMenu(LibraryService &) override;
};

#endif