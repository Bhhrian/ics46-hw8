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

void DisjointSet::makeSet(Vertex x){
    subsets[x].parent = x;
}

Vertex DisjointSet::findSet(Vertex x){
    if (subsets[x].parent != x) {
        return findSet(subsets[x].parent);
    }
    return x;
}