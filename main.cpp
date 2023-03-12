#include "UserDatabase.h"
#include "User.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User

// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/shivanikolla/Desktop/CS32Project4/CS32Project4/users.txt";
const string MOVIE_DATAFILE = "/Users/shivanikolla/Desktop/CS32Project4/CS32Project4/movies.txt";

int main()
{
    UserDatabase udb;
    if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }
    for (;;)
    {
        cout << "Enter user email address (or quit): ";
        string email;
        getline(cin, email);
        if (email == "quit")
            return 0;
        User* u = udb.get_user_from_email(email);
        if (u == nullptr)
            cout << "No user in the database has that email address." << endl;
        else
            cout << "Found " << u->get_full_name() << endl;
    }
//
//    TreeMultimap<std::string, int> tmm;
//    tmm.insert("carey", 5);
//    tmm.insert("carey", 6);
//    tmm.insert("carey", 7);
//    tmm.insert("david", 25);
//    tmm.insert("david", 425);
//    tmm.insert("shivani", 1);
//    tmm.insert("shivani", 3);
//    tmm.insert("shivani", 2);
//    tmm.insert("laura", 3);
//    tmm.insert("srinath", 980);
//    tmm.insert("srinath", 720);
//    tmm.insert("srinath", 240);
//    tmm.insert("ashwin", 70);
//    tmm.insert("ashwin", 80);
//    tmm.insert("ashwin", 90);
//
//    TreeMultimap<std::string,int>::Iterator it = tmm.find("ashwin");
//     // prints 5, 6, and 7 in some order
//     while (it.is_valid())
//     {
//         std::cout << it.get_value() << std::endl;
//         it.advance();
//     }
//
//     it = tmm.find("laura");
//     if (!it.is_valid())
//     std::cout << "laura is not in the multimap!\n";
    
}
