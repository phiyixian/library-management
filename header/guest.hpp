#ifndef GUEST_HPP
#define GUEST_HPP

#include "person.hpp"
#include <string>

// Forward declaration
class LibraryService;

class Guest: public Person
{
    public:
    Guest(std::string, std::string, std::string);
    std::string getRole() const override;
    void displayInformation() const override;
    void showMenu(LibraryService &) override;
};

#endif
