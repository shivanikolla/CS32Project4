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
    
    for (int i=0; i<movies.size(); i++) {
        delete movies[i];
    }
    movies.clear();
    
//    for (int i=0; i <singleMovie.size(); i++) {
//        delete singleMovie[i];
//    }
}

bool MovieDatabase::load(const string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int checkPoint = 0;
    
    if (!infile)
        return false;
    
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
        float newRating = 0;
        
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
                singleMovie.push_back(movie);
                IDtoMovie.insert(movieID, movie);
                
                for (int i=0; i<directors.size(); i++) {
                    DirectorToMovies.insert(directors[i], singleMovie);
                }
                
                for (int i=0; i<actors.size(); i++) {
                    ActorToMovies.insert(actors[i], singleMovie);

                }

                for (int i=0; i <genre.size(); i++) {
                    GenreToMovies.insert(genre[i], singleMovie);
                }
                checkPoint = 0;
                movie = nullptr;
                actors.clear();
                directors.clear();
                genre.clear();
                singleMovie.clear();
            }
        } //closes while loop
        
        infile.close();
    } //closes if (infile)
 
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string, Movie*>::Iterator it = IDtoMovie.find(id); //O(logN)
    
    if (it.is_valid()) { //O(1)
        return it.get_value(); //O(1)
    }
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const //O(logD + M)
{
    TreeMultimap<std::string,std::vector<Movie*>>::Iterator it = DirectorToMovies.find(director); //O(logD)
    std::vector<Movie*> moviesOfdirectors;
    
    if (!it.is_valid()) {
        return moviesOfdirectors;
    }
    
    while (it.is_valid()) {  //O(1)
        int i=0; //O(1)
        moviesOfdirectors.push_back(it.get_value().at(i)); //O(M) overall
        it.advance(); //O(1)
    }
    
    return moviesOfdirectors;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<std::string,std::vector<Movie*>>::Iterator it = ActorToMovies.find(actor);
    std::vector<Movie*> moviesOfactors;
    
    if (!it.is_valid()) {
        return moviesOfactors;
    }
    while (it.is_valid()) {
        int i=0;
        moviesOfactors.push_back(it.get_value().at(i));
        it.advance();
    }
    
    return moviesOfactors;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<std::string,std::vector<Movie*>>::Iterator it = GenreToMovies.find(genre);
    std::vector<Movie*> moviesOfgenre;
    
    if (!it.is_valid()) {
        return moviesOfgenre;
    }
    
    while (it.is_valid()) {
        int i=0;
        moviesOfgenre.push_back(it.get_value().at(i));
        it.advance();
    }
    return moviesOfgenre;
}

