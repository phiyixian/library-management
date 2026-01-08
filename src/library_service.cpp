#include "../header/library_service.hpp"
<<<<<<< Updated upstream
#include <iostream>
#include <string>
#include <vector> //temporary header for books
=======
#include "../header/borrow_records.hpp"
#include "../header/books.hpp"
#include "../header/librarian.hpp"
#include "../header/member.hpp"
#include "../header/person.hpp"
#include "../header/utility.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

// Constructor - load books from database file
LibraryService::LibraryService()
{
    // Load books from database file
    books.loadFromFile("database/books_database.txt");
}

//all users

void LibraryService::searchByTitle()
{
    std::string keyword_title;
    std::cout << "Enter title of book: ";
    std::getline(std::cin, keyword_title); //getline to include space

    // Use linked list to search
    books.displayByTitle(keyword_title);
}

void LibraryService::searchByAuthor()
{
    std::string keyword_author;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    std::cout << "Enter author of book: ";
    std::getline(std::cin, keyword_author);
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Search by Author" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter author name: ";
    std::getline(std::cin >> std::ws, keyword_author);
>>>>>>> Stashed changes

    // Use linked list to search
    books.displayByAuthor(keyword_author);
}

void LibraryService::searchByGenre()
{
    std::string keyword_genre;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    std::cout << "Enter genre of book: ";
    std::getline(std::cin, keyword_genre);
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Search by Genre" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter genre: ";
    std::getline(std::cin >> std::ws, keyword_genre);
>>>>>>> Stashed changes

    // Use linked list to search
    books.displayByGenre(keyword_genre);
}

//member + librarian

bool LibraryService::borrowBook()
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Library Catalogue" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    // Use linked list to display all books
    books.displayAll();
}

//--------------------------------
// member + librarian
//--------------------------------
// Prompts the user for book ID to borrow
// Checks the user fine status and borrowing limit
bool LibraryService::borrowBook(Member &user)
{
    const int BORROW_LIMIT = 5;
    const double FINE_LIMIT = 5.0;

    // Update user's borrow history status and total fines before borrowing
    linkedRecords& borrowlist = user.getBorrowHistory();
    borrowlist.updateStatus();
    double totalFines = borrowlist.calculateTotalFines();
    user.setFine(totalFines);
    

    if (user.getFine() > FINE_LIMIT)
    {
        std::cout << "Error, your fine exceeds the limit of RM5. Please pay your fines before borrowing new books." << std::endl;
        return false;
    }

    if (user.getBorrowCount() >= BORROW_LIMIT)
    {
        std::cout << "[ERROR] You have reached your borrowing limit of " << BORROW_LIMIT << " books." << std::endl;
        return false;
    }

    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Borrow Book" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
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
    std::string book_id_borrow;
    std::cout << "Enter book ID: ";
    std::getline(std::cin, book_id_borrow);

    // Validate book by searching book's id using linked list
    BookNode *book = books.searchByID(book_id_borrow);
    
    if (book == nullptr)
    {
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
        if (book.id == book_id_borrow)
        {
            if (book.is_borrowed == true)
            {
                std::cout << "Error, Book is already borrowed" << std::endl;
                return false;
            }
            
            bool borrowing_limit_exceeded = false;
            if (borrowing_limit_exceeded == true)
            {
                std::cout << "Error, borrowing limit exceeded" << std::endl;
                return false;
            }

            //set book borrowing condtiion to true
            book.is_borrowed = true;

            //save borrowing recored and assign due date later

            std::cout << "Book borrowed successfully" << std::endl;
            return true;
        }
=======
        std::cout << "Error, book does not exist" << std::endl;
        return false;
>>>>>>> Stashed changes
=======
        std::cout << "Error, book does not exist" << std::endl;
        return false;
>>>>>>> Stashed changes
=======
        std::cout << "Error, book does not exist" << std::endl;
        return false;
>>>>>>> Stashed changes
=======
        std::cout << "Error, book does not exist" << std::endl;
        return false;
>>>>>>> Stashed changes
    }
    
    if (book->is_borrowed == true)
    {
        std::cout << "Error, Book is already borrowed" << std::endl;
        return false;
    }
    
    // Actually borrowing the book
    time_t borrowTime = time(nullptr);
    time_t dueTime = borrowTime + 14 * 24 * 60 * 60; // 2 weeks due date
    borrowlist.insert(book->id, borrowTime, dueTime, false);
    
    // Save borrow record to active_borrows.txt
    borrowlist.save();
    
    // Save to borrow history
    std::ofstream historyFile("database/borrow_history.txt", std::ios::app);
    if (historyFile)
    {
        historyFile << user.getID() << "|BORROWED|" << book->id << "|"
                    << parseTimeIntoString(borrowTime) << "|"
                    << parseTimeIntoString(dueTime) << "|\n";
        historyFile.close();
    }
    
    // Update book status in linked list
    books.updateBookStatus(book->id, true, "Borrowed");
    books.incrementBorrowCount(book->id);
    // Save changes to file
    books.saveToFile("database/books_database.txt");
    user.borrowIncrement(); // Increment borrow count

    std::cout << "Book borrowed successfully" << std::endl;
    return true;
}

