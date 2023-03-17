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
    
    struct temporaryMovieAndRank
    {
        temporaryMovieAndRank(const std::string& id, int score, float rating, const std::string& name):movie_id(id), compatibility_score(score), movie_rating(rating), movie_name(name)
        {}

        std::string movie_id;
        int compatibility_score;
        float movie_rating;
        std::string movie_name;
    };
    
    const UserDatabase* m_user_database; //making pointers to the databases so we don't have to overload the assignment operator
    const MovieDatabase* m_movie_database;
    
    static bool compareScore(const temporaryMovieAndRank& a, const temporaryMovieAndRank& b) //CANNOT access any non static member variables
    {
        if (a.compatibility_score != b.compatibility_score)//if the scores of a and b are not equal to each other,
        {
            return a.compatibility_score > b.compatibility_score;     //return true if a is bigger than b
        }
        else if (a.movie_rating != b.movie_rating)
        {
            return a.movie_rating > b.movie_rating;
        }
        else
        {
            return a.movie_name < b.movie_name; //string comparison is different, if the first name is less than second name that means they are in the correct order
        }
         
    }
    
    

};

#endif // RECOMMENDER_INCLUDED

