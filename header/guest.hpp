#ifndef GUEST_HPP
#define GUEST_HPP

#include "person.hpp"
#include <string>

class Guest: public Person
{
    public:
    Guest(std::string, std::string, std::string);
    std::string getRole() const override; //overriding virtual function derived in base class
    void displayInformation() const override;
    void showMenu() override;
};

#endif