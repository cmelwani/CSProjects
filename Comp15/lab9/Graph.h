/*
 * Filename: Graph.h
 * Contains: Interface of the template Graph class 
 * Part of: Lab assignment "Graph Traversal" for Comp 15
 *
 */

#include "Queue.h"
#include <iostream>
#include <ostream>

#ifndef GRAPH_H_
#define GRAPH_H_

// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullGraph : public exception
{
public:
    const char *what() const throw()
    {
        return "Graph is full";
    }
};

class EmptyGraph : public exception
{
public:
    const char *what() const throw()
    {
        return "Graph is empty";
    }
};

// wrapper functions
template<class Vertex>
int index_is(Vertex *vertices, Vertex v);

template<class Vertex>
class Graph
{
public:
    //Constructor functions
    Graph();
    Graph(int num_vertices);

    // Functions needed to modify the graph
    void initialize_graph(int num_vertices);
    void add_vertex(Vertex v);
    void add_edge(Vertex from, Vertex to, int weight);

    void print_matrix(ostream &output) const;  // prints edges of graph

    // Helpers functions for implementing BFS and DFS
    bool is_vertex(Vertex v) const;                      // true if exists
    void get_to_vertices(Vertex v,                       // enqueues neighbors
                         Queue<Vertex> &neighbors) const;//     of v
    void clear_marks();
    void mark_vertex(Vertex v);
    bool is_marked(Vertex v) const;
    void initialize_path();                              // clears path info
    void update_predecessor(Vertex pred, Vertex succ);   // stores predecessor
    void report_path(ostream &out, Vertex start, Vertex end) const;  // print

private:
    static const int NULL_EDGE = -1;
    static const int NULL_PRED = -1;

    int      num_vertices;       // number of vertices of the graph
    Vertex  *vertices;           // stores label of vertices, if any
    int    **edges;              // weighted 2-D array to store edges 

    int     *path;               // array used to store a path
    int      curr_vertex;        // variable to track current vertex in DFS
    bool    *marks;              // used to mark that a vertex has been visited 
};

#endif
