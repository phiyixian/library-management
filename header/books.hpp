#ifndef BOOKS_HPP
#define BOOKS_HPP

#include <string>
#include <ctime>

//Book node structure for linked list
struct BookNode
{
    std::string id;           // Book ID (format: A001, B002, etc.)
    std::string title;    
    std::string author;     
    std::string genre;       
    std::string dateAdded;    
    std::string lastUpdated; 
    int borrowCount;         
    bool is_borrowed;       
    std::string status;     
    
    BookNode *next;    
    BookNode *prev;           
    
    // Constructor
    BookNode() : borrowCount(0), is_borrowed(false), next(nullptr), prev(nullptr) {}
};

// Linked list class for managing books
class BookList
{
    private:
        BookNode *head;      
        //Number of books in the list
        int count;            
        
    public:
        //Constructor/Destructor
        BookList();
        ~BookList();
        
        //Load and Save functions
        void loadFromFile(const std::string &filepath);
        void saveToFile(const std::string &filepath);
        
        //Search functions
        BookNode* searchByID(const std::string &id);
        BookNode* searchByTitle(const std::string &title);
        BookNode* searchByAuthor(const std::string &author);
        BookNode* searchByGenre(const std::string &genre);
        
        //Add and Remove functions
        bool addBook(const std::string &id, const std::string &title, 
                     const std::string &author, const std::string &genre);
        bool removeBook(const std::string &id);
        
        // Generate next available book ID
        std::string generateNextID() const;
        
        // Update functions
        bool updateBookStatus(const std::string &id, bool is_borrowed, const std::string &status);
        bool incrementBorrowCount(const std::string &id);
        
        //Display functions
        void displayAll();
        void displayByTitle(const std::string &title);
        void displayByAuthor(const std::string &author);
        void displayByGenre(const std::string &genre);
        
        //Getter functions
        BookNode* getHead() const;
        int getCount() const;
        
        //Check if book exists
        bool bookExists(const std::string &id);
        
        //Get current date/time as string
        std::string getCurrentDate() const;
};

#endif
