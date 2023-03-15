#include "UserDatabase.h"
#include "User.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "treemm.h"
using namespace std;

UserDatabase::UserDatabase() { }
UserDatabase::~UserDatabase() {
    for (int i=0; i<users.size(); i++) {
    delete users[i];
    }
    users.clear();
}

bool UserDatabase::load(const string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int checkpoint = 0;

    if (infile)
    {
        std::string email;
        std::string name;
        std::string watchHistoryNumber;
        User* user = nullptr;
        while(getline(infile, line)) //read a whole line into line
        {
            if (!line.empty()) //if the line is not empty
            {
                if (checkpoint == 0) { //first check means the line is the name
                    name = line;
                    checkpoint++;
                }
                else if (checkpoint == 1) { //second check means the line is the email
                    email = line;
                    checkpoint++;
                }
                else if (checkpoint == 2) { //means the line is the number of movies the user has watched
                    watchHistoryNumber = line;
                    checkpoint++;
                }
                else if (checkpoint >= 3) //start of the movie ID numbers
                {
                    watchHistory.push_back(line);
                    checkpoint++;
                }
            }
            
            else {
                user = new User(name, email, watchHistory);
                users.push_back(user);
                emailToUser.insert(email, user);
                checkpoint = 0;
                user = nullptr;
                watchHistory.clear();
            }
        }
        
        //creating a user object for last user because won't be created with the above loop
        if (checkpoint > 0)
        {
            user = new User(name, email, watchHistory);
            users.push_back(user);
            emailToUser.insert(email, user);
            user = nullptr;
            watchHistory.clear();
        }
        
    infile.close();
    }
    
    return true; 
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator it = emailToUser.find(email);
    
    if (it.is_valid()) {
        return it.get_value();
    }
    
    return nullptr;
}

