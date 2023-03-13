#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
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
//    UserDatabase udb;
//    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
//    {
//        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//        return 1;
//    }
//
    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))
    {
        cout << "Failed to load movie file" <<endl;
        return 1;
    }
    
    for (;;)
    {
        cout << "Enter MovieID or quit";
        string movieID;
        getline(cin, movieID);
        if (movieID == "quit")
            return  0;

        Movie* m = mdb.get_movie_from_id(movieID);
        if (m == nullptr)
            cout << "No movie in the database has that ID" <<endl;
        else
            cout << "Found " << m->get_title() <<endl;
        
//        cout << "Enter user email address (or quit): ";
//        string email;
//        getline(cin, email);
//        if (email == "quit")
//            return 0;
//        User* u = udb.get_user_from_email(email);
//        if (u == nullptr)
//            cout << "No user in the database has that email address." << endl;
//        else
//            cout << "Found " << u->get_full_name() << endl;
    }

    
}
