#include "../header/utility.hpp"
#include "../header/librarian.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

Person *login()
{
    
    std::string userid, username;
    std::cout << "Enter User ID: ";
    std::cin >> userid;
    std::cout << "Enter User Name: ";
    std::cin >> username;

    std::fstream peopledata("database/people_database.txt", std::ios::in);
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

            if (role == "LIBRARIAN")
                p = new Librarian(id, name, email);
            else if (role == "MEMBER") 
                p = new Member(id, name, email);
            else if (role == "GUEST")
                p = new Guest(id, name, email);

            //no need for setters
            if (!p)
            {
                std::cerr << "login(): Unknown role in database: " << role << "\n";
                return nullptr;
            }
            return p;
        }
    }
    return nullptr;
}

// Registers a new user and returns the created object
// Userrole should be either "LIBRARIAN" or "MEMBER"
Person *registerUser(const std::string &userrole)
{
    std::fstream peopledata("database/people_database.txt", std::ios::in);
    if (!peopledata)
    {
        std::cerr << "registerUser(): Error opening people database for reading\n";
        std::exit(1);
    }
 
    std::string useremail, username;
    std::cout << "Enter Email: "; // maybe use regex to validate emails
    std::cin >> useremail;
    std::cout << "Enter User Name: ";
    std::cin >> username;

        
    std::string name, email;
    int max_suffix = 0;
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
            std::cerr << "Username is taken\n";
            return nullptr;
        }    

        if (email == useremail)
        {
            std::cerr << "Email is already registered\n";
            return nullptr;
        }

        // Updates ID for every ID that matches the role
        // Useful for incrementing the ID for new user later
        if (role == userrole)
        {
            try {
                // Handle both old format (M1, L1) and new format (M001, L001)
                int suffix = 0;
                if (tempid.length() == 2)
                {
                    // Old format: M1 -> 1
                    suffix = std::stoi(tempid.substr(1));
                }
                else if (tempid.length() >= 4)
                {
                    // New format: M001 -> 1, L002 -> 2
                    suffix = std::stoi(tempid.substr(1));
                }
                if (suffix > max_suffix)
                    max_suffix = suffix;
            } catch (...) {
                // Skip invalid IDs
            }
        }
    }

    peopledata.close();

    // Reopen file in append mode to add new user
    peopledata.open("database/people_database.txt", std::ios::app);
    if (!peopledata)
    {
        std::cerr << "registerUser(): Error opening people database for appending\n";
        std::exit(1);
    }

    // Incrementing the ID
    int nextSuffix = max_suffix + 1;

    std::ostringstream idoss;
    idoss << userrole[0]
        << std::setw(3)
        << std::setfill('0')
        << nextSuffix;

    std::string id = idoss.str();

    // Saving the user's info
    // Format: Role|ID|Username|Email|
    // ID format: G001, L001, M001
    peopledata << '\n' << userrole << '|' << id << '|' << username << '|' << useremail;

    peopledata.close();

    Person *p = nullptr;
    // (poly) Create derived object based on role
    
    if (userrole == "LIBRARIAN")
        p = new Librarian(id, username, useremail);
    if (userrole == "MEMBER") 
        p = new Member(id, username, useremail);
    
    return p;
}

std::string borrowStatus(bool overdue){
    if(overdue){
        return "OVERDUE";
    } else {
        return "ONTIME";
    }
}

time_t parseTimeFromString(const std::string &dateTimeString) {
    std::tm tm = {};
    std::istringstream iss(dateTimeString);
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&tm); // local time
}

const std::string parseTimeIntoString(time_t t) {
    std::tm *parseTimeptr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(parseTimeptr, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}