bool LibraryService::returnBook()
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Return Book" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    // Update overdue status before returning
    borrowlist.updateStatus();
    
    // Show borrowed books
    std::cout << "\nYour Current Borrowed Books:\n";
    borrowlist.printRecords();

>>>>>>> Stashed changes
    std::string return_book_id;
    std::cout << "enter book id: ";
    std::cin >> return_book_id;

    for (Book& book : books)
    {
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
        if (book.id == return_book_id)
        {
            if (book.is_borrowed == false)
            {
                std::cout << "Error, book is not borrowed" << std::endl;
                return false;
            }

            //temp bool for overdue, hakim's part
            bool overdue_return = false;
            if (overdue_return == true)
            {
                book.is_borrowed = false;
                std::cout << "Book returned successfully" << std::endl;
                //record return date and fine calculation

                return true;
            }
            else
            {
                book.is_borrowed = false;
                std::cout << "Book returned successfully" << std::endl;
                //record return date

                return true;
            }
        }
    }

    std::cout << "Error, book does not exits" << std::endl;
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
        std::cout << "\nEnter Book ID to return (or 'Q' to cancel): ";
        std::cin >> return_book_id;
        std::cin.ignore(); // Clear the newline character from the buffer

        if (return_book_id == "Q" || return_book_id == "q")
        {
            return false; // User chose to quit
        }

        // Check if the book ID is in the borrow list
        if (borrowlist.getRecordCount() == 0)
        {
            std::cout << "You have no borrowed books." << std::endl;
            return false;
        }

        
        record* current = borrowlist.getRecordByBookID(return_book_id);

        if (current)
        {
            time_t returnTime = time(nullptr);
            
            // Save to borrow history before removing
            borrowlist.saveToHistory(return_book_id, returnTime);
            
            // See if overdue and pay fine if necessary
            if (current->overdue)
            {
                std::cout << "\nThis book is overdue!" << std::endl;
                int overdueDays = borrowlist.overdueDays(current->dueDate);
                double fine = borrowlist.calculateFine(overdueDays);
                std::cout << "Overdue by: " << overdueDays << " days" << std::endl;
                std::cout << "Fine amount: RM" << std::fixed << std::setprecision(2) << fine << std::endl;
                std::cout << "Please proceed to pay the fine." << std::endl;
                double change = payFine(fine, user);
                std::cout << "Thank you for your payment! Your change is RM" << std::fixed << std::setprecision(2) << change << std::endl;
            }
            
            // Remove it from the borrow list (active borrows)
            borrowlist.remove(return_book_id);
            // Save updated active borrows
            borrowlist.save();
            
            // Update book status in linked list
            books.updateBookStatus(return_book_id, false, "Available");
            // Save changes to file
            books.saveToFile("database/books_database.txt");
            
            user.borrowDecrement(); // Decrement borrow count
            std::cout << "\nBook returned successfully!" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Invalid Book ID. Please try again." << std::endl;
        }
    } while (true);
}

bool LibraryService::returnBook(Member &user)
{
    linkedRecords& borrowlist = user.getBorrowHistory();
    return returnBook(borrowlist, user);
}

// Pay the fine for one book
// Returns the change after paying the fine
// And deducts the fine from the user's total fines
double LibraryService::payFine(double fine, Member &user)
{
    double payment;
    while(true){
        payment = 0;
        std::cout << "Payment: RM";
        std::cin >> payment;
        if(payment < fine){
            std::cout << "Insufficient funds!" << std::endl;
        } else if(payment <= 0) {
            std::cout << "Please enter valid amount." << std::endl;
        } else {
            payment -= fine;
            user.decreaseFines(fine);
            break;
        }
    }
    return payment;
}

double LibraryService::payFine(double fine, Librarian &user)
{
    double payment;
    while(true){
        payment = 0;
        std::cout << "Payment: RM";
        std::cin >> payment;
        if(payment < fine){
            std::cout << "Insufficient funds!" << std::endl;
        } else if(payment <= 0) {
            std::cout << "Please enter valid amount." << std::endl;
        } else {
            payment -= fine;
            user.decreaseFines(fine);
            break;
        }
    }
    return payment;
}

