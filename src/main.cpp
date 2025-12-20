#include <iostream>
#include <fstream>
#include <string>
#include <vector> //temporary for storing user files
#include "../header/people_database_temp.hpp"
#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"

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
    std::cout << "\nWelcome, Guest: " << user.name << "\n";
    std::cout << "Allowed actions:\n";
    std::cout << "1. Search books by title\n";
    std::cout << "2. Search books by author\n";
    std::cout << "3. Search books by genre\n";
}

void memberMenu(const TempUser& user)
{
    std::cout << "\nWelcome, Member: " << user.name << "\n";
    std::cout << "Allowed actions:\n";
    std::cout << "1. Search books\n";
    std::cout << "2. Borrow book\n";
    std::cout << "3. Return book\n";
    std::cout << "4. View borrowed books\n";
}

void librarianMenu(const TempUser& user)
{
    std::cout << "\nWelcome, Librarian: " << user.name << "\n";
    std::cout << "Allowed actions:\n";
    std::cout << "1. Add book\n";
    std::cout << "2. Remove book\n";
    std::cout << "3. Register member\n";
    std::cout << "4. Remove member\n";
    std::cout << "5. Borrow / return book\n";
    std::cout << "6. Fine calculation\n";
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