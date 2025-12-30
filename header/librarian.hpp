#ifndef LIBRARIAN_HPP
#define LIBRARIAN_HPP

#include "person.hpp"
#include <string>

class Librarian: public Person
{
    private:
    std::string position_title;

    public:
    Librarian(std::string, std::string, std::string, std::string);

    void setPositionTitle(std::string);
    std::string getPositionTitle() const;
    
    std::string getRole() const override;
    void displayInformation() const override;
};

#endif