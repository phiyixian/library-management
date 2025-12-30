#include "../header/librarian.hpp"
#include <string>
#include <iostream>

Librarian::Librarian(std::string ID_main, std::string name_main, std::string email_main, std::string position_title_main)
: Person(ID_main, name_main, email_main), position_title(position_title_main)
{
    setPositionTitle(position_title_main);
}

void Librarian::setPositionTitle(std::string position_title_main)
{
    position_title = position_title_main;
}

std::string Librarian::getPositionTitle() const
{
    return position_title;
}

std::string Librarian::getRole() const
{
    return "Librarian";
}

void Librarian::displayInformation() const
{
    std::cout << "--LIBRARIAN--" << std::endl;
    Person::displayInformation();
    std::cout << "Position: " << position_title << std::endl;
}