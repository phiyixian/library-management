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
    default:
        // Error check maybe
        break;
    }


    user->showMenu();
    

    return 0;
}

//test output

// //leads users to respective menu, from there they can do actions within the system
    // if (currentUser->role == "Guest")
    // {
    //     guestMenu(*currentUser, library);
    // }
    // else if (currentUser->role == "Member")
    // {
    //     memberMenu(*currentUser, library);
    // }
    // else if (currentUser->role == "Librarian")
    // {
    //     librarianMenu(*currentUser, library);
    // }