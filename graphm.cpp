//
// Created by Tony T on 2/16/20.
// Dijkstra's algorithm
// reads and input file of locations with graph edges and finds to shortest path from each location to each end location
// though an adjacency matrix, used a build method to take in the file data and dijkstra's algorithm to find the shortest path
// include printing method for all path and weight

#include "graphm.h"

GraphM::GraphM(){          //initialized, the data member
    for(int from = 0; from < MAXNODES; from++){
        //data[from] = NULL;
        for(int to = 0; to < MAXNODES; to++){
            C[from][to] = INFINITY;
            T[from][to].dist = INFINITY;
            T[from][to].path = 0;
            T[from][to].visited = false;
        }
    }
    size = 0;
}

void GraphM::buildGraph( ifstream &infile ){
    string in;
    infile >> in;
    try {                               // try catch exception to make sure and int is inputted
        size = stoi( in );
    } catch ( const std::exception& ){
        size = 0;
    }
    getline( infile,in );       // move to next line in file
    if ( size == 0 ){
        return;
    }
    for( int i = 1; i <= size; i++ ){  // create DataNode array with Location names
        getline( infile,in );
        NodeData* ptr = new NodeData( in );
        data[ i ] = *ptr;
    }

    int from, to, weight;
    while( infile >> from >> to >> weight ){        // inserts weight to cost matrix
        if ( weight == 0 && from == 0 && to == 0 ){
            break;
        }
        C[ from ][ to ] = weight;
    }
}

void GraphM::insertEdge( int from, int to, int weight ){ // method for inserting edge
    C[ from ][ to ] = weight;
}

void GraphM::removeEdge( int from, int to ){            // method for removing edge
    C[ from ][ to ] = INFINITY;
}

void GraphM::findShortestPath(){                        // Dijkstra's formula
    int min = INFINITY, minVertece;      // holds min distance and min verteces // set the nodes with infinity distance

    for( int source = 1; source <= size; source++ ){    // changes the source node
        for( int i = 1; i <= size; i++ ){               // Mark all nodes unvisited for new source node
            T[ source ][ i ].visited = false;
        }
        T[ source ][ source ].dist = 0;                 // sets the start data for new source
        T[ source ][ source ].visited = true;
        T[ source ][ source ].path = source;
        minVertece = source;
        for( int rounds = 1; rounds < size; rounds++ ) {
            for ( int adjacent = 1; adjacent <= size; adjacent++ ){// update adjacent cost
                if ( C[ minVertece ][ adjacent ] != INFINITY && !T[ source ][ adjacent ].visited ){ // if not visited
                    T[ source ][ adjacent ].dist = minDist( T[ source ][adjacent ].dist,
                                                       ( T[ source ][ minVertece ].dist + C[ minVertece ][ adjacent ] ) );
                    T[ source ][ adjacent ].path = minVertece;
                }
            }
            min = INFINITY;
            for( int v = 1; v <= size; v++ ){
                if( T[ source ][ v ].visited == false && T[ source ][ v ].dist < min ){ // finds not visited, shortest distance at this point
                    min = T[source][v].dist;
                    minVertece = v;
                }
            }
            T[ source ][ minVertece ].visited = true; // mark visited
        }
    }
}

void GraphM::displayAll() {
    int width = 20;
    cout << "Description" << setw( width ) << "From Node" << setw( width ) << "To Node" << setw( width ); // for visual description
    cout << "Dijkstra's" << setw( width ) << "Path" << endl;
    for( int from = 1; from <= size; from++ ){      // display for each source
        cout << data[ from ] << endl;
        for( int to = 1; to <= size; to++ ){        // display for each end location
            cout << setw( width *1.2 ) << from;
            cout << setw( width *1.2 ) << to;
            if( T[ from ][ to ].dist == INFINITY ){
                cout << setw( width * 1.2 ) <<  "--" ;
            } else {
                cout << setw( width * 1.2 ) << T[ from ][ to ].dist;
            }
            cout << setw( width * 1.2 );
            if( T [ from ][ to ].dist != INFINITY ){
                cout << from << " ";
            }
            displayPath( from,to );
            cout << endl;
        }
    }
}

void GraphM::display( int from, int to ){       // displays the requested from and to node with it's path
    int width = 20;
    cout << "Description" << setw( width ) << "From Node" << setw( width ) << "To Node" << setw( width ); // for visual description
    cout << "Dijkstra's" << setw( width ) << "Path" << endl;
    cout << data[from] << endl;
    cout << setw( width *1.2 ) << from;
    cout << setw( width *1.2 ) << to;
    if( T [ from ][ to ].dist == INFINITY ){
        cout << setw( width * 1.2 ) <<  "--";
    } else {
        cout << setw( width * 1.2 ) << T[from][to].dist;
    }
    cout << setw( width * 1.2 );
    if( T [ from ][ to ].dist != INFINITY ){
        cout << from << " ";
    }
    displayPath( from,to );
    cout << endl;
}

int GraphM::minDist( int a, int b ){        // returns min value of the 2 parameters
    if( a < b ){
        return a;
    }
    else{
        return b;
    }
}

void GraphM::displayPath( int start, int path ){    // recursive call to display path from end location to the start
    if( start != path && path != 0 ){
        displayPath( start, T[ start ][ path ].path );
        if( T [ start ][ path ].dist != INFINITY){
            cout << path << " ";
        }
    }
}
