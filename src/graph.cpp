#include "graph.h"

void error(string msg){
    cerr << "Error: " << msg << endl;
}

//Disjoint class
DisjointSet::DisjointSet(int numVertices){
    subsets.resize(numVertices);
    for (Vertex i = 0; i < numVertices; ++i) {
        makeSet(i);
    }
}