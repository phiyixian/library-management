#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "../header/people_database_temp.hpp"
#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"
#include "../header/library_service.hpp"
#include "../header/utility.hpp"

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(35) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSeparator()
{
    std::cout << std::string(50, '-') << std::endl;
}

int main()
{
    int choice;
    Person *user = nullptr;
    LibraryService library;

    printHeader("Library Management System");
    std::cout << "\n1. Register (New Member)" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Continue as Guest" << std::endl;
    std::cout << "0. Exit" << std::endl;
    printSeparator();
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1: // Register
        printHeader("Member Registration");
        user = registerUser("MEMBER");
        if (user)
        {
            std::cout << "\n[SUCCESS] Registration successful!\n";
        }
        else
        {
            std::cout << "\n[ERROR] Registration failed. Please try again.\n";
        }
        break;

    case 2: // Login
        printHeader("Login");
        do 
        {
            user = login();
            if (user == nullptr)
            {
                std::cout << "\n[ERROR] User ID not found or Username mismatch. Try again." << std::endl;
            }
        } while(user == nullptr);
        
        std::cout << "\n[SUCCESS] Login successful!\n";
        break;

    case 3: // Continue as Guest
        {
        printHeader("Guest Access");
        std::string guestname, guestemail;
        std::cin.ignore();
        std::cout << "Enter Your Name: ";
        std::getline(std::cin, guestname);
        std::cout << "Enter Your Email: ";
        std::getline(std::cin, guestemail);
        
        user = new Guest("GXXX", guestname, guestemail);
        std::cout << "\n[SUCCESS] Continuing as Guest!\n";
        break;
        }
    case 0:
        std::cout << "\nThank you for using Library Management System. Goodbye!\n";
        return 0;
    default:
        std::cout << "\n[ERROR] Invalid option. Please choose from (1-3), or 0 to exit." << std::endl;
        return 0;
    }

    if (user)
    {
        user->showMenu(library);
        delete user; // Clean up
    }
    else
    {
        std::cout << "\n[ERROR] No user session started.\n";
    }

    return 0;
}
