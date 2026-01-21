#include "../header/guest.hpp"
#include "../header/library_service.hpp"
#include <string>
#include <iostream>
#include <limits>

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

void Guest::showMenu(LibraryService &library)
{
    int choice;
    while(true)
    {
        std::cout << "\n";
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "  Welcome, " << this->name << " (Guest)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "\nBOOK SEARCH & BROWSING ✮⋆˙" << std::endl;
        std::cout << "  1. Search by Title" << std::endl;
        std::cout << "  2. Search by Author" << std::endl;
        std::cout << "  3. Search by Genre" << std::endl;
        std::cout << "  4. Display Full Catalogue" << std::endl;
        std::cout << "\n  0. Exit" << std::endl;
        std::cout << "\nIf you would like to borrow a book, please exit" << std::endl; 
        std::cout << "and sign in as a member! :)" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[ERROR] Invalid choice. Please enter from (1-4), or 0 to exit.\n";
            continue;
        }
        
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
            std::cout << "\n[SUCCESS] Thank you for visiting the Smart Library Management System! Goodbye!\n";
            return;
        default:
            std::cout << "\n[ERROR]" << std::endl;
        }
        
    }
    
}
