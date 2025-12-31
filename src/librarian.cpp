#include "../header/librarian.hpp"
#include <string>
#include <iostream>

Librarian::Librarian(std::string ID_main, std::string name_main, std::string email_main, std::string position_title_main)
: Person(ID_main, name_main, email_main), position_title(position_title_main) {}

void Librarian::setPositionTitle(std::string position_title_main)
{
    position_title = position_title_main;
}

std::string Librarian::getPositionTitle() const
{
    return position_title;
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
        std::cout << "\nWelcome, Librarian: " << this->name << std::endl;
        std::cout << "User actions:" << std::endl;
        std::cout << "1. Search book by title" << std::endl;
        std::cout << "2. Search book by author" << std::endl;
        std::cout << "3. Search book by genre" << std::endl;
        std::cout << "4. Borrow book" << std::endl;
        std::cout << "5. Return book" << std::endl;
        std::cout << "6. View borrowed books" << std::endl;
        std::cout << "7. Display Catalogue" << std::endl;
        std::cout << std::endl;
        std::cout << "Administrative actions:" << std::endl;
        std::cout << "8. Add a new book" << std::endl;
        std::cout << "9. Remove a book" << std::endl;
        std::cout << "10. Register new member" << std::endl;
        std::cout << "11. Remove member" << std::endl;
        std::cout << std::endl;
        std::cout << "12. Quit" << std::endl;
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
        case 4:
            library.borrowBook();
            break;
        case 5:
            library.returnBook();
            break;
        case 6:
            library.checkBorrowed();
            break;
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
        default:
            std::cout << "Invalid action\n";
            break;
        }
        
    } while (choice != 12);
    
    std::cout << "Thank you for using" << std::endl;
    return;
}