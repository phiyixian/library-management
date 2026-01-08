#include "../header/librarian.hpp"
#include "../header/library_service.hpp"
#include <string>
#include <iostream>

librarian::librarian(std::string ID_main, std::string name_main, std::string email_main, std::string position_title_main)
: person(ID_main, name_main, email_main), position_title(position_title_main)
{
    setPositionTitle(position_title_main);
}

void librarian::setPositionTitle(std::string position_title_main)
{
    position_title = position_title_main;
}

std::string librarian::getPositionTitle() const
{
    return position_title;
}

std::string librarian::getRole() const
{
    return "Librarian";
}

<<<<<<< Updated upstream
<<<<<<< Updated upstream
void librarian::displayInformation() const
=======
=======
>>>>>>> Stashed changes
void Librarian::decreaseFines(double amount)
{
    // Librarians don't have fines, but this function is needed for polymorphism
    // This is a no-op for librarians
    (void)amount; // Suppress unused parameter warning
}

void Librarian::displayInformation() const
>>>>>>> Stashed changes
{
    std::cout << "--LIBRARIAN--" << std::endl;
    person::displayInformation();
    std::cout << "Position: " << position_title << std::endl;
<<<<<<< Updated upstream
=======
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
        
        switch (choice)
        {
        // User actions
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
        // Administrative actions
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
>>>>>>> Stashed changes
}