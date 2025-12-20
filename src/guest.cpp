#include "../header/guest.hpp"
#include <string>
#include <iostream>

guest::guest(std::string ID_main, std::string name_main, std::string email_main)
: person(ID_main, name_main, email_main) {}

std::string guest::getRole() const
{
    return "Guest";
}

void guest::displayInformation() const
{
    std::cout << "-GUEST-" << std::endl;
    person::displayInformation();
}