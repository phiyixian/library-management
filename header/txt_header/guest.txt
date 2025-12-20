#ifndef GUEST_HPP
#define GUEST_HPP

#include "person.hpp"
#include <string>

class guest: public person
{
    public:
    guest(std::string, std::string, std::string);
    std::string getRole() const override; //overriding virtual function derived in base class
    void displayInformation() const override;
};

#endif