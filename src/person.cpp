#include "../header/person.hpp"
#include <iostream>
#include <string>

person::person(std::string ID_main, std::string name_main, std::string email_main)
{
    setID(ID_main);
    setName(name_main);
    setEmail(email_main);
}

void person::setID(std::string ID_main)
{
    ID = ID_main;
}

void person::setName(std::string name_main)
{
    name = name_main;
}

void person::setEmail(std::string email_main)
{
    email = email_main;
}

std::string person::getID() const
{
    return ID;
}

std::string person::getName() const
{
    return name;
}

std::string person::getEmail() const
{
    return email;
}

void person::displayInformation() const
{
    std::cout << "NAME:   " << name << std::endl;
    std::cout << "ID:     " << ID << std::endl;
    std::cout << "E-MAIL: " << email << std::endl;
}

std::string person::getRole() const
{
    return "person";
}