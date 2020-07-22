//
// Created by Tony T on 2/16/20.
// Depth-First Search
// Takes in a graph through edge nodes and creates adjacency lists from each node in order to complete a Depth first search
// includes build graph function from a input file, destructor and helper methods to insert, dfs and clear

#ifndef DIJKSTRAS_DEPTHFIRST_GRAPHL_H
#define DIJKSTRAS_DEPTHFIRST_GRAPHL_H

#include "nodedata.h"
#include <list>

class GraphL {
public:
    GraphL(); // Constructor
    ~GraphL(); // destructor
    void buildGraph(ifstream &infile); // builds up graph node information and adjacency list of edges between each node reading from a data file.
    void displayGraph(); // Displays each node information and edge in the graph
    void depthFirstSearch(); //Makes a depth-first search and displays each node in depth-first order


private:
    struct EdgeNode;        // forward reference for the compiler
    struct GraphNode {      // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };

    struct EdgeNode {
        int adjGraphNode;   // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };
    const static int MAXNODES = INT_MAX;
    int size;

    GraphNode* dataArray;   // array of GraphNodes
    void dfsHelper( int v );// recursive helper method
    void insertEdge( int from, int to); // insert method for edge in correct order
    void clear( EdgeNode* clear);       // helper method for destructor to clear adjacency lists
};



#endif //DIJKSTRAS_DEPTHFIRST_GRAPHL_H
