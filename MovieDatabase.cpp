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
    
    for (int i=0; i< movies.size(); i++) {
        delete movies[i];
    }
    movies.clear();
}

bool MovieDatabase::load(const string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int checkPoint = 0;
    Movie* movie = nullptr;
    std::string movieID;
    std::string movieName;
    std::string releaseYear;
    std::vector<std::string> directors;
    std::vector<std::string> genre;
    std::vector<std::string> actors;
    std::string rating;
    float newRating = 0;
    
    if (!infile)
        return false;
    
    if (infile)
    {
    
        while(getline(infile, line))
        {
//            std::cerr<<line<<std::endl;
            if (!line.empty())
            {
                if (checkPoint == 0) {//if it's the first checkpoint, it's the movieID
                    movieID = toLower(line);
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
                        singleDirector = toLower(singleDirector);
                            directors.push_back(singleDirector);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleDirector);
                        singleDirector = toLower(singleDirector);
                        directors.push_back(singleDirector);
                    }

                    checkPoint++;
                }
                else if (checkPoint == 4) { //if it's the fifth checkpoint, it's the actor
                    
                    std::istringstream iss(line);
                    std::string singleActor;
                    
                    while (getline(iss, singleActor, ',')) {
                        singleActor = toLower(singleActor);
                            actors.push_back(singleActor);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleActor);
                       singleActor = toLower(singleActor);
                        actors.push_back(singleActor);
                     
                    }
                    
                    checkPoint++;
                }
                else if (checkPoint == 5) { //if it's the 6th checkpoint, it's the genre
                    
                    std::istringstream iss(line);
                    std::string singleGenre;
                    
                    while (getline(iss, singleGenre, ',')) {
                        singleGenre = toLower(singleGenre);
                            genre.push_back(singleGenre);
                    }
                    
                    if (!iss.eof()) {
                        getline(iss, singleGenre);
                       singleGenre = toLower(singleGenre);
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
                
                for (int i=0; i<directors.size(); i++) {
                    DirectorToMovies.insert(directors[i], movie);
                }
                
                for (int i=0; i<actors.size(); i++) {
                    ActorToMovies.insert(actors[i], movie);

                }

                for (int i=0; i <genre.size(); i++) {
                    GenreToMovies.insert(genre[i], movie);
                }
                checkPoint = 0;
                movie = nullptr;
                actors.clear();
                directors.clear();
                genre.clear();
            }
        } //closes while loop
        
        //accounts for the last movie in the database because won't be created with the logic of the loop above
        if (checkPoint > 0) //O(1)
        {
            movie = new Movie(movieID, movieName, releaseYear, directors, actors, genre, newRating);
            movies.push_back(movie);
            IDtoMovie.insert(movieID, movie);

            for (int i=0; i<directors.size(); i++) {
                DirectorToMovies.insert(directors[i], movie);
            }

            for (int i=0; i<actors.size(); i++) {
                ActorToMovies.insert(actors[i], movie);

            }

            for (int i=0; i < genre.size(); i++) {
                GenreToMovies.insert(genre[i], movie);
            }
            checkPoint = 0;
            movie = nullptr;
            actors.clear();
            directors.clear();
            genre.clear();

        }
        
        infile.close();
    }
 
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string item = id;
    item = toLower(id);
    
    TreeMultimap<std::string, Movie*>::Iterator it = IDtoMovie.find(item); //O(logN)
    
    if (it.is_valid()) { //O(1)
        return it.get_value(); //O(1)
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const //O(logD + M)
{
    string item = director;
    item = toLower(director);
    
    TreeMultimap<std::string, Movie*>::Iterator it = DirectorToMovies.find(item); //O(logD)
    std::vector<Movie*> moviesOfdirectors;
    
    if (!it.is_valid()) {
        return moviesOfdirectors;
    }
    
    while (it.is_valid()) {  //O(1)
     
        moviesOfdirectors.push_back(it.get_value()); //O(M) overall
        it.advance(); //O(1)
    }
    
    return moviesOfdirectors;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const //O(logD + M)
{
    string item = actor;
    item = toLower(actor);
    
    TreeMultimap<std::string,Movie*>::Iterator it = ActorToMovies.find(item);
    std::vector<Movie*> moviesOfactors;
    
    if (!it.is_valid()) {
        return moviesOfactors;
    }
    while (it.is_valid()) {
        moviesOfactors.push_back(it.get_value());
        it.advance();
    }
    
    return moviesOfactors;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const //O(logD + M)
{
    string item = genre;
    item = toLower(genre);
    
    TreeMultimap<std::string,Movie*>::Iterator it = GenreToMovies.find(item);
    std::vector<Movie*> moviesOfgenre;
    
    if (!it.is_valid()) {
        return moviesOfgenre;
    }
    
    while (it.is_valid()) {
        moviesOfgenre.push_back(it.get_value());
        it.advance();
    }
    return moviesOfgenre;
}
