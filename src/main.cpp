#include <iostream>
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include <fstream>
#include <string>
#include <limits>
#include <vector> //temporary for storing user files
=======
#include <string>
#include <limits>
#include <iomanip>
>>>>>>> Stashed changes
=======
#include <string>
#include <limits>
#include <iomanip>
>>>>>>> Stashed changes
=======
#include <string>
#include <limits>
#include <iomanip>
>>>>>>> Stashed changes
=======
#include <string>
#include <limits>
#include <iomanip>
>>>>>>> Stashed changes
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
void guestMenu(const TempUser& user, LibraryService& library)
{
    int choice;
    do
    {
        std::cout << "guest menu" << std::endl;
        std::cout << "1. search book by title" << std::endl;
        std::cout << "2. search book by author" << std::endl;
        std::cout << "3. search book by genre" << std::endl;
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
        std::cout << "6. Add book" << std::endl;
        std::cout << "7. Remove book" << std::endl;
        std::cout << "8. Register member" << std::endl;
        std::cout << "9. Remove member" << std::endl;
        std::cout << "10. Fine calculation" << std::endl;
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
        /*
        else if (choice == 6) //forgot lmao
        {
        }
        else if (choice == 7)
        {
            library.removeBook();
        }
        else if (choice == 8)
        {
            library.registerMember();
        }
        else if (choice == 9)
        {
            library.removeMember();
        }
        else if (choice == 10)
        {
            library.calculateFine();
        }
        */
        else if (choice == 0)
        {
            break;
        }
    } while (choice != 0);
}

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(35) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSeparator()
{
    std::cout << std::string(50, '-') << std::endl;
}

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(35) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSeparator()
{
    std::cout << std::string(50, '-') << std::endl;
}

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(35) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSeparator()
{
    std::cout << std::string(50, '-') << std::endl;
}

void printHeader(const std::string &title)
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::setw(35) << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printSeparator()
{
    std::cout << std::string(50, '-') << std::endl;
}

int main()
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
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
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    int choice;
    Person *user = nullptr;
    LibraryService library;

    printHeader("Library Management System");
    std::cout << "\n1. Register (New Member)" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Continue as Guest" << std::endl;
    std::cout << "0. Exit" << std::endl;
    printSeparator();
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1: // Register
        printHeader("Member Registration");
        user = registerUser("MEMBER");
        if (user)
        {
            std::cout << "\n[SUCCESS] Registration successful!\n";
        }
        else
        {
            std::cout << "\n[ERROR] Registration failed. Please try again.\n";
        }
        break;

    case 2: // Login
        printHeader("Login");
        do 
        {
            user = login();
            if (user == nullptr)
            {
                std::cout << "\n[ERROR] ID not found or Username mismatch. Try again." << std::endl;
            }
        } while(user == nullptr);
        
        std::cout << "\n[SUCCESS] Login successful!\n";
        break;

    case 3: // Continue as Guest
        {
        printHeader("Guest Access");
        std::string guestname, guestemail;
        std::cin.ignore();
        std::cout << "Enter Your Name: ";
        std::getline(std::cin, guestname);
        std::cout << "Enter Your Email: ";
        std::getline(std::cin, guestemail);
        
        user = new Guest("GXXX", guestname, guestemail);
        std::cout << "\n[SUCCESS] Continuing as Guest!\n";
        break;
        }
    case 0:
        std::cout << "\nThank you for using Library Management System. Goodbye!\n";
        return 0;
    default:
        std::cout << "\n[ERROR] Invalid option. Please try again." << std::endl;
        return 0;
    }

    if (user)
    {
        user->showMenu(library);
        delete user; // Clean up
    }
    else
    {
        std::cout << "\n[ERROR] No user session started.\n";
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    }

    return 0;
}

//test output