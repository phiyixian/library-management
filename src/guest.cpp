#include "../header/guest.hpp"
#include "../header/library_service.hpp"
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
<<<<<<< Updated upstream
    std::cout << "-GUEST-" << std::endl;
    person::displayInformation();
=======
    std::cout << "-Guest-" << std::endl;
    Person::displayInformation();
}

void Guest::showMenu(LibraryService &library)
{
    int choice;
    do
    {
        std::cout << "\n";
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "  Welcome, " << this->name << " (Guest)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "\nBOOK SEARCH & BROWSING" << std::endl;
        std::cout << "  1. Search by Title" << std::endl;
        std::cout << "  2. Search by Author" << std::endl;
        std::cout << "  3. Search by Genre" << std::endl;
        std::cout << "  4. Display Full Catalogue" << std::endl;
        std::cout << "\n  0. Exit" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice)
        {
        case 1:
            library.searchByTitle();
            break;        
        case 2:
            library.searchByAuthor();
            break;
        case 3:
            library.searchByGenre();
            break;
        case 4:
            library.displayCatalogue();
            break;
        case 0:
            std::cout << "\n[SUCCESS] Thank you for visiting! Goodbye!\n";
            break;
        default:
            std::cout << "\n[ERROR] Invalid choice. Please try again.\n";
            break;
        }
        
    } while (choice != 0);
    
    return;
>>>>>>> Stashed changes
}