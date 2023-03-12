#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include <string>

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User*> emailToUser;
    std::vector<std::string> watchHistory;
    std::vector<User*> users;
    
};

#endif // USERDATABASE_INCLUDED

