#include "../header/person.hpp"
#include <iostream>
#include <string>

Person::Person(std::string ID_main, std::string name_main, std::string email_main)
{
    setID(ID_main);
    setName(name_main);
    setEmail(email_main);
}

void Person::setID(std::string ID_main)
{
    ID = ID_main;
}

void Person::setName(std::string name_main)
{
    name = name_main;
}

void Person::setEmail(std::string email_main)
{
    email = email_main;
}

std::string Person::getID() const
{
    return ID;
}

std::string Person::getName() const
{
    return name;
}

std::string Person::getEmail() const
{
    return email;
}

void Person::displayInformation() const
{
    std::cout << "NAME:   " << name << std::endl;
    std::cout << "ID:     " << ID << std::endl;
    std::cout << "E-MAIL: " << email << std::endl;
}

std::string Person::getRole() const
{
    return "Person";
}

void Person::showMenu() 
{
    std::cout << "Welcome\n";
}