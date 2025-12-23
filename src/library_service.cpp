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
/*
void LibraryService::checkBorrowed()
{}

//librarian only features;
bool LibraryService::addBook()
{}

bool LibraryService::removeBook()
{}

bool LibraryService::registerMember()
{}

bool LibraryService::removeMember()
{}

double LibraryService::calculateFine()
{}
*/