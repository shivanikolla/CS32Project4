#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"

#include "User.h"
#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = user_database;
    m_movie_database = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    int score = 0;
    User* user = m_user_database.get_user_from_email(user_email);
    vector<string> watch_history = user->get_watch_history();
    
    for (int i=0; i < watch_history.size(); i++)
    {
        
        
        
        
    }
    
    return vector<MovieAndRank>();
}

