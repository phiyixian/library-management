#include "../header/member.hpp"
#include <string>
#include <iostream>

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
    // 2. Free up the history linked lists

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
    do
    {
        std::cout << "\nWelcome, Member: " << this->name << std::endl;
        std::cout << "User actions:" << std::endl;
        std::cout << "1. Search book by title" << std::endl;
        std::cout << "2. Search book by author" << std::endl;
        std::cout << "3. Search book by genre" << std::endl;
        std::cout << "4. Borrow book" << std::endl;
        std::cout << "5. Return book" << std::endl;
        std::cout << "6. View borrowed books" << std::endl;
        std::cout << "7. Display Catalogue" << std::endl;
        std::cout << "8. Quit" << std::endl;
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
        default:
            std::cout << "Invalid action\n";
            break;
        }
        
    } while (choice != 8);
    
    std::cout << "Thank you for using" << std::endl;
    return;
}


