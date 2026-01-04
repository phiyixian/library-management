#include "../header/library_service.hpp"
#include "../header/borrow_records.hpp"
#include "../header/librarian.hpp"
#include "../header/member.hpp"
#include "../header/person.hpp"
#include "../header/utility.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector> //temporary header for books

//temp vector to store books
LibraryService::LibraryService()
{
    books.push_back(Book{"1", "Dune", "Frank Herbert", "Sci-Fi", false});
    books.push_back(Book{"2", "1984", "George Orwell", "Dystopian", false});
    books.push_back(Book{"3", "Clean Code", "Robert Martin", "Programming", false});
}

//all users

void LibraryService::searchByTitle()
{
    std::string keyword_title;
    std::cout << "Enter title of book: ";
    std::getline(std::cin, keyword_title); //getline to include space

    bool found = false;

    //EDIT SO IT CHECKS .TXT FILE
    for (const Book& book : books)
    {
        if (book.title == keyword_title)
        {
            found = true;
            std::cout << "ID: " << book.id << std::endl;
            std::cout << "Title: " << book.title << std::endl;
            std::cout << "author: " << book.author << std::endl;
            std::cout << "genre: " << book.genre << std::endl;
        }
    }

    if (found == false)
    {
        std::cout << "No books found" << std::endl;
    }
}

void LibraryService::searchByAuthor()
{
    std::string keyword_author;
    std::cout << "Enter author of book: ";
    std::getline(std::cin, keyword_author);

    bool found = false;

    //EDIT SO IT CHECK .TXT FILE
    for (const Book& book : books)
    {
        if (book.author == keyword_author)
        {
            found = true;
            std::cout << book.title << " by " << book.author << std::endl;
        }
    }

    if (found == false)
    {
        std::cout << "No books found" << std::endl;
    }
}

void LibraryService::searchByGenre()
{
    std::string keyword_genre;
    std::cout << "Enter genre of book: ";
    std::getline(std::cin, keyword_genre);

    bool found = false;

    //EDIT SO IT CHECKS .TXT FILE
    for (const Book& book : books)
    {
        if (book.genre == keyword_genre)
        {
            found = true;
            std::cout << book.title << "(" << book.genre << ")" << std::endl;
        }
    }

    if (found == false)
    {
        std::cout << "No books found" << std::endl;
    }
}

void LibraryService::displayCatalogue()
{
    for (const Book& book : books)
    {
        std::cout << "\nID: " << book.id << std::endl;
        std::cout << "Title: " << book.title << std::endl;
        std::cout << "author: " << book.author << std::endl;
        std::cout << "genre: " << book.genre << std::endl;
    }
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

    if (user.getBorrowCount() == BORROW_LIMIT)
    {
        std::cout << "Error, you have reached your borrowing limit of " << BORROW_LIMIT << " books." << std::endl;
        return false;
    }

    std::string book_id_borrow;
    std::cout << "Enter book ID: ";
    std::getline(std::cin, book_id_borrow);

    //validate book by searching book's id
    //EDIT SO IT CHECK FROM .TXT FILE
    for (Book& book : books)
    {
        if (book.id == book_id_borrow)
        {
            if (book.is_borrowed == true)
            {
                std::cout << "Error, Book is already borrowed" << std::endl;
                return false;
            }
            

            // Actually borrowing the book
            borrowlist.insert(book.id, time(nullptr), time(nullptr) + 14 * 24 * 60 * 60, false); // 2 weeks due date
            //set book borrowing condition to true
            book.is_borrowed = true;

            std::cout << "Book borrowed successfully" << std::endl;
            return true;
        }
    }

    std::cout << "Error, book does not exist" << std::endl;
    return false;
}

bool LibraryService::returnBook(linkedRecords &borrowlist, Member &user)
{
    // Here should also include payfine
    borrowlist.updateStatus(); // Update overdue status before returning
    borrowlist.printRecords(); // Show borrowed books

    std::string return_book_id;
    do
    {
        std::cout << "Enter Book ID or 'Q' to back: ";
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
            // Return the book

            // See if overdue and pay fine if necessary
            if (current->overdue)
            {
                std::cout << "This book is overdue. Please proceed to pay the fine." << std::endl;
                double change = payFine(borrowlist.calculateFine(borrowlist.overdueDays(current->dueDate)), user);
                std::cout << "Thank you for your payment! Your change is RM" << change << std::endl;
            }
            // Remove it from the linked list
            borrowlist.remove(return_book_id);
        }
        else
        {
            std::cout << "Invalid Book ID. Please try again." << std::endl;
        }
    } while (true);
}