void LibraryService::checkBorrowed()
{
    bool found = false;

    std::cout << "Borrowed books:" << std::endl;

    BookNode *current = books.getHead();
    while (current != nullptr)
    {
        if (current->is_borrowed == true)
        {
            found = true;
            std::cout << "ID: " << current->id << std::endl;
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Author: " << current->author << std::endl;
            std::cout << "Genre: " << current->genre << std::endl;
        }
        current = current->next;
    }

    if (found == false)
    {
        std::cout << "no books currently borrowed" << std::endl;
    }
}



//librarian only features;
bool LibraryService::addBook()
{
    std::string id, title, author, genre;
    std::cin.ignore();

    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Add New Book" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    // Ask if user wants to auto-generate ID or enter manually
    char choice;
    std::cout << "Auto-generate book ID? (Y/n): ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice == 'Y' || choice == 'y' || choice == '\n')
    {
        // Auto-generate ID
        id = books.generateNextID();
        std::cout << "Generated Book ID: " << id << std::endl;
    }
    else
    {
        // Manual entry
        std::cout << "Enter book ID (format: A001, B002, etc.): ";
        std::getline(std::cin, id);
        
        // Validate format
        if (id.length() != 4 || !std::isalpha(id[0]) || !std::isdigit(id[1]) || 
            !std::isdigit(id[2]) || !std::isdigit(id[3]))
        {
            std::cout << "[ERROR] Invalid ID format. Must be Letter + 3 digits (e.g., A001)" << std::endl;
            return false;
        }
    }

    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    // Add book to linked list
    if (books.addBook(id, title, author, genre))
    {
        // Save to file
        books.saveToFile("database/books_database.txt");
        std::cout << "\n[SUCCESS] Book added successfully!" << std::endl;
        std::cout << "Book ID: " << id << std::endl;
        std::cout << "Title: " << title << std::endl;
        return true;
    }
    
    return false;
}

bool LibraryService::removeBook()
{
    std::cout << "\n";
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  Remove Book" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::string book_id;
    std::cin.ignore();
    std::cout << "Enter book ID to remove: ";
    std::getline(std::cin, book_id);
    
    // Validate ID format
    if (book_id.length() != 4 || !std::isalpha(book_id[0]) || !std::isdigit(book_id[1]) || 
        !std::isdigit(book_id[2]) || !std::isdigit(book_id[3]))
    {
        std::cout << "[ERROR] Invalid ID format. Must be Letter + 3 digits (e.g., A001)" << std::endl;
        return false;
    }

    // Remove book from linked list
    if (books.removeBook(book_id))
    {
        // Save to file
        books.saveToFile("database/books_database.txt");
        std::cout << "\n[SUCCESS] Book removed successfully!" << std::endl;
        return true;
    }
    
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
    return false;
}

//later
/*
void LibraryService::checkBorrowed()
{}

//librarian only features;
bool LibraryService::addBook()
{}

bool LibraryService::removeBook()
{}

bool LibraryService::registerMember()
<<<<<<< Updated upstream
{}

bool LibraryService::removeMember()
{}

double LibraryService::calculateFine()
{}
*/
=======
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    return false;
}

