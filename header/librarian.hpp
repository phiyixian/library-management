#ifndef LIBRARIAN_HPP
#define LIBRARIAN_HPP

#include "person.hpp"
#include <string>

<<<<<<< Updated upstream
<<<<<<< Updated upstream
class librarian: public person
=======
=======
>>>>>>> Stashed changes
// Forward declaration
class LibraryService;

class Librarian: public Person
>>>>>>> Stashed changes
{
    private:
    std::string position_title;

    public:
    librarian(std::string, std::string, std::string, std::string);

    void setPositionTitle(std::string);
    std::string getPositionTitle() const;
    
    std::string getRole() const override;
    void displayInformation() const override;
};

#endif