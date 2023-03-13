#include "MovieDatabase.h"
#include "Movie.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

MovieDatabase::MovieDatabase() { }

MovieDatabase::~MovieDatabase() {
    movies.clear();
}

bool MovieDatabase::load(const string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int checkPoint = 0;
    
    if (infile)
    {
        Movie* movie = nullptr;
        std::string movieID;
        std::string movieName;
        std::string releaseYear;
        std::vector<std::string> directors;
        std::vector<std::string> genre;
        std::vector<std::string> actors;
        std::string rating;
        float newRating;
        
        while(getline(infile, line))
        {
            if (!line.empty())
            {
                if (checkPoint == 0) { //if it's the first checkpoint, it's the movieID
                    movieID = line;
                    checkPoint++;
                
                }
                else if (checkPoint == 1) { //if it's the second checkpoint, it's the movieName
                    movieName = line;
                    checkPoint++;
                  
                }
                else if (checkPoint == 2) { //if it's the third checkpoint, it's the releaseYear
                    releaseYear = line;
                    checkPoint++;
                  
                }
                else if (checkPoint == 3) { //if it's the fourth checkpoint, it's the director
                    
                    std::istringstream iss(line);
                    std::string singleDirector;
                    
                    while (getline(iss, singleDirector, ',')) {

                            directors.push_back(singleDirector);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleDirector);
                        directors.push_back(singleDirector);
                    }

                    checkPoint++;
                }
                else if (checkPoint == 4) { //if it's the fifth checkpoint, it's the actor
                    
                    std::istringstream iss(line);
                    std::string singleActor;
                    
                    while (getline(iss, singleActor, ',')) {
                            actors.push_back(singleActor);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleActor);
                        actors.push_back(singleActor);
                    }
                    
                    checkPoint++;
                }
                else if (checkPoint == 5) { //if it's the 6th checkpoint, it's the genre
                    
                    std::istringstream iss(line);
                    std::string singleGenre;
                    
                    while (getline(iss, singleGenre, ',')) {
                        
                            genre.push_back(singleGenre);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleGenre);
                        genre.push_back(singleGenre);
                    }
                    
                checkPoint++;
                }
                else if (checkPoint == 6){ //if it's the last checkpoint, it's the rating
                    
                    rating = line;
                    newRating = std::stof(rating);
                    checkPoint++;
                }
                
            } //closes if line empty statement
            else
            {
                movie = new Movie(movieID, movieName, releaseYear, directors, actors, genre, newRating);
                movies.push_back(movie);
                IDtoMovie.insert(movieID, movie);
                checkPoint = 0;
                movie = nullptr;
                actors.clear();
                directors.clear();
                genre.clear();
            }
        } //closes while loop
        
        infile.close();
    } //closes if (infile)
 
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = IDtoMovie.find(id);
    
    if (it.is_valid()) {
        return it.get_value();
    }
    return nullptr;
}

std::vector<Movie*> dummy;
vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return dummy;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return dummy;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return dummy;  // Replace this line with correct code.
}

