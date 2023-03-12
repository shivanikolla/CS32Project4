#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include "treemm.h"
#include <string>
#include <vector>

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, std::string> IDtoMovie;
    TreeMultimap<std::string, std::vector<std::string>> DirectorToMovies;
    TreeMultimap<std::string, std::vector<std::string>> ActorToMovies;
    TreeMultimap<std::string, std::vector<std::string>> GenreToMovies;
    
    
};

#endif // MOVIEDATABASE_INCLUDED

