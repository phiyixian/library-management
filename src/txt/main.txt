#include <iostream>
#include <fstream>
#include <string>
#include "../header/people_database_temp.hpp"
#include "../header/person.hpp"
#include "../header/member.hpp"
#include "../header/guest.hpp"
#include "../header/librarian.hpp"

int main()
{
    using namespace std;

    peopleDatabase pdb;

    // Create objects (dynamic so polymorphism works)
    // person* guest1 = new guest("G001", "Person A", "A@test.com");
    // person* member1 = new member("M001", "Person B", "B@scammer.com");
    // person* member2 = new member("M002", "Person C", "C@idk.com");
    // person* librarian1 = new librarian("L001", "Person D", "D@yeke.com", "Senior Librarian");

    // test 1 add people to database
    // pdb.addPerson(guest1);
    // pdb.addPerson(member1);
    // pdb.addPerson(member2);
    // pdb.addPerson(librarian1);

    std::cout << "\n=== TEST: LISTING ALL PEOPLE ===" << std::endl;;
    pdb.listAll();

    // Test 2 searching
    // std::cout << "\n=== TEST: SEARCH BY ID (M001) ===" << std::endl;
    // person *found_test = pdb.findByID("M001");

    // if (found_test)
    // {
    //     std::cout << "Person found!" << std::endl;
    //     std::cout << "Role: " << found_test->getRole() << std::endl;
    //     found_test->displayInformation();
    // }
    // else
    // {
    //     std::cout << "Person not found." << std::endl;
    // }

    // Test 3 member borrowed count
    // std::cout << "\n=== TEST: Member Borrow Count ===" << std::endl;
    // member *member_test = dynamic_cast<member *>(found_test); //used dynamic_cast than static_cast for going downcasting
    // if (member_test)
    // {
    //     member_test->borrowDecrement();
    //     member_test->borrowIncrement();

    //     std::cout << "Updated borrowed count for " << member_test->getName() << ": " << member_test->getBorrowCount() << std::endl;
    // }

    // Test 4 polymorphism table. annoying af
    // std::cout << "\n=== TEST: Polymorphism ===\n";

    // for (size_t i = 0; i < pdb.size(); i++) 
    // {
    //     person *person_object = pdb.get(i);
    //     person_object->displayInformation();
    //     std::cout << std::endl;
    // }

    // std::cout << "\n=== END OF TESTS ===\n";

    // return 0;
}


//test output