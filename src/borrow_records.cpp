#include "../header/borrow_records.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

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

        // check if member has more than one borrow history
        if(borrowHead->next == NULL){
            borrowHead->next = newRecord;
            newRecord->prev = borrowHead;
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

void linkedRecords::remove(int book_ID){
    record *temp;
    temp = borrowHead;
    while(temp != NULL){
        if(temp->book_ID == book_ID){
            if(temp->overdue){
                cout << "Your borrowed book is overdue." << endl;
                cout << "Please pay your fine before you return your book." << endl;

                // Display overdue days and fine charged
                int overdue_Days = overdueDays(temp->dueDate);
                cout << "Overdue by " << overdue_Days << " days\n";

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
