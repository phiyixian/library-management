#include "../header/library_service.hpp"
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

//member + librarian

bool LibraryService::borrowBook()
{
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
    }

    std::cout << "Error, book does not exist" << std::endl;
    return false;
}

bool LibraryService::returnBook()
{
    std::string return_book_id;
    std::cout << "enter book id: ";
    std::cin >> return_book_id;

    for (Book& book : books)
    {
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
    return false;
}

//later

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
    for (const Book& book : books)
    {
        if (book.id == new_book.id)
        {
            std::cout << "error. book id already exists" << std::endl;
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
