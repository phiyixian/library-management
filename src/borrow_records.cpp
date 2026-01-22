#include "../header/borrow_records.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../header/utility.hpp"
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>

// test
constexpr int LOAN_DURATION_SECONDS = 60;
constexpr int FINE_INTERVAL_SECONDS = 60;

//actual
/*
constexpr int LOAN_DURATION_SECONDS = 60;
constexpr int LOAN_INTERVAL_SECONDS = 60;
*/

// Initialize new linked list for each member
linkedRecords::linkedRecords(std::string member_ID) : member_ID(member_ID) {
    borrowHead = nullptr;
    load();
    updateStatus();
}

// Returns the ID of the member / librarian whom the linked list of history belongs to
std::string linkedRecords::getID()
{
    return member_ID;
}

void linkedRecords::load(){
    // Load active borrowing records from file
    std::fstream borrowdata("database/active_borrows.txt", std::ios::in);
    if (!borrowdata)
    {
        std::cerr << "load(): Error loading active borrowing history\n";
        std::exit(1);
    }

    std::string line;
    std::getline(borrowdata, line); // Skip header

    // Loading loop
    while (std::getline(borrowdata, line))
    {
        std::istringstream ss(line);
        std::string memberID;

        std::getline(ss, memberID, '|');

        if (memberID == this->member_ID)
        {
            std::string book_ID, borrowDate, dueDate, status;
            std::getline(ss, book_ID, '|');
            std::getline(ss, borrowDate, '|');
            std::getline(ss, dueDate, '|');
            std::getline(ss, status, '|');

            insert(book_ID, parseTimeFromString(borrowDate), parseTimeFromString(dueDate), status == "OVERDUE");
        }
    }
}

void linkedRecords::save(){
    // Save borrowing records to database
    //
    // Save borrowDate and dueDate as so
    //
    // convert time_t to string for saving
    const std::string path = "database/active_borrows.txt";
    const std::string tempPath = path + ".tmp";

    std::ifstream ifs(path);
    std::ofstream ofs(tempPath);
    if (!ofs) {
        std::cerr << "save(): Error opening temporary file for writing\n";
        std::exit(1);
    }

    // Write header to temp file
    ofs << "memberID|bookID|borrowDate|dueDate|Status|\n";

    // Copy all lines except those belonging to this member
    std::string line;
    const std::string prefix = this->member_ID + "|";

    if (ifs) {
        std::getline(ifs, line); // Skip header from original file
        while (std::getline(ifs, line)) {
            if (line.rfind(prefix, 0) == 0) {
                // skip lines that start with "memberID|"
                continue;
            }
            ofs << line << "\n";
        }
        ifs.close();
    } else {
        std::cerr << "save(): Error opening active borrow file for reading\n";
        // Don't exit, just proceed with writing current records if file doesn't exist
    }

    // Append this member's current active borrows
    record *temp = borrowHead;
    while (temp != nullptr) {
        std::string status = borrowStatus(temp->overdue);
        ofs << this->member_ID << "|" << temp->book_ID << "|"
            << parseTimeIntoString(temp->borrowDate) << "|"
            << parseTimeIntoString(temp->dueDate) << "|"
            << status << "|\n";
        temp = temp->next;
    }

    ofs.close();

    std::error_code ec;

    // 1. Remove the old file if it exists
    std::filesystem::remove(path, ec);

    // 2. Rename the temp file to the original path
    std::filesystem::rename(tempPath, path, ec);

    if (ec) {
        std::cerr << "save(): Critical error during file swap: " << ec.message() << "\n";
    }
}

void linkedRecords::updateStatus(){
    // Update overdue status for all borrow records
    record *temp = borrowHead;
    time_t now = time(nullptr);

    while (temp != nullptr) {
        if (now > temp->dueDate) {
            temp->overdue = true;
        } else {
            temp->overdue = false;
        }
        temp = temp->next;
    }
}

