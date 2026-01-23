#include "../header/reservation_queue.hpp"
#include "../header/utility.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <cctype>

ReservationQueue::ReservationQueue() : front(nullptr), rear(nullptr), count(0) {}

ReservationQueue::~ReservationQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

void ReservationQueue::enqueue(const std::string &memberID, const std::string &bookID, time_t reservationDate)
{
    ReservationNode *newNode = new ReservationNode(memberID, bookID, reservationDate);
    
    if (rear == nullptr)
    {
        // Queue is empty
        front = rear = newNode;
    }
    else
    {
        // Add to rear
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

bool ReservationQueue::dequeue()
{
    if (isEmpty())
    {
        return false;
    }
    
    ReservationNode *temp = front;
    front = front->next;
    
    // If queue becomes empty
    if (front == nullptr)
    {
        rear = nullptr;
    }
    
    delete temp;
    count--;
    return true;
}

ReservationNode* ReservationQueue::peek() const
{
    return front;
}

bool ReservationQueue::isEmpty() const
{
    return front == nullptr;
}

int ReservationQueue::getCount() const
{
    return count;
}

bool ReservationQueue::removeReservation(const std::string &memberID, const std::string &bookID)
{
    if (isEmpty())
    {
        return false;
    }
    
    // If it's the front node
    if (front->memberID == memberID && front->bookID == bookID)
    {
        dequeue();
        return true;
    }
    
    // Search for the node
    ReservationNode *current = front;
    ReservationNode *prev = nullptr;
    
    while (current != nullptr)
    {
        if (current->memberID == memberID && current->bookID == bookID)
        {
            // Found the node to remove
            if (prev != nullptr)
            {
                prev->next = current->next;
            }
            
            // If it's the rear node
            if (current == rear)
            {
                rear = prev;
            }
            
            delete current;
            count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    
    return false;
}

bool ReservationQueue::hasReservation(const std::string &memberID, const std::string &bookID) const
{
    ReservationNode *current = front;
    while (current != nullptr)
    {
        if (current->memberID == memberID && current->bookID == bookID)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

ReservationNode* ReservationQueue::getNextReservation(const std::string &bookID) const
{
    ReservationNode *current = front;
    while (current != nullptr)
    {
        if (current->bookID == bookID)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void ReservationQueue::loadFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        // File doesn't exist yet, that's okay
        return;
    }
    
    std::string line;
    std::getline(file, line);  // Skip header
    
    // Clear existing queue
    while (!isEmpty())
    {
        dequeue();
    }
    
    // Load reservations from file
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::istringstream ss(line);
        std::string memberID, bookID, reservationDateStr;
        
        std::getline(ss, memberID, '|');
        std::getline(ss, bookID, '|');
        std::getline(ss, reservationDateStr, '|');
        
        // Parse time_t from ISO 8601 format string (e.g., 2026-01-08T10:31:28)
        // Also supports Unix timestamp format for backward compatibility
        time_t reservationDate = 0;
        if (!reservationDateStr.empty())
        {
            // Check if it's a pure numeric string (Unix timestamp)
            bool isNumeric = true;
            for (char c : reservationDateStr) {
                if (!std::isdigit(c)) {
                    isNumeric = false;
                    break;
                }
            }
            
            if (isNumeric && reservationDateStr.length() > 10) {
                // Likely a Unix timestamp, parse directly
                try {
                    reservationDate = std::stoll(reservationDateStr);
                } catch (...) {
                    reservationDate = time(nullptr);  // Default to current time if parsing fails
                }
            } else {
                // Try to parse as ISO 8601 format string
                reservationDate = parseTimeFromString(reservationDateStr);
                // If parsing failed (returns -1 or invalid), try Unix timestamp as fallback
                if (reservationDate == -1 || reservationDate == 0) {
                    try {
                        reservationDate = std::stoll(reservationDateStr);
                    } catch (...) {
                        reservationDate = time(nullptr);  // Default to current time if parsing fails
                    }
                }
            }
        }
        
        enqueue(memberID, bookID, reservationDate);
    }
    
    file.close();
}

void ReservationQueue::saveToFile(const std::string &filepath)
{
    const std::string tempPath = filepath + ".tmp";
    std::ofstream file(tempPath);
    
    if (!file)
    {
        std::cerr << "Error: Cannot create temporary file for writing reservations" << std::endl;
        return;
    }
    
    // Write header
    file << "Member ID|Book ID|Reservation Date|\n";
    
    // Write all reservations
    ReservationNode *current = front;
    while (current != nullptr)
    {
        file << current->memberID << "|"
             << current->bookID << "|"
             << parseTimeIntoString(current->reservationDate) << "|\n";
        
        current = current->next;
    }
    
    file.close();
    
    // Replace original file with temporary file
    std::error_code ec;
    std::filesystem::remove(filepath, ec);
    std::filesystem::rename(tempPath, filepath, ec);
    
    if (ec)
    {
        std::cerr << "Error: Failed to replace reservations file: " << ec.message() << std::endl;
    }
}

void ReservationQueue::displayReservations(const std::string &bookID) const
{
    bool found = false;
    ReservationNode *current = front;
    
    std::cout << "\nReservations for Book ID " << bookID << ":\n";
    std::cout << std::string(50, '-') << std::endl;
    
    int position = 1;
    while (current != nullptr)
    {
        if (current->bookID == bookID)
        {
            found = true;
            std::cout << "Position: " << position << std::endl;
            std::cout << "Member ID: " << current->memberID << std::endl;
            std::cout << "Reservation Date: " << formatDateForDisplay(current->reservationDate) << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            position++;
        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "No reservations found for this book." << std::endl;
    }
}

void ReservationQueue::displayMemberReservations(const std::string &memberID) const
{
    bool found = false;
    ReservationNode *current = front;
    
    std::cout << "\nYour Reservations:\n";
    std::cout << std::string(50, '-') << std::endl;
    
    while (current != nullptr)
    {
        if (current->memberID == memberID)
        {
            found = true;
            std::cout << "Book ID: " << current->bookID << std::endl;
            std::cout << "Reservation Date: " << formatDateForDisplay(current->reservationDate) << std::endl;
            
            // Count position in queue for this book
            int position = 1;
            ReservationNode *temp = front;
            while (temp != current)
            {
                if (temp->bookID == current->bookID)
                {
                    position++;
                }
                temp = temp->next;
            }
            std::cout << "Your Position in Queue: " << position << std::endl;
            std::cout << std::string(50, '-') << std::endl;
        }
        current = current->next;
    }
    
    if (!found)
    {
        std::cout << "You have no active reservations." << std::endl;
    }
}

ReservationNode* ReservationQueue::getFront() const
{
    return front;
}

