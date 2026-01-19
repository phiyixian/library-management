#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include "person.hpp"
#include "borrow_records.hpp"

// Forward declaration
class LibraryService;

class Member: public Person
{
    private:
    int borrow_count;
    double fines = 0;
    linkedRecords borrow_history; //initialize linked list for borrow records

    public:
    Member(std::string, std::string, std::string);
    ~Member();

    void borrowIncrement();
    void borrowDecrement();

    void setFine(double);
    double getFine();
    void decreaseFines(double);

    void setBorrowCount(int);
    int getBorrowCount();

    linkedRecords& getBorrowHistory();

    //overriding virtual functions derived in basd class
    std::string getRole() const override;
    void displayInformation() const override;
    void showMenu(LibraryService &) override;
};

#endif
