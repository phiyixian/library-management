#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

<<<<<<< Updated upstream
<<<<<<< Updated upstream
class person
=======
=======
>>>>>>> Stashed changes
// Forward declaration to avoid circular dependency
class LibraryService;

class Person
>>>>>>> Stashed changes
{
    protected:
    std::string ID, name, email;

    public:
    //constructor
    person(std::string, std::string, std::string);
    virtual ~person() = default; //polymorphism

    //actuators and accessors
    std::string getID() const;
    std::string getName() const;
    std::string getEmail() const;

    void setID(std::string);
    void setName(std::string);
    void setEmail(std::string);

    // to be used in polymorphism
    virtual void displayInformation() const;
    virtual std::string getRole() const;
};

#endif