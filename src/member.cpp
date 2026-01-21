#include "../header/member.hpp"
#include "../header/library_service.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

Member::Member(std::string ID_main, std::string name_main, std::string email_main)
: Person(ID_main, name_main, email_main), borrow_count(0), borrow_history(ID_main)
{
    setFine(this->borrow_history.calculateTotalFines());
    setBorrowCount(this->borrow_history.getRecordCount());
}

Member::~Member()
{
    // 1. Save the borrow history to file
    borrow_history.save();
    // 2. Free up the history linked lists (handled by destructor of linkedRecords)
}

void Member::borrowIncrement()
{
    borrow_count++;
}

void Member::borrowDecrement()
{
    if (borrow_count > 0)
    {
        borrow_count--;
    }
}

void Member::setFine(double fine)
{
    this->fines = fine;
}

double Member::getFine()
{
    return this->fines;
}

void Member::decreaseFines(double amount)
{
    this->fines -= amount;
    if (this->fines < 0)
    {
        this->fines = 0;
    }
}

void Member::setBorrowCount(int borrow_count_main)
{
    borrow_count = borrow_count_main;
}

int Member::getBorrowCount()
{
    return borrow_count;
}

std::string Member::getRole() const
{
    return "Member";
}

linkedRecords& Member::getBorrowHistory()
{
    return this->borrow_history;
}

void Member::displayInformation() const
{
    std::cout << "-MEMBER-" << std::endl;
    Person::displayInformation();
    std::cout << "Borrowed books: " << borrow_count << std::endl;
}

void Member::showMenu(LibraryService &library)
{
    int choice;
    while (true)
    {
        std::cout << std::endl;
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
        
        std::cout << "\nBOOK SEARCH & BROWSING ✮⋆˙" << std::endl;
        std::cout << "  1. Search by Title" << std::endl;
        std::cout << "  2. Search by Author" << std::endl;
        std::cout << "  3. Search by Genre" << std::endl;
        std::cout << "  4. Display Full Catalogue" << std::endl;
        
        std::cout << "\nBORROWING ✶⋆˚" << std::endl;
        std::cout << "  5. Borrow Book" << std::endl;
        std::cout << "  6. Return Book" << std::endl;
        std::cout << "  7. View My Borrowed Books" << std::endl;
        
        std::cout << "\n  0. Logout" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid option. Please choose from (1-7), or 0 to exit." << std::endl;
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
            case 5:
                library.borrowBook(*this);
                break;
            case 6:
                library.returnBook(*this);
                break;
            case 7:
                {
                std::cout << "\n";
                std::cout << std::string(50, '=') << std::endl;
                std::cout << std::setw(33) << "My Borrowed Books" << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                linkedRecords& borrowlist = this->getBorrowHistory();
                borrowlist.updateStatus();
                borrowlist.printRecords();
                break;
                }
                //library.displayCatalogue();
                break;
            case 0:
                std::cout << "\n[SUCCESS] Logging out. Thank you for using the Smart Library Management System!\n";
                return;
            default:
                std::cout << "[ERROR]" << std::endl;
        }
    }
}
