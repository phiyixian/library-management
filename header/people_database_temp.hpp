#ifndef PEOPLE_DATABASE_TEMP_HPP
#define PEOPLE_DATABASE_TEMP_HPP

#include "person.hpp"
#include "member.hpp"
#include "guest.hpp"
#include "librarian.hpp"
#include <string>
#include <vector>

class peopleDatabase
{
    private:
    std::vector<Person *> people;

    public:
    peopleDatabase() = default;
    ~peopleDatabase();

    void addPerson(Person *people_main);
    Person* findByID(const std::string &ID_main);
    void listAll() const;
    size_t size() const;
    Person* get(size_t index) const;
};

#endif
