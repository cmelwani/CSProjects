/*
 * Graph.cpp
 * COMP15
 * Spring 2020
 Cheryl Melwani
 April 8th, 2020
 * Its function is to handle all of the implementation of the Graph class that
 include reading in values from a v.dat and a.dat files, computing different
 queries such as list and dist and path. Cities are vertices and the graph
 is represented as a vector.
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Graph.h"
#include "Location.h"

using namespace std;

Graph::Graph() {

}

Graph::~Graph() {

}

/* Purpose: readVertices reads all of the cities from the .vdat file and
their locations. It populates all of this information into the city struct
that I created that represents all the vertices in the directed graph.
The function also populates all of the structs into the graph that is
represented using a vector called graph. The function takes in the
longitude and latitude values and changes that to a location of type Location
and stores that location into the city struct.
Return: void
Parameter: filename of the text file */
void Graph::readVertices(string filename) {
    ifstream input;
    string city;
    double long_min, long_degree, lat_min, lat_degree;
    input.open(filename);
    if (input.fail()) {
        cerr << "Unable to open " << filename;
        exit(EXIT_FAILURE);
    }
    input >> city >> lat_degree >> lat_min >> long_degree >> long_min;

    while (!input.eof()) {
        City new_city;
        new_city.visited = false;
        new_city.name = city;
        double longitude = setLongitude(long_degree, long_min);
        double latitude = setLatitude(lat_degree, lat_min);
        new_city.location.set_location(latitude, longitude);
        graph.push_back(new_city);
        input >> city >> lat_degree >> lat_min >> long_degree >> long_min;
    }

}

/* Purpose: readEdges() reads all of the city and their adjacent cities from the
.adat file and populates the adjacacent city vector found in each city struct.
Return: void
Parameter: the filename of the .adat file */
void Graph::readEdges(string filename) {
    ifstream input;
    string city, adj_city;
    input.open(filename);
    if (input.fail()) {
        cerr << "Unable to open " << filename;
        exit(EXIT_FAILURE);
    }
    while(input >> city >> adj_city) {
        for(int i = 0; i < (int)graph.size(); i++) {
            if(graph.at(i).name == city) {
                for(int j = 0; j < (int)graph.size(); j++) {
                    if(graph.at(j).name == adj_city) {
                        graph.at(i).adj_cities.push_back(&graph.at(j));
                    }
                }
            }
        }
    }
}

/* Purpose: helper function that takes the longitude minutes and degrees and
converts into a degree value that Location.cpp can read in
Return: double that represents the longitude degree
Parameter: the longitude degree and minutes from the text file */
double Graph::setLongitude(double long_degree, double long_min) {
    if (long_degree > 0) {
        long_degree = long_degree + (long_min/60);
    }
    if (long_degree < 0) {
        long_degree = long_degree - (long_min/60);
    }
    return long_degree;
}

/* Purpose: helper function that takes the latitude minutes and degrees and
converts into a degree value that Location.cpp can read in
Return: double that represents the latitude degree
Parameter: the latitude degree and minutes from the text file */
double Graph::setLatitude(double lat_degree, double lat_min) {
    if (lat_degree > 0) {
        lat_degree = lat_degree + (lat_min/60);
    }
    if (lat_degree < 0) {
        lat_degree = lat_degree - (lat_min/60);
    }
    return lat_degree;
}

/* Purpose: list() handles the list query and prints out all the names of the
cities into terminal and described in the spec.
Return: void
Parameter: none */
void Graph::list() {
    for (int i = 0; i < (int)graph.size(); i++) {
        cout << graph[i].name << endl;
    }
}

/* Purpose: dist() handles the dist query and finds the geographical distance
between two cities that the user inputs. This geographical distance is then
printed out onto terminal. The function uses the Location.cpp file to compute
the distance
Return: void
Parameter: the two cities that the user inputs */
double Graph::dist(string city1, string city2) {
    Location city1_loc;
    Location city2_loc;
    bool is_there1 = false;
    bool is_there2 = false;
    double distance = 0;
    for (int i = 0; i < (int)graph.size(); i++) {
        if (graph[i].name == city1) {
            city1_loc = graph[i].location;
            is_there1 = true;
        }
        else if (graph[i].name == city2) {
            city2_loc = graph[i].location;
            is_there2 = true;
        }
    }
    if (is_there1 == false || is_there2 == false) {
        distance = -1.00;
    }
    else if (is_there1 == true && is_there2 == true) {
        distance = city1_loc.distance_to(city2_loc);
    }
    return distance;

}

/* Purpose: path() handles the path query. It is the wrapper function that calls
the recursive path function that actually handles finding all paths. This
wrapper function is the public function visible to the editor. It handles
checking if the cities are in the .vdat file, and what happens if there is no
path. It pretty much takes care of the error checking.
Return: void
Parameter: the two cities that the user wants to find a path between and the
max number of paths the user inputs */
void Graph::path(string city1, string city2, int max_path) {
    bool is_there1 = false;
    bool is_there2 = false;
    City *city_to, *city_from;
    for(int i = 0; i < (int)graph.size(); i++) {
        if(graph[i].name == city1) {
            city_from = &graph.at(i);
            is_there1 = true;
        }
        if(graph[i].name == city2) {
            city_to = &graph.at(i);
            is_there2 = true;
        }
    }
    if (is_there1 == true && is_there2 == true) {
        int path_index = 0;
        vector<City> path;
        City *curr_city = city_from;
        pathHelper(curr_city, city_to, max_path, path, path_index);
        if(path_index == 0) {
            cout << "ERROR: no-path-possible" << endl;
        } else {
            cout << "-EOT-" << endl;
        }
    }
    else if(is_there1 == false || is_there2 == false) {
        cout << "ERROR: unknown city" << endl;
    }
}

/* Purpose: pathHelper() is the private, recursive function that actually
finds all the paths between the two cities inserted by the user. It uses
max path as the boundary for the number of paths it should find.
Return: void
Parameter: the two cities that the user wants to find a path between, the
max number of paths the user inputs, a vector of type city holds all the cities
in the current path, and the path index which represents how any paths have been
found.  */
void Graph::pathHelper(City *curr_city, City *city_to, int max_path,
                        vector<City> path, int &path_index) {
    curr_city->visited = true;
    path.push_back(*curr_city);

    if(path_index == max_path) {
        return;
    }
    else if (city_to == curr_city) {
        path_index++;
        if (path_index <= max_path) {
            print_path(path, path_index);
            path.clear();
        }
    }
    else {
        for (int i = 0; i < (int)curr_city->adj_cities.size(); i++) {
            if (curr_city->adj_cities.at(i)->visited == false) {
                pathHelper(curr_city->adj_cities.at(i), city_to, max_path,
                path, path_index);
            }
        }
        path.pop_back();
    }
    curr_city->visited = false;
}

/* Purpose: print_path() handles printing the actual path onto terminal. It
is called by the recursive path function above path_helper();
Return: void
Parameter: vector of cities inside the current path, and the current path
index */
void Graph::print_path(vector<City> path, int path_index) {
    cout << "PATH " << path_index << " :: 0 " << path.at(0).name << " ";
    path.at(0).location.print();
    cout << " ";
    for (int j = 1; j < (int)path.size(); j++) {
        int distance = dist(path.at(j-1).name, path.at(j).name);
        cout << distance << " ";
        cout << path.at(j).name << " ";
        path.at(j).location.print();
        cout << " ";
    }
    cout << endl;
}
