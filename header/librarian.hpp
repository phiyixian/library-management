#ifndef LIBRARIAN_HPP
#define LIBRARIAN_HPP

#include "person.hpp"
#include <string>

// Forward declaration
class LibraryService;

class Librarian: public Person
{
    private:
    std::string position_title;
    int borrow_count;

    public:
    Librarian(std::string, std::string, std::string, std::string = "New Hire");

    void setPositionTitle(std::string);
    std::string getPositionTitle() const;

    void decreaseFines(double);

    std::string getRole() const override;
    void displayInformation() const override;
    void showMenu(LibraryService &) override;
};

#endif
