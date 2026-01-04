#ifndef PEOPLE_DATABASE_TEMP_HPP
#define PEOPLE_DATABASE_TEMP_HPP

#include "person.hpp"
#include "member.hpp"
#include "guest.hpp"
#include "librarian.hpp"
#include <string>
#include <vector> //used vector for dynamic memory allocation, easier than raw dogging raw memory

class peopleDatabase
{
    private:
    std::vector<Person *> people;

    public:
    peopleDatabase() = default; //constructor
    ~peopleDatabase(); //destruuctor

    void addPerson(Person *people_main);
    Person* findByID(const std::string &ID_main);
    void listAll() const;
    size_t size() const; //used size_t for unsigned array size, will never be negative
    Person* get(size_t index) const;
};


#endif