#include <iostream>

#include <string>
#include <limits>
#include "../header/people_database_temp.hpp"
#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"
#include "../header/library_service.hpp"
#include "../header/utility.hpp"

int main()
{
    //just temporary to check polymorphism works
    int choice;

    std::cout << "===== Library Management System =====" << std::endl;
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Continue as Guest" << std::endl;
    std::cout << "> ";
    std::cin >> choice; // There should be an error check here for invalid choices

    Person *user;

    switch (choice)
    {
    case 1: // Register
        user = registerUser();
        std::cout << "Register successful!\n";
        break;
    case 2: // Login
        do 
        {
        user = loginUser();

        if (user == nullptr)
        {
            std::cout << "ID not found or Username mismatch. Try again.";
        }
        } while(user == nullptr);
        
        std::cout << "Login successful!\n";
        break;
    case 3: // Continue as Guest
        {
        std::string guestname, guestemail;
        std::cout << "Enter User Name: ";
        std::cin >> guestname;
        std::cout << "Enter User Email: ";
        std::cin >> guestemail;
        
        user = new Guest("GXXX", guestname, guestemail);
        std::cout << "Continuing as Guest!\n";
        break;
        }
    default:
        // Error check maybe
        break;
    }


    user->showMenu();
    

    return 0;
}