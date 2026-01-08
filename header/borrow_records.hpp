#ifndef BORROW_RECORDS_HPP
#define BORROW_RECORDS_HPP

#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct record
{
    int book_ID;
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
        double fines = 0;
        record *borrowHead;
    public:
        linkedRecords(string member_ID, int book_ID);

<<<<<<< Updated upstream
        void insert(int book_ID);
        void remove(int book_ID);
=======
        void load();
        void save();
        void saveToHistory(const std::string &book_ID, time_t returnDate); // Save to borrow_history.txt
        void updateStatus();

        void insert(std::string book_ID, time_t borrowDate, time_t dueDate, bool overdue);
        void remove(std::string book_ID);
>>>>>>> Stashed changes

        record *getHead();

        record *getHead();

        record *getHead();

        record *getHead();

        void printRecords();
        void printRecord(int book_ID);

        void checkOverdues();
        void checkOverdue(int book_ID);

        void calculateFines();
        double payFine(int fine);

        int overdueDays(time_t dueDate);
        double calculateFine(int overdueDays);
};

#endif