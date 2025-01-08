/*
 * main.cpp
 * COMP15
 * Spring 2020
 Cheryl Melwani
 April 8th, 2020
 * Creates an instance of the graph class. Main driver for calling respective
 functions depending on what queries the user inputs. Also, main driver for
 testing functions of the graph class for phase 1.
 */

#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

/* Purpose: main creates an instance of graph and calls respective
functions depending on what the user inputs.
Return: an integer
Parameters: int argc - the number of inputs in the command line arguements
after your executable. argv[] holds the names of those files.
 */
int main(int argc, char *argv[]) {
    Graph g;
    if(argc < 3){
        cerr << "Usage: findpath vertex_data edge_data " << endl;
        exit(EXIT_FAILURE);
    }
    g.readVertices(argv[1]);
    g.readEdges(argv[2]);
    string command;
    //SPLIT MAIN INTO TWO FUNCTIONS
    while(cin >> command) {
        if(command == "list") {
            g.list();
            cout << "-EOT-" << endl;
        }
        else if(command == "dist") {
            string city1, city2;
            cin >> city1 >> city2;
            double distance = g.dist(city1, city2);
            printf("%.2f", distance);
            cout << "\n";
            cout << "-EOT-" << endl;
        }
        else if(command == "quit") {
            return 0;
        }
        else if(command == "path") {
            string city1, city2;
            int max_path = 0;
            cin >> city1 >> city2 >> max_path;
            if (max_path < 0) {
                max_path = 1;
            }
            g.path(city1, city2, max_path);
        }
        else if(command != "quit" || command != "dist" || command != "list" ||
                command != "path") {
            cout << "-EOT-" << endl;
        }
    }
}
