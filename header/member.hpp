#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include "person.hpp"

class member: public person
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