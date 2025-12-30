#include "../header/member.hpp"
#include <string>
#include <iostream>

Member::Member(std::string ID_main, std::string name_main, std::string email_main)
: Person(ID_main, name_main, email_main), borrow_count(0) {}

void Member::borrowIncrement()
{
    borrow_count++;
}

void Member::borrowDecrement()
{
    if (borrow_count > 0)
    {
        borrow_count--;
    }
}

void Member::setBorrowCount(int borrow_count_main)
{
    borrow_count = borrow_count_main;
}

int Member::getBorrowCount()
{
    return borrow_count;
}

std::string Member::getRole() const
{
    return "Member";
}

void Member::displayInformation() const
{
    std::cout << "-MEMBER-" << std::endl;
    Person::displayInformation();
    std::cout << "Borrowed books: " << borrow_count << std::endl;
}



