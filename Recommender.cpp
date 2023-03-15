#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = user_database;
    m_movie_database = movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if (movie_count < 0) //movie count cannot be less than 0 so return an empty vector
        return  vector<MovieAndRank>();
    
    User* user = m_user_database.get_user_from_email(user_email); //using the email provided
    if (user == nullptr) //the email provided is not valid
        return vector<MovieAndRank>();
    
    vector<string> watch_history = user->get_watch_history(); //using the user pointer to get the users watch history
    vector<Movie*> candidateMovies; //a vector that will hold all of the potential candidate movies that we can recommend for the user
    map<string, int> movieToScores; //using the map data structure to keep track of a movie and its compatibility score
                                    //this will be helpful in the case that a director, actor, or genre is associated with the same movie
    
    for (int i=0; i <watch_history.size(); i++) //looping through the watch history to get the directors, actors, and genres associated with the user
    {
        
        Movie* m = m_movie_database.get_movie_from_id(watch_history[i]); //getting the movie pointer associated to the movie in the watch history
        vector<string> directors = m->get_directors(); //getting all the directors associated with that movie and storing them in to a vector
        vector<string> actors = m->get_actors(); //getting all the actors associated with that movie
        vector<string> genre = m->get_genres(); //getting all the genres associated with that movie
        
        for (int i=0; i < directors.size(); i++) {
            vector<Movie*> directorToMovies = m_movie_database.get_movies_with_director(directors[i]);//getting all of the movies associated with a director
            
            for (int i=0; i < directorToMovies.size(); i++)
            {
                movieToScores[directorToMovies[i]->get_id()] +=20;
                candidateMovies.push_back(directorToMovies[i]); //pushing back on to candidateMovies vector
            }
            
        }
        
        for (int i=0; i < actors.size(); i++) {
            vector<Movie*> actorToMovies = m_movie_database.get_movies_with_actor(actors[i]); //getting all of the movies associated with an actor
            
            for (int i=0; i < actorToMovies.size(); i++)
            {
                movieToScores[actorToMovies[i]->get_id()] +=30;
                candidateMovies.push_back(actorToMovies[i]); //pushing back on to candidateMovies vector
            }
            
        }
        
        for (int i=0; i < genre.size(); i++) {
            vector<Movie*> genreToMovies = m_movie_database.get_movies_with_genre(genre[i]); //getting all of the movies associated with a genre
            
            for (int i=0; i < genreToMovies.size(); i++)
            {
                movieToScores[genreToMovies[i]->get_id()] +=1;
                candidateMovies.push_back(genreToMovies[i]); //pushing back on to candidateMovies vector
            }

        }
        
    }
    

    //now, we will remove the movies the user has already watched from our movieToScores map so it doesn't get recommended
    for (int i=0; i < watch_history.size(); i++)
    {
        movieToScores.erase(watch_history[i]);
    }
    
    
    //now, we will sort the movies based on the given criteria to provide a correct recommendation
    vector<MovieAndRank> sortedMovies;
    
    for (map<string, int>::iterator it = movieToScores.begin(); it != movieToScores.end(); it++) //first, we will make a vector of MovieAndRank objects using the map we created
    {
        MovieAndRank m(it->first, it->second); //it->first refers to the movieID associated with the map and it->second refers to the compatibilityscore
        sortedMovies.push_back(m); //add this object to the vector
    }
    
    
    //using the std::sort function, we can sort this vector of MovieAndRank objects
    //I have overloaded the compare operator, which can be found defined in the private
    
    sort(sortedMovies.begin(), sortedMovies.end());
    
    
    //need to resize the vector to fit the number by movie_count
    
    return vector<MovieAndRank>();
}

