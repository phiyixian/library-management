#include "../header/books.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <filesystem>
#include <cctype>

BookList::BookList() : head(nullptr), count(0) {}

//destructor
BookList::~BookList()
{
    BookNode *current = head;
    while (current != nullptr)
    {
        BookNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
}

//get current date as string
std::string BookList::getCurrentDate() const
{
    std::time_t now = std::time(nullptr);
    std::tm *timeinfo = std::localtime(&now);
    
    std::ostringstream oss;
    oss << (1900 + timeinfo->tm_year) << "-"
        << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1) << "-"
        << std::setfill('0') << std::setw(2) << timeinfo->tm_mday;
    
    return oss.str();
}

//load books from file
void BookList::loadFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line); 
    
    //clear existing list
    BookNode *current = head;
    while (current != nullptr)
    {
        BookNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
    
    //load books from file
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::istringstream ss(line);
        std::string title, author, genre, id, dateAdded, lastUpdated, borrowCountStr, status;
        
        std::getline(ss, title, '|');
        std::getline(ss, author, '|');
        std::getline(ss, genre, '|');
        std::getline(ss, id, '|');
        std::getline(ss, dateAdded, '|');
        std::getline(ss, lastUpdated, '|');
        std::getline(ss, borrowCountStr, '|');
        std::getline(ss, status, '|');
        
        // Create new book node
        BookNode *newBook = new BookNode();
        newBook->id = id;
        newBook->title = title;
        newBook->author = author;
        newBook->genre = genre;
        newBook->dateAdded = dateAdded;
        newBook->lastUpdated = lastUpdated;
        newBook->borrowCount = (borrowCountStr.empty() ? 0 : std::stoi(borrowCountStr));
        newBook->status = status;
        newBook->is_borrowed = (status == "Borrowed");
        newBook->next = nullptr;
        newBook->prev = nullptr;
        
        //insert at the end of the list
        if (head == nullptr)
        {
            head = newBook;
        }
        else
        {
            BookNode *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newBook;
            newBook->prev = temp;
        }
        count++;
    }
    
    file.close();
}

//Save books to file
void BookList::saveToFile(const std::string &filepath)
{
    const std::string tempPath = filepath + ".tmp";
    std::ofstream file(tempPath);
    
    if (!file)
    {
        std::cerr << "Error: Cannot create temporary file for writing" << std::endl;
        return;
    }
    
    // Write header
    file << "Title|Author|Genre|ID|Date Added|Last Updated|Borrow Count|Status\n";
    
    // Write all books
    BookNode *current = head;
    while (current != nullptr)
    {
        file << current->title << "|"
             << current->author << "|"
             << current->genre << "|"
             << current->id << "|"
             << current->dateAdded << "|"
             << current->lastUpdated << "|"
             << current->borrowCount << "|"
             << current->status << "\n";
        
        current = current->next;
    }
    
    file.close();
    
    //replace original file with temporary file
    std::error_code ec;
    std::filesystem::remove(filepath, ec);
    std::filesystem::rename(tempPath, filepath, ec);
    
    if (ec)
    {
        std::cerr << "Error: Failed to replace file: " << ec.message() << std::endl;
    }
}

