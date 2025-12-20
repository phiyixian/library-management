#include <iostream>
#include <fstream>
#include <string>
#include <vector> //temporary for storing user files
#include "../header/people_database_temp.hpp"
#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"
#include "../header/library_service.hpp"

//temp user struct
struct TempUser
{
    std::string id;
    std::string name;
    std::string role;
};

std::vector<TempUser> temp_users = {
    {"G001", "Guest User", "Guest"},
    {"M001", "Alice", "Member"},
    {"M002", "Bob", "Member"},
    {"L001", "Dr. Smith", "Librarian"}
};

TempUser* findUserByID(std::vector<TempUser>& users, const std::string& id)
{
    for (auto& user : users)
    {
        if (user.id == id)
        {
            return &user;
        }
    }
    return nullptr;
}

TempUser* login(std::vector<TempUser>& users)
{
    std::string id;
    std::cout << "Enter user id: ";
    std::cin >> id;

    TempUser* user = findUserByID(users, id);

    if (user == nullptr)
    {
        std::cout << "user not found" << std::endl;
        return nullptr;
    }

    return user;
}
//end of temp


//user menu

void guestMenu(const TempUser& user)
{
    int choice;
    do
    {
        std::cout << "guest menu" << std::endl;
        std::cout << "1. search book" << std::endl;
        std::cin >> choice;

        if (choice == 1)
        {}
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);
}

void memberMenu(const TempUser& user)
{
    int choice;
    do
    {
        std::cout << "\nWelcome, Member: " << user.name << std::endl;
        std::cout << "Allowed actions:" << std::endl;
        std::cout << "1. Search books" << std::endl;
        std::cout << "2. Borrow book" << std::endl;
        std::cout << "3. Return book" << std::endl;
        std::cout << "4. View borrowed books" << std::endl;
        std::cin >> choice;

        if (choice == 1)
        {}
        else if (choice == 2)
        {}
        else if (choice == 3)
        {}
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);
    
    std::cout << "Thank you for using" << std::endl;
    return;
}

void librarianMenu(const TempUser& user)
{
    int choice;
    do
    {
        std::cout << "\nWelcome, librarian: " << user.name << std::endl;
        std::cout << "1. Add book" << std::endl;
        std::cout << "2. Remove book" << std::endl;
        std::cout << "3. Register member" << std::endl;
        std::cout << "4. Remove member" << std::endl;
        std::cout << "5. Borrow book" << std::endl;
        std::cout << "6. Return book" << std::endl;
        std::cout << "7. Fine calculation" << std::endl;
        std::cin >> choice;

        if (choice == 1)
        {}
        else if (choice == 2)
        {}
        else if (choice == 3)
        {}
        else if (choice == 4)
        {}
        else if (choice == 5)
        {}
        else if (choice == 6)
        {}
        else if (choice == 7)
        {}
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);

}

int main()
{
    //just temporary to check polymorphism works. yes it works
    peopleDatabase pdb;
    std::cout << "\n=== TEST: LISTING ALL PEOPLE ===" << std::endl;
    pdb.listAll();

    //create a temp user and login menu
    TempUser* currentUser = login(temp_users);
    if (currentUser == nullptr)
    {
        return 0;
    }

    //leads users to respective menu, from there they can do actions within the system
    if (currentUser->role == "Guest")
    {
        guestMenu(*currentUser);
    }
    else if (currentUser->role == "Member")
    {
        memberMenu(*currentUser);
    }
    else if (currentUser->role == "Librarian")
    {
        librarianMenu(*currentUser);
    }

    return 0;
}

//test output