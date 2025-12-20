#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class person
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