bool LibraryService::registerMember()
>>>>>>> Stashed changes
{
    std::string username, email;
    
    std::cout << "\n========== Register New Member ==========" << std::endl;
    std::cout << "Enter Username: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    
    std::cout << "Enter Email: ";
    std::getline(std::cin, email);
    
    // Check if username or email already exists
    std::ifstream peopledata("database/people_database.txt");
    if (!peopledata)
    {
        std::cerr << "Error: Cannot open people database\n";
        return false;
    }
    
    std::string line;
    std::getline(peopledata, line); // Skip header
    
    while (std::getline(peopledata, line))
    {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string role, id, name, existingEmail;
        
        std::getline(ss, role, '|');
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, existingEmail, '|');
        
        if (name == username)
        {
            std::cout << "Error: Username already exists!\n";
            peopledata.close();
            return false;
        }
        
        if (existingEmail == email)
        {
            std::cout << "Error: Email already registered!\n";
            peopledata.close();
            return false;
        }
    }
    peopledata.close();
    
    // Find max member ID
    peopledata.open("database/people_database.txt");
    std::getline(peopledata, line); // Skip header
    
    int max_suffix = 0;
    while (std::getline(peopledata, line))
    {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string role, tempid;
        std::getline(ss, role, '|');
        std::getline(ss, tempid, '|');
        
        if (role == "MEMBER" && tempid.length() >= 2)
        {
            try {
                // Handle both old format (M1, M2) and new format (M001, M002)
                int suffix = 0;
                if (tempid.length() == 2)
                {
                    // Old format: M1 -> 1
                    suffix = std::stoi(tempid.substr(1));
                }
                else if (tempid.length() >= 4)
                {
                    // New format: M001 -> 1, M002 -> 2
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
    
    // Generate new ID
    int nextSuffix = max_suffix + 1;
    std::ostringstream idoss;
    idoss << "M" << std::setfill('0') << std::setw(3) << nextSuffix;
    std::string newID = idoss.str();
    
    // Append to file
    std::ofstream outFile("database/people_database.txt", std::ios::app);
    if (!outFile)
    {
        std::cerr << "Error: Cannot append to people database\n";
        return false;
    }
    
    outFile << "\nMEMBER|" << newID << "|" << username << "|" << email;
    outFile.close();
    
    std::cout << "\nMember registered successfully!" << std::endl;
    std::cout << "Member ID: " << newID << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    
    return true;
}

bool LibraryService::removeMember()
{
    std::string memberID;
    
    std::cout << "\n========== Remove Member ==========" << std::endl;
    std::cout << "Enter Member ID to remove: ";
    std::cin.ignore();
    std::getline(std::cin, memberID);
    
    // Check if member has active borrows
    std::ifstream activeBorrows("database/active_borrows.txt");
    if (activeBorrows)
    {
        std::string line;
        std::getline(activeBorrows, line); // Skip header
        while (std::getline(activeBorrows, line))
        {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string memID;
            std::getline(ss, memID, '|');
            
            if (memID == memberID)
            {
                std::cout << "Error: Member has active borrows. Cannot remove member with borrowed books.\n";
                activeBorrows.close();
                return false;
            }
        }
        activeBorrows.close();
    }
    
    // Remove from people database
    const std::string path = "database/people_database.txt";
    const std::string tempPath = path + ".tmp";
    
    std::ifstream ifs(path);
    std::ofstream ofs(tempPath);
    
    if (!ifs || !ofs)
    {
        std::cerr << "Error: Cannot open people database files\n";
        return false;
    }
    
    std::string line;
    bool found = false;
    
    // Copy header
    std::getline(ifs, line);
    ofs << line << "\n";
    
    // Copy all lines except the one to remove
    while (std::getline(ifs, line))
    {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string role, id;
        std::getline(ss, role, '|');
        std::getline(ss, id, '|');
        
        if (role == "MEMBER" && id == memberID)
        {
            found = true;
            continue; // Skip this line
        }
        
        ofs << line << "\n";
    }
    
    ifs.close();
    ofs.close();
    
    if (!found)
    {
        std::filesystem::remove(tempPath);
        std::cout << "Error: Member ID not found!\n";
        return false;
    }
    
    // Replace file
    std::error_code ec;
    std::filesystem::remove(path, ec);
    std::filesystem::rename(tempPath, path, ec);
    
    if (ec)
    {
        std::cerr << "Error: Failed to update people database: " << ec.message() << "\n";
        return false;
    }
    
    std::cout << "\nMember removed successfully!" << std::endl;
    return true;
}

double LibraryService::calculateFine()
{
    std::cout << "to be done later, hakim + phi's part" << std::endl;
    return 0.0;
}

//--------------------------------
// HELPER FUNCTIONS FOR LOADING AND SAVING BOOKS & PEOPLE
//--------------------------------
// Load books from file - now uses linked list
void LibraryService::loadBooksFromFile()
{
    books.loadFromFile("database/books_database.txt");
}

// Save books to file - now uses linked list
void LibraryService::saveBooksToFile()
{
    books.saveToFile("database/books_database.txt");
}

// INCOMPLETE
void LibraryService::loadPeopleFromFile()
{
    // Load people from file
    std::fstream peopledata("../database/people_database.txt", std::ios::in);
    if (!peopledata)
    {
        std::cerr << "loadPeopleFromFile(): Error loading active borrowing history\n";
        std::exit(1);
    }
    // Role|ID|Username|Email|
    std::string line;
    std::getline(peopledata, line); // Skip header

    // Loading loop
    while (std::getline(peopledata, line))
    {
        std::istringstream ss(line);
        std::string role, id, username, email;

        std::getline(ss, role, '|');
        std::getline(ss, id, '|');
        std::getline(ss, username, '|');
        std::getline(ss, email, '|');
        
        
    }
    peopledata.close();
}

// INCOMPLETE
void LibraryService::savePeopleToFile()
{
    // Save people to file
    std::ofstream ofs("../database/people_database.txt");
    if (!ofs) {
        std::cerr << "savePeopleToFile(): Error opening file for writing\n";
        std::exit(1);
    }
    
    // Write header
    ofs << "Role|ID|Username|Email|\n";

    // Writing loop
    // To be implemented

    ofs.close();
}
>>>>>>> Stashed changes
