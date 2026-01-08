#include "../header/borrow_records.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
<<<<<<< Updated upstream

using namespace std;
=======
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "borrow_records.hpp"
>>>>>>> Stashed changes

// Initialize new linked list for each member
linkedRecords::linkedRecords(string member_ID, int book_ID){
    this->member_ID = member_ID;

    borrowHead = new record;
    borrowHead->book_ID = book_ID;
    borrowHead->borrowDate = time(nullptr);
    borrowHead->dueDate = borrowHead->borrowDate + 14 * 24 * 60 * 60;
    borrowHead->overdue = false;
    borrowHead->next = NULL;
    borrowHead->prev = NULL;

    fines = 0;
}

void linkedRecords::insert(int book_ID){
    checkOverdues();

    if(fines > 5){
        cout << "Your fine is more than RM5, you are not allowed to borrow anymore books." << endl;
        cout << "Please pay the fines and return the books before you borrow new book." << endl;
    } else {
        // create new borrow record
        record *newRecord = new record;
        newRecord->book_ID = book_ID;
        newRecord->borrowDate = time(nullptr); 
        newRecord->dueDate = newRecord->borrowDate + 14 * 24 * 60 * 60;
        newRecord->overdue = false;
        newRecord->next = NULL;

<<<<<<< Updated upstream
        // check if member has more than one borrow history
        if(borrowHead->next == NULL){
            borrowHead->next = newRecord;
            newRecord->prev = borrowHead;
=======
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
    
    // Format: memberID|Event|bookID|borrowTime|dueTime|
    // Event can be: BORROWED, RETURNED
    historyFile << this->member_ID << "|RETURNED|" << book_ID << "|"
                << parseTimeIntoString(returnedRecord->borrowDate) << "|"
                << parseTimeIntoString(returnedRecord->dueDate) << "|"
                << parseTimeIntoString(returnDate) << "|\n";
    
    historyFile.close();
}

void linkedRecords::updateStatus(){
    // Update overdue status for all borrow records
    record *temp = borrowHead;
    time_t now = time(nullptr);

    while (temp != nullptr) {
        if (now > temp->dueDate) {
            temp->overdue = true;
>>>>>>> Stashed changes
        } else {
            record *temp;
            temp = borrowHead;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newRecord;
            newRecord->prev = temp;
        }
    }
}

<<<<<<< Updated upstream
void linkedRecords::remove(int book_ID){
    record *temp;
    temp = borrowHead;
    while(temp != NULL){
=======
void linkedRecords::remove(std::string book_ID){
    record *temp = borrowHead;
    // Traverse linked list to find book ID
    while(temp != nullptr){
        // When the book is found
>>>>>>> Stashed changes
        if(temp->book_ID == book_ID){
            if(temp->overdue){
                cout << "Your borrowed book is overdue." << endl;
                cout << "Please pay your fine before you return your book." << endl;

                // Display overdue days and fine charged
                int overdue_Days = overdueDays(temp->dueDate);
                cout << "Overdue by " << overdue_Days << " days\n";

<<<<<<< Updated upstream
                double fine = calculateFine(overdue_Days);
                cout << "Fine charged: RM" << fine << endl;

                // Fine payment before returning book
                double change = payFine(fine);
                cout << endl;
                cout << "Thanks for your payment!" << endl;
                cout << "Change: RM" << fine << endl;

                // Remove book from linked list
                if(temp->prev)
                    temp->prev->next = temp->next;

                if(temp->next)
                    temp->next->prev = temp->prev;

                delete temp;

                cout << "Your book has been returned." << endl;
            }
=======
            record *toDelete = temp;
            temp = temp->next; // Move to next before deleting
            delete toDelete;
            return; // Book found and removed
>>>>>>> Stashed changes
        }
        temp = temp->next;
    }
}


void linkedRecords::printRecords(){
    // Display all borrow records for the member
    cout << "All borrow records for " << member_ID << ": " << endl;
    record *temp;
    temp = borrowHead;
    int count = 0;
    while(temp != NULL){
        cout << "Book " << count << ": " << temp->book_ID << endl;
        cout << "Borrow Date: " << ctime(&temp->borrowDate) << endl;
        cout << "Due Date: " << ctime(&temp->dueDate) << endl;
        if(temp->overdue){
            cout << "Book is overdue!" << endl;
        }
        cout << endl;
        count++;
        temp = temp->next;
    }
}

void linkedRecords::printRecord(int book_ID){
    // print single borrow record based on book ID
    record *temp;
    temp = borrowHead;
    while(temp != NULL){
        if(temp->book_ID == book_ID){
            cout << "Book is found" << ": " << temp->book_ID << endl;
            cout << "Borrow Date: " << ctime(&temp->borrowDate) << endl;
            cout << "Due Date: " << ctime(&temp->dueDate) << endl;
            cout << endl;
        }
        temp = temp->next;
    }
}

// check for all overdues
void linkedRecords::checkOverdues(){
    fines = 0;
    time_t now = time(nullptr);
    cout << "Checking if your borrow history is overdue..." << endl;
    cout << "Date today: " << ctime(&now) << endl;

    record *temp;
    temp = borrowHead;

    while(temp != NULL){
        // check if due date has passed
        if(now > temp->dueDate){
            temp->overdue = true;
            cout << "Your book is overdue! Details: " << endl;
            cout << "Book" << ": " << temp->book_ID << endl;
            cout << "Borrow Date: " << ctime(&temp->borrowDate) << endl;
            cout << "Due Date: " << ctime(&temp->dueDate) << endl;

            // print number of days overdue
            int overdue_Days = overdueDays(temp->dueDate);
            cout << "Overdue by " << overdue_Days << " days\n";

            double fine = calculateFine(overdue_Days);
            cout << "Fine charged: RM" << fine << endl;
            fines += fine;
        } else {
            temp->overdue = false;
        }
        temp = temp->next;
    }

    cout << "Total fines charged: RM" << fines << endl;
    if(fines == 0){
        cout << "Thanks for returning your books on time!";
    } else {
        cout << "Remember to return your book next time!";
    }

}

int linkedRecords::overdueDays(time_t dueDate){
    time_t now = time(nullptr);
    return (now - dueDate) / (24 * 60 * 60);
}

double linkedRecords::calculateFine(int overdueDays){
    return overdueDays * 0.5;
}

double linkedRecords::payFine(int fine){
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
            fines -= fine;
            break;
        }
    }
    return payment;
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
