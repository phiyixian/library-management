#include "../header/librarian.hpp"
#include <string>
#include <iostream>

librarian::librarian(std::string ID_main, std::string name_main, std::string email_main, std::string position_title_main)
: person(ID_main, name_main, email_main), position_title(position_title_main)
{
    setPositionTitle(position_title_main);
}

void librarian::setPositionTitle(std::string position_title_main)
{
    position_title = position_title_main;
}

std::string librarian::getPositionTitle() const
{
    return position_title;
}

std::string librarian::getRole() const
{
    return "Librarian";
}

void librarian::displayInformation() const
{
    std::cout << "--LIBRARIAN--" << std::endl;
    person::displayInformation();
    std::cout << "Position: " << position_title << std::endl;
}