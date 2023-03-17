#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>
#include <cctype>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> IDtoMovie;
    TreeMultimap<std::string, Movie*> DirectorToMovies;
    TreeMultimap<std::string, Movie*> ActorToMovies;
    TreeMultimap<std::string, Movie*> GenreToMovies;
    std::vector<Movie*> movies;
    
    std::string toLower(std::string s) const
    {
        std::string caseInsensitive = "";
//        
        for (int i=0; i < s.length(); i++)
        {
            if (isalpha(s.at(i)))
                caseInsensitive += tolower(s.at(i));
            else
                caseInsensitive += s.at(i);
        }
        return caseInsensitive;
    }
    
};

#endif // MOVIEDATABASE_INCLUDED
