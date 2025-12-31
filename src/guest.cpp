#include "../header/guest.hpp"
#include <string>
#include <iostream>

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
    do
    {
        std::cout << "\nWelcome, Guest: " << this->name << std::endl;
        std::cout << "User actions:" << std::endl;
        std::cout << "1. Search book by title" << std::endl;
        std::cout << "2. Search book by author" << std::endl;
        std::cout << "3. Search book by genre" << std::endl;
        std::cout << "4. Display Catalogue" << std::endl;
        std::cout << "5. Quit" << std::endl;
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
        default:
            std::cout << "Invalid action\n";
            break;
        }
        
    } while (choice != 5);
    
    std::cout << "Thank you for using" << std::endl;
    return;
}