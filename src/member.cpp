#include "../header/member.hpp"
#include "../header/library_service.hpp"
#include <string>
#include <iostream>
#include <iomanip>

member::member(std::string ID_main, std::string name_main, std::string email_main)
: person(ID_main, name_main, email_main), borrow_count(0) {}

void member::borrowIncrement()
{
    borrow_count++;
}

void member::borrowDecrement()
{
    if (borrow_count > 0)
    {
        borrow_count--;
    }
}

void member::setBorrowCount(int borrow_count_main)
{
    borrow_count = borrow_count_main;
}

int member::getBorrowCount()
{
    return borrow_count;
}

std::string member::getRole() const
{
    return "Member";
}

void member::displayInformation() const
{
    std::cout << "-MEMBER-" << std::endl;
    person::displayInformation();
    std::cout << "Borrowed books: " << borrow_count << std::endl;
}

<<<<<<< Updated upstream
=======
void Member::showMenu(LibraryService &library)
{
    int choice;
    do
    {
        std::cout << "\n";
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "  Welcome, " << this->name << " (Member)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        // Display member info
        linkedRecords& borrowlist = this->getBorrowHistory();
        borrowlist.updateStatus();
        double totalFines = borrowlist.calculateTotalFines();
        this->setFine(totalFines);
        
        std::cout << "Books Borrowed: " << this->borrow_count << std::endl;
        if (totalFines > 0)
        {
            std::cout << "Outstanding Fines: RM" << std::fixed << std::setprecision(2) << totalFines << std::endl;
        }
        std::cout << std::string(50, '-') << std::endl;
        
        std::cout << "\nBOOK SEARCH" << std::endl;
        std::cout << "  1. Search by Title" << std::endl;
        std::cout << "  2. Search by Author" << std::endl;
        std::cout << "  3. Search by Genre" << std::endl;
        std::cout << "  7. Display Full Catalogue" << std::endl;
        
        std::cout << "\nBORROWING" << std::endl;
        std::cout << "  4. Borrow Book" << std::endl;
        std::cout << "  5. Return Book" << std::endl;
        std::cout << "  6. View My Borrowed Books" << std::endl;
        
        std::cout << "\n  0. Logout" << std::endl;
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
            library.borrowBook(*this);
            break;
        case 5:
            library.returnBook(*this);
            break;
        case 6:
            {
            std::cout << "\n";
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "  My Borrowed Books" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            linkedRecords& borrowlist = this->getBorrowHistory();
            borrowlist.updateStatus();
            borrowlist.printRecords();
            break;
            }
        case 7:
            library.displayCatalogue();
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
>>>>>>> Stashed changes


