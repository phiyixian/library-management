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

void clearScreen() {
    // Cross-platform screen clearing
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    int padding = (50 + title.length()) / 2;  // length() is a built-in C++ function for std::string
    std::cout << std::setw(padding) << title << std::endl;
    //std::cout << std::setw(35) << title << std::endl;
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

    while (true)
    {
        clearScreen();

        std::cout << R"(

        _____
        /    /|_ ___________________________________
        /    // /|       ~~*~~                      /|
        (====|/ //  Welcome to the...   ______      / |
        (=====|/    SMART LIBRARY     /  /  / |   / .|
        (====|/    MANAGEMENT SYSTEM  /__/__/ (_) / /||
        /_________________________________________/ / ||
        |  _____________________________________  ||  ||
        | ||                                    | ||
        | ||                                    | ||
        | ||                                    | || 
        )" << std::endl;

        std::cout << "\nPress Enter to log in..." << std::endl;
        std::cin.get();
        clearScreen();

        std::cout << R"(
                _.--._  _.--._             -----~~~~====*====~~~~-----
            ,-=.-":;:;:;\':;:;:;"-._              ˗ˏˋ ꒰ SLMP  ꒱ˎˊ˗
            \\\:;:;:;:;:;\:;:;:;:;:;\         
            \\\:;:;:;:;:;\:;:;:;:;:;\        1. Register as New Member
            \\\:;:;:;:;:;\:;:;:;:;:;\       2. Login
            \\\:;:;:;:;:;\:;::;:;:;:\      3. Continue as Guest
            \\\;:;::;:;:;\:;:;:;::;:\     0. Exit
            \\\;;:;:_:--:\:_:--:_;:;\   -----~~~~====*====~~~~----- 
            \\\_.-"      :      "-._\
            \`_..--""--.;.--""--.._=>    

        )" << std::endl;

        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > 3)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[ERROR] Invalid option. Please choose from (1-3), or 0 to exit." << std::endl;
            continue;
        }

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
            
            user = new Guest("GXXX", guestname, guestemail);
            std::cout << "\n[SUCCESS] Continuing as Guest!\n";
            break;
            }

        case 0:
            std::cout << "\nThank you for using Library Management System. Goodbye!\n";
            return 0;

        default:
            continue;
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
    }


    return 0;
}
