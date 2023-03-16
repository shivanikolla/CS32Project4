#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = &user_database;
    m_movie_database = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if (movie_count < 0) //movie count cannot be less than 0 so return an empty vector
        return  vector<MovieAndRank>();
    
    User* user = m_user_database->get_user_from_email(user_email); //using the email provided
  
    if (user == nullptr) //the email provided is not valid
        return vector<MovieAndRank>(); //return empty vector

    vector<string> watch_history = user->get_watch_history(); //using the user pointer to get the users watch history
    unordered_map<string, int> movieToScores; //using the map data structure to keep track of a movie and its compatibility score
    
    unordered_map<string, int> directorToScoresCount;
    unordered_map<string, int> actorToScoresCount;
    unordered_map<string, int> genreToScoresCount;
    
    for (int i=0; i < watch_history.size(); i++) //looping through the watch history to get the directors, actors, and genres associated with the each movie
    {

        Movie* m = m_movie_database->get_movie_from_id(watch_history[i]); //getting the movie pointer associated to the movie in the watch history

            vector<string> directors = m->get_directors(); //getting all the directors associated with that movie and storing them in to a vector
            vector<string> actors = m->get_actors(); //getting all the actors associated with that movie
            vector<string> genre = m->get_genres(); //getting all the genres associated with that movie

        for (int j=0; j < directors.size(); j++) {
            vector<Movie*> directorToMovies = m_movie_database->get_movies_with_director(directors[j]);//getting all of the movies associated with a director

            for (int k=0; k < directorToMovies.size(); k++) { //looping through all of the movies that have that director in it
                
                movieToScores[directorToMovies[k]->get_id()] +=20;
                

            }
        }

        for (int j=0; j < actors.size(); j++) {
            vector<Movie*> actorToMovies = m_movie_database->get_movies_with_actor(actors[j]); //getting all of the movies associated with an actor

            for (int k=0; k < actorToMovies.size(); k++) { //looping through all of the movies that have that actor in it
                
                     movieToScores[actorToMovies[k]->get_id()] +=30;
            }
        }

        for (int j=0; j < genre.size(); j++) {
            vector<Movie*> genreToMovies = m_movie_database->get_movies_with_genre(genre[j]); //getting all of the movies associated with a genre

            for (int k=0; k < genreToMovies.size(); k++) { //looping through all of the movies that have that genre in it
            
                movieToScores[genreToMovies[k]->get_id()] +=1;

            }
        }

    }

//    //now, we will remove the movies the user has already watched from our movieToScores map so it doesn't get recommended because the user has already seen it
    for (int i=0; i < watch_history.size(); i++)
    {
        movieToScores.erase(watch_history[i]); //if movieToScores contains a movieID of watch history erase it from the map
    }
    
    //now, we will sort the movies based on the given criteria to provide a correct recommendation
    vector<temporaryMovieAndRank> moviesToSort;
    for (unordered_map<string, int>::iterator it = movieToScores.begin(); it != movieToScores.end(); it++) //first, we will make a vector of MovieAndRank objects using the map we created
    {
        Movie* temp = m_movie_database->get_movie_from_id(it->first);
        
        temporaryMovieAndRank object(it->first, it->second, temp->get_rating(), temp->get_title());
        moviesToSort.push_back(object);
    }
    
    //using the std::sort function, we can sort this vector of MovieAndRank objects
    //I have overloaded the compare operator, which can be found defined in the private
    sort(moviesToSort.begin(), moviesToSort.end(), compareScore);
    
    //resizing the vector to fit the movie_count parameter
    while (moviesToSort.size()> movie_count)
    {
        moviesToSort.pop_back();
    }
    
    //now after the comparisons have been made, making a vector of MovieAndRank objects
    vector<MovieAndRank> sortedMovies;
    for (vector<temporaryMovieAndRank>::iterator it = moviesToSort.begin(); it != moviesToSort.end(); it++)
    {
        MovieAndRank mAr((*it).movie_id, (*it).compatibility_score);
        sortedMovies.push_back(mAr);
    }
    
    return sortedMovies; //return the resulting vector
    
}

