//
// Created by Tony T on 2/16/20.
// Dijkstra's algorithm
// reads and input file of locations with graph edges and finds to shortest path from each location to each end location
// though an adjacency matrix, used a build method to take in the file data and dijkstra's algorithm to find the shortest path
// include printing method for all path and weight

#ifndef DIJKSTRAS_DEPTHFIRST_GRAPHM_H
#define DIJKSTRAS_DEPTHFIRST_GRAPHM_H

#include "nodedata.h"

class GraphM {
public:
    GraphM();       //among others that need to be initialized, the data member T is initialized to sets all dist
                    // to infinity, sets all visited to false, and sets all path to 0.
    void buildGraph(ifstream& infile);      // builds up graph node information and adjacency matrix of edges
                                            // between each node reading from a data file.
    void insertEdge(int from, int to, int weight);  //insert an edge into graph between two given nodes
    void removeEdge(int from, int to);              //remove an edge between two given nodes
    void findShortestPath();        // find the shortest path between every node to every other node in the graph
                                    // TableType T is updated with shortest path information
    void displayAll();              // uses couts to demonstrate that the algorithm works properly. For the data
    void display(int from, int to); // only display requested data

private:
    const static int INFINITY = INT_MAX;
    const static int MAXNODES = 100;    //at most nodes per graph as stated in assignment

    struct TableType {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source known so far
        int path;              // previous node in path of min dist
    };

    NodeData data[MAXNODES];              // data for graph nodes
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

    int minDist( int a, int b );          // Helper function to find min value of 2 parameters
    void displayPath(int start, int path);// recursive method to print path
};

#endif //DIJKSTRAS_DEPTHFIRST_GRAPHM_H
