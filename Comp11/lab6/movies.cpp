#include <iostream>
#include <fstream>

using namespace std;

// Hard coded queries that the user can execute
const string PRINT_MOVIE = "p";
const string ADD_GROSS = "a";
const string FILMOGRAPHY = "f";
const string STAR_POWER = "s";
const string QUIT = "q";

struct Actor;

struct Movie {
  string title;
  int year;
  double gross;
  string director;
  Actor *actors[5];
};

struct Actor {
  string name;
  int num_movies;
  Movie *movies[100];
};

int main(){

string filename = "moviedata.txt";
ifstream infile(filename.c_str());
if(infile.fail()) {
  cerr << "Error: The file failed to open correctly." << endl;
  exit(EXIT_FAILURE);
}
  int total_movies;
  infile >> total_movies;

  Movie *movies = new Movies[total_movies];
  Actor *actors = new Actor[2250];

  int year;
  double gross;
  int num_movies;

  for(int i = 0; i < 2250; i++){
      getline(infile, actor[i].name);
  }

  for(int i = 0; i < total_movies; i++){
      getline(infile, movies[i].title);
      infile >> year;
      movies[i].year = year;
      iinfile >> gross;
      movies[i].gross = gross;
      getline(infile, movies[i].director);
      for(int j = 0; j < 5; j++) {
        getline(infile, actors[j].name);
      }

  }



    /* * * * * * * * * * * * YOUR CODE * * * * * * * * * * * * *
     * (read in moviedata.txt and store it in your data structure)
     * * * * * * * * * * * * YOUR CODE * * * * * * * * * * * * */


    // Perform the main loop of requesting and executing queries
    string query;
    cout << "Enter a query: ";
    while (cin >> query) {
        cin.ignore();

        if (query == PRINT_MOVIE) {
            string movie_name;
            cout << "Movie Name: ";
            getline(cin, movie_name);

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *             (execute the "print movie" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        } else if (query == ADD_GROSS) {
            string movie_name;
            int dollars;
            cout << "Movie Name: ";
            getline(cin, movie_name);
            cout << "Dollar amount to add: ";
            cin >> dollars;

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "add to gross" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
       } else if (query == FILMOGRAPHY) {
            string actor_name;
            cout << "Actor Name: ";
            getline(cin, actor_name);

            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "filography" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
       } else if (query == STAR_POWER) {
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
            *            (execute the "star power" query)
            * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
      }else if (query == QUIT) {
            return 0;
        } else {
            cout << query << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }

    return 0;
}
