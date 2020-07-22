//
// Created by Tony T on 2/16/20.
// Depth-First Search
// Takes in a graph through edge nodes and creates adjacency lists from each node in order to complete a Depth first search
// includes build graph function from a input file, destructor and helper methods to insert, dfs and clear

#include "graphl.h"
#include <stack>


GraphL::GraphL(){ // Constructor
}

GraphL::~GraphL(){ // Destructor
    for ( int i = 1; i <= size; i ++ ){
        clear( dataArray[i].edgeHead );
        size = 0;
        dataArray[i].visited = false;
    }
    dataArray = NULL;
    delete dataArray;
}

void GraphL::clear( EdgeNode* clear){ // recursive helper method to delete adjacency list
    EdgeNode* cur = clear;
    while( cur != NULL){
        cur = cur->nextEdge;
    }
    cur = NULL;
    delete cur;
}

void GraphL::buildGraph( ifstream &infile ){ // Builds graph with input file
    string in;
    infile >> in;
    try {                                   // try catch for stoi method
        size = stoi(in);
    } catch( const std::exception& ){
        size = 0;
    }
    getline(infile,in);             // gets to the end of the current line
    if( size == 0 ){                       // end if there are no Locations
        return;
    }
    dataArray = new GraphNode[ size + 1 ];
    for( int i = 1; i <= size; i++ ){       // create DataNode array with Location names
        getline( infile,in );
        NodeData *ptr = new NodeData( in );
        dataArray[ i ].data = ptr;
        dataArray[ i ].visited = false;
    }
    int from, to;
    while( infile >> from >> to ){        // read file for edges
        if( from == 0 && to == 0 ){      // input to end edges
            break;
        }
        insertEdge( from, to );         // helper method to insert new node in correct order
    }
}

void GraphL::displayGraph(){
    int width = 20;                     // set width for accurate spacing
    cout << "Graph:" << endl;
    for( int from = 1; from <= size; from++ ){
          cout << "Node " << from << setw( width ) << *dataArray[from].data << endl; // display Start node
          cout << endl;
          EdgeNode* cur = dataArray[ from ].edgeHead;
          while( cur != NULL ){
              cout << setw( width ) << "Edge: " << from << " " << cur->adjGraphNode << endl;  // display adjacency lists
              cur = cur->nextEdge;
          }
          cout << endl;
    }
}

void GraphL::insertEdge( int from, int to ){
    EdgeNode* temp = new EdgeNode;              // create a new EdgeNode
    temp->adjGraphNode = to;
    EdgeNode *cur;

    // Case 1: add to the front, when empty or less than the first node
    if ( dataArray[ from ].edgeHead == NULL || dataArray[ from ].edgeHead->adjGraphNode > to) {
        temp->nextEdge = dataArray[ from ].edgeHead;
        dataArray[ from ].edgeHead = temp;
        return;
    }
    // Case 2: add to the middle/end
    else {
        cur = dataArray[ from ].edgeHead;
        while( cur->nextEdge != NULL && cur->nextEdge->adjGraphNode < to ){
            if( cur->adjGraphNode == to ){
                return;
            }
            cur = cur->nextEdge;
        }
        temp->nextEdge = cur->nextEdge;
        cur->nextEdge = temp;
    }
}

void GraphL::depthFirstSearch(){
    for( int i = 1; i <= size; i++ ){ // call for all Nodes to ensure all nodes are called
        if( !dataArray[ i ].visited ){ // if not vistited yet call helper
            dfsHelper( i );
        }
    }
    cout << endl;
}

void GraphL::dfsHelper( int v ){
    dataArray[v].visited = true;            // set node t visited
    EdgeNode *cur = dataArray[v].edgeHead;
    cout << v << " ";
    while( cur != NULL ){
        if( !dataArray[ cur->adjGraphNode ].visited ){ // iterate through adjacency list, recall helper for nodes not visited yet
            dfsHelper( cur->adjGraphNode );
        }
        cur = cur->nextEdge;
    }
}




