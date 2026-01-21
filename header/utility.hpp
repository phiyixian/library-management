#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <ctime>

// Forward declarations
class Person;

// Function declarations
Person* registerUser(const std::string &userrole);
Person* login();

std::string borrowStatus(bool overdue);
time_t parseTimeFromString(const std::string &dateTimeString);
const std::string parseTimeIntoString(time_t t);
const std::string formatDateForDisplay(time_t t);
#endif

