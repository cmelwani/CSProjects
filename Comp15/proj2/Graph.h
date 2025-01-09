/*
 * Graph.h
 * COMP15
 * Spring 2020
 Cheryl Melwani
 April 8th, 2020
 * This file is the interface of the Graph class. Public and private functions
 are declared in this file. The struct city is the data structure used to
 implement the vertices in the graph. The graph is represented by the vector
 called graph.
 */


#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include "Location.h"

using namespace std;

struct City {
    bool visited;
    string name;
    Location location;
    vector<City*> adj_cities;
};

class Graph {

public:
    Graph();
    ~Graph();
    double setLongitude(double long_degree, double long_min);
    double setLatitude(double lat_degree, double lat_min);
    void readVertices(string filename);
    void readEdges(string filename);
    void list();
    double dist(string city1, string city2);
    void path(string city1, string city2, int max_path);

private:
    vector<City> graph;
    void pathHelper(City *curr_city, City *city_to, int max_path,
                    vector<City> path, int &path_index);
    void print_path(vector<City> path, int path_index);


};

#endif
