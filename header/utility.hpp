#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "person.hpp"
#include "member.hpp"
#include "guest.hpp"
#include "librarian.hpp"
#include "library_service.hpp"
#include "borrow_records.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Person *registerUser();

Person *loginUser();

std::string borrowStatus(bool overdue);

time_t parseTimeFromString(const std::string &dateTimeString);
const std::string parseTimeIntoString(time_t t);

#endif