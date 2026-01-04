#ifndef BORROW_RECORDS_HPP
#define BORROW_RECORDS_HPP

#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct record
{
    string book_ID;
    time_t borrowDate;
    time_t dueDate;
    bool overdue;
    record *next;
    record *prev;
};

class linkedRecords
{
    private:
        string member_ID;
        record *borrowHead;
    public:
        linkedRecords(string member_ID);
        
        record* getHead();
        string getID();

        void load();
        void save();
        void updateStatus();

        void insert(string book_ID, time_t borrowDate, time_t dueDate, bool overdue);
        void remove(string book_ID);

        void printRecords();
        void printRecord(string book_ID);
        int getRecordCount();
        record* getRecordByBookID(string book_ID);

        void checkOverdues();
        void checkOverdue(string book_ID);

        double calculateTotalFines();

        int overdueDays(time_t dueDate);
        double calculateFine(int overdueDays);
};

#endif