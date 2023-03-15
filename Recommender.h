#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "MovieDatabase.h"
#include "UserDatabase.h"

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    UserDatabase m_user_database;
    MovieDatabase m_movie_database;
    
    bool compareScore(const MovieAndRank& a, const MovieAndRank& b)
    {
        
        if (a.compatibility_score != b.compatibility_score)
        {
            return a.compatibility_score > b.compatibility_score; //return true if a has higher compatibility score
        }
        //else if
            // return the movie with the higher rating
        //else
            //return based on the movies titles
        
        
        return true;
    }

};

#endif // RECOMMENDER_INCLUDED

