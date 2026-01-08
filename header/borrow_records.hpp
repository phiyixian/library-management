#ifndef BORROW_RECORDS_HPP
#define BORROW_RECORDS_HPP

#include <string>
#include <vector>
#include <ctime>


struct record
{
    std::string book_ID;
    time_t borrowDate;
    time_t dueDate;
    bool overdue;
    record *next;
    record *prev;
};

class linkedRecords
{
    private:
        std::string member_ID;
        record *borrowHead;
    public:
        linkedRecords(std::string member_ID);
        
        std::string getID();

        void load();
        void save();
        void updateStatus();

        void insert(std::string book_ID, time_t borrowDate, time_t dueDate, bool overdue);
        void remove(std::string book_ID);

        void printRecords();
        void printRecord(std::string book_ID);
        int getRecordCount();
        record* getRecordByBookID(std::string book_ID);

        void checkOverdues();
        void checkOverdue(std::string book_ID);

        double calculateTotalFines();

        int overdueDays(time_t dueDate);
        double calculateFine(int overdueDays);
};

#endif