// Pay the fine for one book
// Returns the change after paying the fine
// And deducts the fine from the user's total fines
double LibraryService::payFine(double fine, Member &user)
{
    double payment;
    while(true){
        payment = 0;
        cout << "Payment: RM";
        cin >> payment;
        if(payment < fine){
            cout << "Insufficient funds!" << endl;
        } else if(payment <= 0) {
            cout << "Please enter valid amount." << endl;
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
        cout << "Payment: RM";
        cin >> payment;
        if(payment < fine){
            cout << "Insufficient funds!" << endl;
        } else if(payment <= 0) {
            cout << "Please enter valid amount." << endl;
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

    for (const Book& book : books)
    {
        if (book.is_borrowed == true)
        {
            found = true;
            std::cout << "ID: " << book.id << std::endl;
            std::cout << "Title: " << book.title << std::endl;
            std::cout << "Author: " << book.author << std::endl;
            std::cout << "Genre: " << book.genre << std::endl;
        }
    }

    if (found == false)
    {
        std::cout << "no books currently borrowed" << std::endl;
    }
}



//librarian only features;
bool LibraryService::addBook()
{
    Book new_book;

    std::cout << "Enter book ID: ";
    std::getline(std::cin, new_book.id);

    //check for duplicate first
    books.

    for (const Book& book : books)
    {
        if (book.id == new_book.id)
        {
            std::cout << "error. book IDalready exists" << std::endl;
            return false;
        }
    }

    std::cout << "Enter title: ";
    std::getline(std::cin, new_book.title);
    std::cout << "Enter author: ";
    std::getline(std::cin, new_book.author);
    std::cout << "Enter genre: ";
    std::getline(std::cin, new_book.genre);

    //set the book's borrowing condition to false; not currently borrowed
    new_book.is_borrowed = false;

    //add to books vector; to be edited
    books.push_back(new_book);

    std::cout << "book added" << std::endl;
    return true;
}

bool LibraryService::removeBook()
{
    std::string book_id;
    std::cout << "Enter book ID to remove: ";
    std::getline(std::cin, book_id);

    for (auto delete_key = books.begin(); delete_key != books.end(); delete_key++)
    {
        if (delete_key->id == book_id)
        {
            if (delete_key->is_borrowed == true)
            {
                std::cout << "Error, book is currently borrowed" << std::endl;
                return false;
            }
            else
            {
                books.erase(delete_key);
                std::cout << "Book erased successfully" << std::endl;
                return true;
            }
        }
    }

    std::cout << "Book does not exist" << std::endl;
    return false;
}

bool LibraryService::registerMember()
{

    std::cout << "to be done later, hakim + phi's part" << std::endl;
    return false;
}

bool LibraryService::removeMember()
{
    std::cout << "to be done later, hakim + phi's part" << std::endl;
    return false;
}

double LibraryService::calculateFine()
{
    std::cout << "to be done later, hakim + phi's part" << std::endl;
    return 0.0;
}

void LibraryService::loadBooksFromFile()
{
    // Load books from file
    std::fstream bookdata("../database/books_database.txt", std::ios::in);
    if (!bookdata)
    {
        std::cerr << "loadBooksFromFile(): Error loading active borrowing history\n";
        std::exit(1);
    }

    std::string line;
    std::getline(bookdata, line);

    // Loading loop
    while (std::getline(bookdata, line))
    {
        std::istringstream ss(line);
        std::string title, bookID, category, dateAdded, lastUpdated, borrowCount, status;

        std::getline(ss, title, '|');
        std::getline(ss, bookID, '|');
        std::getline(ss, category, '|');
        std::getline(ss, dateAdded, '|');
        std::getline(ss, lastUpdated, '|');
        std::getline(ss, borrowCount, '|');
        std::getline(ss, status, '|');

        // Create a new Book object and add it to the books vector
        Book newBook;
        newBook.id = bookID;
        newBook.title = title;
        newBook.author = "Unknown"; // Placeholder for author
        newBook.genre = category;
        newBook.is_borrowed = (status == "BORROWED");

        books.push_back(newBook);
    }

    bookdata.close();
}
