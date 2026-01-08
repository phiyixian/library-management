#include "../header/librarian.hpp"
#include "../header/library_service.hpp"
#include <string>
#include <iostream>
#include <limits>

Librarian::Librarian(std::string ID_main, std::string name_main, std::string email_main, std::string position_title_main)
: Person(ID_main, name_main, email_main), position_title(position_title_main), borrow_count(0) {}

void Librarian::setPositionTitle(std::string position_title_main)
{
    position_title = position_title_main;
}

std::string Librarian::getPositionTitle() const
{
    return position_title;
}

void Librarian::decreaseFines(double amount)
{
    // Librarians don't have fines in this system, but the method is required by polymorphism
    std::cout << "Librarians do not incur fines." << std::endl;
}

std::string Librarian::getRole() const
{
    return "Librarian";
}

void Librarian::displayInformation() const
{
    std::cout << "--LIBRARIAN--" << std::endl;
    Person::displayInformation();
    std::cout << "Position: " << position_title << std::endl;
}

void Librarian::showMenu(LibraryService &library)
{
    int choice;
    do
    {
        std::cout << "\n";
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "  Welcome, " << this->name << " (Librarian)" << std::endl;
        std::cout << "  Position: " << this->position_title << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        std::cout << "\nBOOK SEARCH & BROWSING" << std::endl;
        std::cout << "  1. Search by Title" << std::endl;
        std::cout << "  2. Search by Author" << std::endl;
        std::cout << "  3. Search by Genre" << std::endl;
        std::cout << "  7. Display Full Catalogue" << std::endl;
        std::cout << "  6. View All Borrowed Books" << std::endl;
        
        std::cout << "\nBOOK MANAGEMENT" << std::endl;
        std::cout << "  8. Add New Book" << std::endl;
        std::cout << "  9. Remove Book" << std::endl;
        
        std::cout << "\nMEMBER MANAGEMENT" << std::endl;
        std::cout << "  10. Register New Member" << std::endl;
        std::cout << "  11. Remove Member" << std::endl;
        
        std::cout << "\n  0. Logout" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        
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
        case 6:
            {
            std::cout << "\n";
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "  All Borrowed Books" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            library.checkBorrowed();
            break;
            }
        case 7:
            library.displayCatalogue();
            break;
        case 8:
            library.addBook();
            break;
        case 9:
            library.removeBook();
            break;
        case 10:
            library.registerMember();
            break;
        case 11:
            library.removeMember();
            break;
        case 0:
            std::cout << "\n[SUCCESS] Logging out. Thank you for using the Library Management System!\n";
            break;
        default:
            std::cout << "\n[ERROR] Invalid choice. Please try again.\n";
            break;
        }
        
    } while (choice != 0);
    
    return;
}