//search book by ID
BookNode* BookList::searchByID(const std::string &id)
{
    BookNode *current = head;
    while (current != nullptr)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//search book by title
BookNode* BookList::searchByTitle(const std::string &title)
{
    BookNode *current = head;
    while (current != nullptr)
    {
        if (current->title == title)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//search book by author
BookNode* BookList::searchByAuthor(const std::string &author)
{
    BookNode *current = head;
    while (current != nullptr)
    {
        if (current->author == author)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//search book by genre (returns first match, use displayByGenre for all matches)
BookNode* BookList::searchByGenre(const std::string &genre)
{
    BookNode *current = head;
    while (current != nullptr)
    {
        if (current->genre == genre)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//check if book exists
bool BookList::bookExists(const std::string &id)
{
    return searchByID(id) != nullptr;
}

//generate next available book ID
std::string BookList::generateNextID() const
{
    //find the highest ID in the list
    int maxNum = 0;
    char maxLetter = 'A';
    
    BookNode *current = head;
    while (current != nullptr)
    {
        if (current->id.length() >= 4)
        {
            char letter = current->id[0];
            try {
                int num = std::stoi(current->id.substr(1));
                if (letter > maxLetter || (letter == maxLetter && num > maxNum))
                {
                    maxLetter = letter;
                    maxNum = num;
                }
            } catch (...) {
                // Skip invalid IDs
            }
        }
        current = current->next;
    }
    
    //increment number, or move to next letter if at 999
    if (maxNum >= 999)
    {
        maxLetter++;
        maxNum = 1;
    }
    else
    {
        maxNum++;
    }
    
    std::ostringstream oss;
    oss << maxLetter << std::setfill('0') << std::setw(3) << maxNum;
    return oss.str();
}

//add a new book to the list
bool BookList::addBook(const std::string &id, const std::string &title,
                       const std::string &author, const std::string &genre)
{
    //validate ID format (Letter + 3 digits, e.g., A001)
    if (id.length() != 4 || !std::isalpha(id[0]) || !std::isdigit(id[1]) || 
        !std::isdigit(id[2]) || !std::isdigit(id[3]))
    {
        std::cout << "[ERROR] Invalid book ID format. Must be Letter + 3 digits (e.g., A001, B002)" << std::endl;
        return false;
    }
    
    //check if book ID already exists
    if (bookExists(id))
    {
        std::cout << "[ERROR] Book ID already exists" << std::endl;
        return false;
    }
    
    //create new book node
    BookNode *newBook = new BookNode();
    newBook->id = id;
    newBook->title = title;
    newBook->author = author;
    newBook->genre = genre;
    newBook->dateAdded = getCurrentDate();
    newBook->lastUpdated = getCurrentDate();
    newBook->borrowCount = 0;
    newBook->is_borrowed = false;
    newBook->status = "Available";
    newBook->next = nullptr;
    newBook->prev = nullptr;
    
    //insert at the end of the list
    if (head == nullptr)
    {
        head = newBook;
    }
    else
    {
        BookNode *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newBook;
        newBook->prev = temp;
    }
    count++;
    
    return true;
}

//remove a book from the list
bool BookList::removeBook(const std::string &id)
{
    if (id.length() != 4 || !std::isalpha(id[0]) || !std::isdigit(id[1]) || 
        !std::isdigit(id[2]) || !std::isdigit(id[3]))
    {
        std::cout << "[ERROR] Invalid book ID format. Must be Letter + 3 digits (e.g., A001)" << std::endl;
        return false;
    }
    
    BookNode *current = searchByID(id);
    
    if (current == nullptr)
    {
        std::cout << "[ERROR] Book does not exist" << std::endl;
        return false;
    }
    
    if (current->is_borrowed)
    {
        std::cout << "[ERROR] Book is currently borrowed. Cannot remove borrowed books." << std::endl;
        return false;
    }
    
    // Remove from linked list
    if (current->prev != nullptr)
    {
        current->prev->next = current->next;
    }
    else
    {
        head = current->next;
    }
    
    if (current->next != nullptr)
    {
        current->next->prev = current->prev;
    }
    
    delete current;
    count--;
    
    return true;
}

// Update book status
bool BookList::updateBookStatus(const std::string &id, bool is_borrowed, const std::string &status)
{
    BookNode *book = searchByID(id);
    if (book == nullptr)
    {
        return false;
    }
    
    book->is_borrowed = is_borrowed;
    book->status = status;
    book->lastUpdated = getCurrentDate();
    
    return true;
}

// Increment borrow count
bool BookList::incrementBorrowCount(const std::string &id)
{
    BookNode *book = searchByID(id);
    if (book == nullptr)
    {
        return false;
    }
    
    book->borrowCount++;
    book->lastUpdated = getCurrentDate();
    
    return true;
}

// Display all books
void BookList::displayAll()
{
    if (head == nullptr)
    {
        std::cout << "No books in catalogue." << std::endl;
        return;
    }
    
    BookNode *current = head;
    while (current != nullptr)
    {
        std::cout << "\nID: " << current->id << std::endl;
        std::cout << "Title: " << current->title << std::endl;
        std::cout << "Author: " << current->author << std::endl;
        std::cout << "Genre: " << current->genre << std::endl;
        std::cout << "Status: " << current->status << std::endl;
        std::cout << "Borrow Count: " << current->borrowCount << std::endl;
        current = current->next;
    }
}

// Display books by title
void BookList::displayByTitle(const std::string &title)
{
    bool found = false;
    BookNode *current = head;

    std::cout << "\nBooks found in our library:\n\n";
    
    while (current != nullptr)
    {
        if (current->title == title)
        {
            found = true;
            std::cout << "ID: " << current->id << std::endl;
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Author: " << current->author << std::endl;
            std::cout << "Genre: " << current->genre << std::endl;
            std::cout << "Status: " << current->status << std::endl;
            std::cout << "Borrow Count: " << current->borrowCount << std::endl << std::endl;

        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "No books found" << std::endl;
    }
}

// Display books by author
void BookList::displayByAuthor(const std::string &author)
{
    bool found = false;
    BookNode *current = head;
    
    std::cout << "\nBooks found in our library:\n\n";
    
    while (current != nullptr)
    {
        if (current->author == author)
        {
            found = true;
            std::cout << "ID: " << current->id << std::endl;
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Author: " << current->author << std::endl;
            std::cout << "Genre: " << current->genre << std::endl;
            std::cout << "Status: " << current->status << std::endl;
            std::cout << "Borrow Count: " << current->borrowCount << std::endl << std::endl;
        }
        current = current->next;
    }
        if (!found)
    {
        std::cout << "No books found! Try again.\nHint: Check for any typos." << std::endl;
    }
}

/*{
    bool found = false;
    BookNode *current = head;
    
    while (current != nullptr)
    {
        if (current->author == author)
        {
            found = true;
            std::cout << current->title << " by " << current->author << std::endl;
        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "No books found" << std::endl;
    }
}*/

//display books by genre
void BookList::displayByGenre(const std::string &genre)
{
    bool found = false;
    BookNode *current = head;
    
    std::cout << "\nBooks found in our library:\n\n";
    
    while (current != nullptr)
    {
        if (current->genre == genre)
        {
            found = true;
            std::cout << "ID: " << current->id << std::endl;
            std::cout << "Title: " << current->title << std::endl;
            std::cout << "Author: " << current->author << std::endl;
            std::cout << "Genre: " << current->genre << std::endl;
            std::cout << "Status: " << current->status << std::endl;
            std::cout << "Borrow Count: " << current->borrowCount << std::endl << std::endl;
        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "No books found! Try again.\nHint: Check for any typos." << std::endl;
    }    
}
/*{
    bool found = false;
    BookNode *current = head;
    
    while (current != nullptr)
    {
        if (current->genre == genre)
        {
            found = true;
            std::cout << current->title << " (" << current->genre << ")" << std::endl;
        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "No books found" << std::endl;
    }
}*/

//get head of the list
BookNode* BookList::getHead() const
{
    return head;
}

//get count of books
int BookList::getCount() const
{
    return count;
}

