#include "../header/guest.hpp"
#include <string>
#include <iostream>

Guest::Guest(std::string ID_main, std::string name_main, std::string email_main)
: Person(ID_main, name_main, email_main) {}

std::string Guest::getRole() const
{
    return "Guest";
}

void Guest::displayInformation() const
{
    std::cout << "-Guest-" << std::endl;
    Person::displayInformation();
}