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
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    //change from string to movie object
    TreeMultimap<std::string, Movie*> IDtoMovie;
    TreeMultimap<std::string, std::vector<Movie*>> DirectorToMovies;
    TreeMultimap<std::string, std::vector<Movie*>> ActorToMovies;
    TreeMultimap<std::string, std::vector<Movie*>> GenreToMovies;
    std::vector<Movie*> movies;
//
    
};

#endif // MOVIEDATABASE_INCLUDED

