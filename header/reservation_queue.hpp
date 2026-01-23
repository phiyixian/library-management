#ifndef RESERVATION_QUEUE_HPP
#define RESERVATION_QUEUE_HPP

#include <string>
#include <ctime>

// Node structure for queue (linked list implementation)
struct ReservationNode
{
    std::string memberID;
    std::string bookID;
    time_t reservationDate;
    ReservationNode *next;
    
    // Constructor
    ReservationNode(const std::string &memberID, const std::string &bookID, time_t reservationDate)
        : memberID(memberID), bookID(bookID), reservationDate(reservationDate), next(nullptr) {}
};

// Queue class for managing book reservations
class ReservationQueue
{
    private:
        ReservationNode *front;  // Front of the queue
        ReservationNode *rear;   // Rear of the queue
        int count;               // Number of reservations in queue
        
    public:
        // Constructor/Destructor
        ReservationQueue();
        ~ReservationQueue();
        
        // Queue operations
        void enqueue(const std::string &memberID, const std::string &bookID, time_t reservationDate);
        bool dequeue();  // Removes front element
        ReservationNode* peek() const;  // Returns front element without removing
        
        // Check if queue is empty
        bool isEmpty() const;
        
        // Get count
        int getCount() const;
        
        // Find and remove specific reservation
        bool removeReservation(const std::string &memberID, const std::string &bookID);
        
        // Check if member has reservation for a book
        bool hasReservation(const std::string &memberID, const std::string &bookID) const;
        
        // Get next reservation for a book (front of queue for that book)
        ReservationNode* getNextReservation(const std::string &bookID) const;
        
        // Load and Save functions
        void loadFromFile(const std::string &filepath);
        void saveToFile(const std::string &filepath);
        
        // Display all reservations for a book
        void displayReservations(const std::string &bookID) const;
        
        // Display all reservations for a member
        void displayMemberReservations(const std::string &memberID) const;
        
        // Get front node (for iteration)
        ReservationNode* getFront() const;
};

#endif

