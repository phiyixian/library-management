#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"
#include "../header/library_service.hpp"
#include "../header/utility.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Person *login()
{
    std::string userid, username;
    std::cout << "Enter User ID: ";
    std::cin >> userid;
    std::cout << "Enter User Name: ";
    std::cin >> username;

    std::fstream peopledata("../database/people_databse.txt", std::ios::in);
    if (!peopledata)
    {
        std::cerr << "Error opening people database\n";
        std::exit(1);
    }

    std::string line;

    // Checking if ID exists
    std::getline(peopledata, line); // Skip header in database

    while (std::getline(peopledata, line)) 
    {   
        
        std::istringstream ss(line);
        std::string role, id, name, email;

        std::getline(ss, role, '|');
        std::getline(ss, id, '|');

        if (id == userid) { // When ID is matched
            // Read the rest of the fields
            std::getline(ss, name, '|');
            std::getline(ss, email, '|');

            // Check if entered name is same as database (idk)
            if (username != name)
            {
                return nullptr;
            }
            
            Person *p = nullptr;
            // (poly) Create derived object based on role
            if (role == "GUEST")
                p = new Guest(id, name, email);
            else if (role == "LIBRARIAN")
                p = new Librarian(id, name, email);
            else 
                p = new Member(id, name, email);

            p->setID(id);
            p->setEmail(email);
            p->setName(name);
            
            return p;
        }
    }
    return nullptr;
}

Person *registerUser(std::string &userrole)
{
    std::fstream peopledata("../database/people_databse.txt", std::ios::in | std::ios::app);
    if (!peopledata)
    {
        std::cerr << "Error opening people database\n";
        std::exit(1);
    }
 
    std::string useremail, username;
    std::cout << "Enter Email: "; // maybe use regex to validate emails
    std::cin >> useremail;
    std::cout << "Enter User Name: ";
    std::cin >> username;

        
    std::string name, email,id;
    std::string line;
    std::getline(peopledata, line); // Skip header in database
    while (std::getline(peopledata, line)) // Read loop
    {   
        
        std::istringstream ss(line);
        std::string role, tempid;

        std::getline(ss, role, '|');
        std::getline(ss, tempid, '|');

        std::getline(ss, name, '|');
        std::getline(ss, email, '|');

        // Checks if username and email is unused
        if (name == username)
        {   
            std::cout << "Username is taken\n";
            return nullptr;
        }    

        if (email == useremail)
        {
            std::cout << "Email is already registered\n";
            return nullptr;
        }

        // Updates ID for every ID that matches the role
        // Useful for incrementing the ID for new user later
        if (role == userrole)
        {
            id = tempid;
        }
    }

    // Incrementing the ID
    const int IDNoIndex = 1; // the index in the id string where the numbers start 
    id = userrole[0] + std::to_string(std::stoi(id.substr(IDNoIndex)));

    // Saving the user's info
    // Format: Role|ID|Username|Email|
    // Role format: G001, L001, M001
    peopledata << userrole << '|' << id << '|' << username << '|' << useremail << "|\n";

    Person *p = nullptr;
    // (poly) Create derived object based on role
    if (userrole == "GUEST")
        p = new Guest(id, name, email);
    else if (userrole == "LIBRARIAN")
        p = new Librarian(id, name, email);
    else 
        p = new Member(id, name, email);

    return p;
}