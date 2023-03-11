#include "UserDatabase.h"
#include "User.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

UserDatabase::UserDatabase() { }

bool UserDatabase::load(const string& filename)
{
    std::string line;
    std::ifstream infile(filename);
    int check = 0;
    
    if (infile)
    {
        std::string email;
        std::string name;
        User* user = nullptr;
        while(getline(infile, line))
        {
            if (!line.empty())
            {
                if (check == 0) {
                    name = line;
                    check++;
                }
            }
            
        }
        
        
    }
    
    return false;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    
    
    
    
    return nullptr;  // Replace this line with correct code.
}