void linkedRecords::insert(std::string book_ID, time_t borrowDate, time_t dueDate, bool overdue){
    // Insert new borrow record at the end of linked list

    // create new borrow record
    record *newRecord = new record;
    newRecord->book_ID = book_ID;
    newRecord->borrowDate = borrowDate;
    newRecord->dueDate = dueDate;
    newRecord->overdue = overdue;
    newRecord->next = nullptr;
    newRecord->prev = nullptr;

    // check if member has more than one borrow history
    if(borrowHead == nullptr){
        borrowHead = newRecord;
    } else {
        // append to tail
        record *temp;
        temp = borrowHead;
        while(temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newRecord;
        newRecord->prev = temp;
    }
}

void linkedRecords::remove(std::string book_ID){
    record *temp = borrowHead;
    // Traverse linked list to find book ID
    while(temp != nullptr){
        // When the book is found
        if(temp->book_ID == book_ID){
            // Remove book from linked list
            if(temp->prev)
                temp->prev->next = temp->next;
            else
                borrowHead = temp->next;

            if(temp->next)
                temp->next->prev = temp->prev;

            record *toDelete = temp;
            temp = temp->next; // Move to next before deleting
            delete toDelete;
            return; // Book found and removed
        }
        temp = temp->next;
    }
}

// Returns pointer to head of linked list
record* linkedRecords::getHead(){
    return borrowHead;
}

// Returns pointer to the record if found, else nullptr
record* linkedRecords::getRecordByBookID(std::string book_ID){
    record *temp = borrowHead;

    while(temp != nullptr){
        if(temp->book_ID == book_ID){
            return temp;
        }
        temp = temp->next;
    }

    // Return nullptr if not found
    return nullptr;
}

// Print all borrow records in a table format
void linkedRecords::printRecords(){
    // Display all borrow records for the member
    record *temp = borrowHead;

    if (temp == nullptr) {
        std::cout << "You have no books currently borrowed." << std::endl;
        return;
    }

    // 1. Print the Table Header
    std::cout << "\n-------------------------------------------------------------------" << std::endl;
    std::cout << std::left
              << std::setw(10) << "Book ID"
              << std::setw(25) << "Borrow Date"
              << std::setw(25) << "Due Date"
              << std::setw(10) << "Status" << "\n";
    std::cout << "-------------------------------------------------------------------" << std::endl;

    // 2. Iterate and Print Rows
    while (temp != nullptr) {
        std::cout << std::left
                    << std::setw(10) << temp->book_ID
                    << std::setw(25) << formatDateForDisplay(temp->borrowDate)
                    << std::setw(25) << formatDateForDisplay(temp->dueDate) // user friendly display
                    //<< std::setw(25) << parseTimeIntoString(temp->borrowDate) 
                    //<< std::setw(25) << parseTimeIntoString(temp->dueDate)
                    << std::setw(10) << borrowStatus(temp->overdue)
                    << "\n";
        temp = temp->next;
    }
    std::cout << "-------------------------------------------------------------------\n" << std::endl;
}

void linkedRecords::printRecord(std::string book_ID){
    // Display specific borrow record for the book
    bool found = false;
    record *temp = borrowHead;

    // 1. Print the Table Header
    std::cout << "\n-------------------------------------------------------------------" << std::endl;
    std::cout << std::left
              << std::setw(10) << "Book ID"
              << std::setw(25) << "Borrow Date"
              << std::setw(25) << "Due Date"
              << std::setw(10) << "Status" << "\n";
    std::cout << "-------------------------------------------------------------------\n" << std::endl;

    // 2. Iterate and Print Rows
    while (temp != nullptr) {
        if (temp->book_ID == book_ID) {
            found = true;
            std::cout << std::left
                      << std::setw(10) << temp->book_ID
                      << std::setw(25) << parseTimeIntoString(temp->borrowDate)
                      << std::setw(25) << parseTimeIntoString(temp->dueDate)
                      << std::setw(10) << borrowStatus(temp->overdue)
                      << "\n";
        }
        temp = temp->next;
    }

    if (!found) {
        std::cout << "No records found for Book ID: " << book_ID << "\n";
    }
    std::cout << "-------------------------------------------------------------------\n" << std::endl;
}

// Returns the number of borrow records in the linked list
int linkedRecords::getRecordCount() {
    int count = 0;
    record *temp = borrowHead;

    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// check for all overdues
void linkedRecords::checkOverdues(){
    double fines = 0;
    time_t now = time(nullptr);
    std::cout << "Checking if your borrow history is overdue..." << std::endl;
    std::cout << "Date today: " << ctime(&now) << std::endl;

    record *temp;
    temp = borrowHead;

    while(temp != nullptr){
        // check if due date has passed
        if(now > temp->dueDate){
            temp->overdue = true;
            std::cout << "Your book is overdue! Details: " << std::endl;
            std::cout << "Book" << ": " << temp->book_ID << std::endl;
            std::cout << "Borrow Date: " << ctime(&temp->borrowDate) << std::endl;
            std::cout << "Due Date: " << ctime(&temp->dueDate) << std::endl;

            // print number of days overdue
            int overdue_Days = overdueDays(temp->dueDate);
            std::cout << "Overdue by " << overdue_Days << " days" << std::endl;

            double fine = calculateFine(overdue_Days);
            std::cout << "Fine charged: RM" << fine << std::endl;
            fines += fine;
        } else {
            temp->overdue = false;
        }
        temp = temp->next;
    }

    std::cout << "Total fines charged: RM" << fines << std::endl;
    if(fines == 0){
        std::cout << "Thanks for returning your books on time!";
    } else {
        std::cout << "Remember to return your book next time!";
    }

}

// Check if a specific book is overdue
void linkedRecords::checkOverdue(std::string book_ID){
    record *temp = borrowHead;
    time_t now = time(nullptr);

    while(temp != nullptr){
        if(temp->book_ID == book_ID){
            if(now > temp->dueDate){
                temp->overdue = true;
                int overdue_Days = overdueDays(temp->dueDate);
                double fine = calculateFine(overdue_Days);
                std::cout << "Book " << book_ID << " is overdue by " << overdue_Days << " days." << std::endl;
                std::cout << "Fine charged: RM" << fine << std::endl;
            } else {
                temp->overdue = false;
                std::cout << "Book " << book_ID << " is not overdue." << std::endl;
            }
            return;
        }
        temp = temp->next;
    }
    std::cout << "Book " << book_ID << " not found in borrow records." << std::endl;
}

// Calculate number of overdue days
int linkedRecords::overdueDays(time_t dueDate)
{
    time_t now = time(nullptr);
    if (now <= dueDate)
    {
        return 0;
    }
    int days =  (now - dueDate) / FINE_INTERVAL_SECONDS;

    return std::max(days, 0);
}

// Calculate fine based on number of overdue days
double linkedRecords::calculateFine(int overdueDays){
    return overdueDays * 0.5;
}

// Calculate total fines for all overdue books
double linkedRecords::calculateTotalFines(){
    double totalFines = 0;
    record *temp = borrowHead;

    while(temp != nullptr){
        if(temp->overdue){
            int overdue_Days = overdueDays(temp->dueDate);
            double fine = calculateFine(overdue_Days);
            totalFines += fine;
        }
        temp = temp->next;
    }
    return totalFines;
}

// Save returned book to borrow history file
void linkedRecords::saveToHistory(const std::string &book_ID, time_t returnDate)
{
    // Find the record before removing it
    record *returnedRecord = getRecordByBookID(book_ID);
    if (returnedRecord == nullptr)
    {
        return; // Record not found
    }
    
    // Append to borrow history file
    std::ofstream historyFile("database/borrow_history.txt", std::ios::app);
    if (!historyFile)
    {
        std::cerr << "Error: Cannot open borrow_history.txt for writing\n";
        return;
    }
    
    // Format: memberID|Event|bookID|borrowTime|dueTime|returnTime|
    // Event can be: BORROWED, RETURNED
    historyFile << this->member_ID << "|RETURNED|" << book_ID << "|"
                << parseTimeIntoString(returnedRecord->borrowDate) << "|"
                << parseTimeIntoString(returnedRecord->dueDate) << "|"
                << parseTimeIntoString(returnDate) << "|\n";
    
    historyFile.close();
}
