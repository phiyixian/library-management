//temp file for people database
#include "../header/people_database_temp.hpp"
#include <string>
#include <iostream>
#include <fstream>

peopleDatabase::~peopleDatabase()
{
    for (auto people_main : people)
    {
        delete people_main;
    }
}

void peopleDatabase::addPerson(Person *people_main)
{
    people.push_back(people_main);
}

Person* peopleDatabase::findByID(const std::string &ID_main)
{
    for (auto people_main: people)
    {
        if(people_main->getID() == ID_main)
        {
            return people_main;
        }
    }
    return nullptr;
}

void peopleDatabase::listAll() const
{
    // int i = 0;
    // for (auto people_main: people)
    // {
    //     std::cout << "Person " << i + 1 << std::endl;
    //     people[i]->displayInformation();
    //     std::cout << std::endl;
    // }

    std::string line;

    //Open a file in read mode.
    std::ifstream inFile("database/people_database.txt");
    if (!inFile) {
        std::cerr << "Unable to open file people_database.txt";
        exit(1); // terminate with error
    }

    while(getline(inFile, line)) {
        std::cout << line << std::endl;
    }
}

size_t peopleDatabase::size() const
{
    return people.size();
}

Person* peopleDatabase::get(size_t i) const
{
    return people[i];
}