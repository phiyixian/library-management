#include "../header/member.hpp"
#include <string>
#include <iostream>

member::member(std::string ID_main, std::string name_main, std::string email_main)
: person(ID_main, name_main, email_main), borrow_count(0) {}

void member::borrowIncrement()
{
    borrow_count++;
}

void member::borrowDecrement()
{
    if (borrow_count > 0)
    {
        borrow_count--;
    }
}

void member::setBorrowCount(int borrow_count_main)
{
    borrow_count = borrow_count_main;
}

int member::getBorrowCount()
{
    return borrow_count;
}

std::string member::getRole() const
{
    return "Member";
}

void member::displayInformation() const
{
    std::cout << "-MEMBER-" << std::endl;
    person::displayInformation();
    std::cout << "Borrowed books: " << borrow_count << std::endl;
}



