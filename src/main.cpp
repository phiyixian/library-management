#include <iostream>
#include <fstream>
#include <string>
#include <limits>
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
    {"M001", "Susan", "Member"},
    {"M002", "James", "Member"},
    {"L001", "Iliot", "Librarian"}
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
void guestMenu(const TempUser& user, LibraryService& library)
{
    int choice;
    do
    {
        std::cout << "guest menu" << std::endl;
        std::cout << "1. search book by title" << std::endl;
        std::cout << "2. search book by author" << std::endl;
        std::cout << "3. search book by genre" << std::endl;
        std::cout << "4. display catalogue" << std::endl;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            library.searchByTitle();
        }
        else if (choice == 2)
        {
            library.searchByAuthor();
        }
        else if (choice == 3)
        {
            library.searchByGenre();
        }
        else if (choice == 4)
        {
            library.displayCatalogue();
        }
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);
}

void memberMenu(const TempUser& user, LibraryService& library)
{
    int choice;
    do
    {
        std::cout << "\nWelcome, Member: " << user.name << std::endl;
        std::cout << "Allowed actions:" << std::endl;
        std::cout << "1. search book by title" << std::endl;
        std::cout << "2. search book by author" << std::endl;
        std::cout << "3. search book by genre" << std::endl;
        std::cout << "4. Borrow book" << std::endl;
        std::cout << "5. Return book" << std::endl;
        std::cout << "6. View borrowed books" << std::endl;
        std::cout << "7. Display Catalogue" << std::endl;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            library.searchByTitle();
        }
        else if (choice == 2)
        {
            library.searchByAuthor();
        }
        else if (choice == 3)
        {
            library.searchByGenre();
        }
        else if (choice == 4)
        {
            library.borrowBook();
        }
        else if (choice == 5)
        {
            library.returnBook();
        }
        else if (choice == 6) //forgot lmao
        {
            library.checkBorrowed();
        }
        else if (choice == 7)
        {
            library.displayCatalogue();
        }
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);
    
    std::cout << "Thank you for using" << std::endl;
    return;
}

void librarianMenu(const TempUser& user, LibraryService& library)
{
    int choice;
    do
    {
        std::cout << "\nWelcome, librarian: " << user.name << std::endl;
        std::cout << "1. search book by title" << std::endl;
        std::cout << "2. search book by author" << std::endl;
        std::cout << "3. search book by genre" << std::endl;
        std::cout << "4. Borrow book" << std::endl;
        std::cout << "5. Return book" << std::endl;
        std::cout << "6. Check borrowed book" << std::endl;
        std::cout << "7. Add book" << std::endl;
        std::cout << "8. Remove book" << std::endl;
        std::cout << "9. Register member" << std::endl;
        std::cout << "10. Remove member" << std::endl;
        std::cout << "11. Fine calculation" << std::endl;
        std::cout << "12. display catalogue" << std::endl;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            library.searchByTitle();
        }
        else if (choice == 2)
        {
            library.searchByAuthor();
        }
        else if (choice == 3)
        {
            library.searchByGenre();
        }
        else if (choice == 4)
        {
            library.borrowBook();
        }
        else if (choice == 5)
        {
            library.returnBook();
        }
        else if (choice == 6) //forgot lmao
        {
            library.checkBorrowed();
        }
        else if (choice == 7)
        {
            library.addBook();
        }
        else if (choice == 8)
        {
            library.removeBook();
        }
        else if (choice == 9)
        {
            library.registerMember();
        }
        else if (choice == 10)
        {
            library.removeMember();
        }
        else if (choice == 11)
        {
            library.calculateFine();
        }
        else if (choice == 12)
        {
            library.displayCatalogue();
        }
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

    LibraryService library;

    //leads users to respective menu, from there they can do actions within the system
    if (currentUser->role == "Guest")
    {
        guestMenu(*currentUser, library);
    }
    else if (currentUser->role == "Member")
    {
        memberMenu(*currentUser, library);
    }
    else if (currentUser->role == "Librarian")
    {
        librarianMenu(*currentUser, library);
    }

    return 0;
}

//test output