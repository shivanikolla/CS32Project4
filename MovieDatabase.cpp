#include "MovieDatabase.h"
#include "Movie.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

MovieDatabase::MovieDatabase()
{
   
}

bool MovieDatabase::load(const string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int checkPoint = 0;
    
    if (infile)
    {
        std::string movieID;
        std::string movieName;
        std::string releaseYear;
        std::vector<std::string> directors;
        std::vector<std::string> genre;
        std::vector<std::string> actors;
        std::string rating;
        
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
                    
                    while (!line.empty()) {
                        
                        getline(iss, singleDirector, ',');
                        if (directors.empty()) {
                            directors.push_back(singleDirector);
                        }
                    
                        else {
                            vector<std::string>::iterator it = std::find(directors.begin(), directors.end(), singleDirector); //runs O(N)
                            if (it == directors.end()) {
                                directors.push_back(singleDirector);
                            }
                        
                        }
                        
                    }
                    checkPoint++;
                }
                else if (checkPoint == 4) { //if it's the fifth checkpoint, it's the actor
                    std::istringstream iss(line);
                    std::string singleActor;
                    
                    while (!line.empty()) {
                        getline(iss, singleActor, ',');
                        
                        if (actors.empty()) {
                            actors.push_back(singleActor);
                        }
                        else
                        {
                            vector<std::string>::iterator it = std::find(actors.begin(), actors.end(), singleActor); //runs O(N)
                            if (it == actors.end()) {
                                actors.push_back(singleActor);
                            }
                            
                        }
                    }
                    
                    checkPoint++;
                }
                else if (checkPoint == 5) { //if it's the 6th checkpoint, it's the genre
                    
                    std::istringstream iss(line);
                    std::string singleGenre;
                    
                    while (!line.empty()) {
                        getline(iss, singleGenre, ',');
                        
                        if (genre.empty()) {
                            genre.push_back(singleGenre);
                        }
                        else
                        {
                            vector<std::string>::iterator it = std::find(genre.begin(), genre.end(), singleGenre);
                            
                            if (it == genre.end()) {
                                genre.push_back(singleGenre);
                            }
                            
                        }
                        
                        genre.push_back(singleGenre);
                    }
                    
                    checkPoint++;
                }
                else if (checkPoint == 6){ //if it's the last checkpoint, it's the rating
                    
                    rating = line;
                    checkPoint++;
                }
                else
                {
                    IDtoMovie.insert(movieID, movieName);
                    
                    
                }
                
            }
            else
            {
                checkPoint = 0;
            }
        }
 
    }
 
    return false;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    
    
    return nullptr;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

