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
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y){
    Vertex rootX = findSet(x);
    Vertex rootY = findSet(y);
    if(rootX != rootY){
        subsets[rootY].parent = rootX;
    }
}

//Graph class
Graph Graph::sort_edges() const{
    Graph sorted_edge_lst = * this;
    sort(sorted_edge_lst.begin(), sorted_edge_lst.end());
    return sorted_edge_lst; 
}

VertexList Graph::edges_from(Vertex vertex) const{
    VertexList lst;
    for (const Edge& e : *this) {
        if (e.u == vertex) {
            lst.push_back(e.v);
        }
        else if (e.v == vertex) {
            lst.push_back(e.u);
        }
    }
    return lst;
}


void file_to_graph(string filename, Graph & G){
    ifstream inFile(filename);
    if(!inFile){
        error("file not open");
    }
    inFile >> G;
}

VertexList bfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> label(graph.numVertices, false);   //make a label vector list for checking
    queue<Vertex> q;

    label[startVertex] = true;
    q.push(startVertex);

    while(!q.empty()){
        Vertex v = q.front();
        q.pop();
        result.push_back(v);
        for (Vertex neighbor : graph.edges_from(v)){
            if (!label[neighbor]){
                label[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return result;
}

VertexList dfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> label(graph.numVertices, false);
    stack<Vertex> s;

    label[startVertex] = true;
    s.push(startVertex);

    while(!s.empty()){
        Vertex v = s.top();
        s.pop();
        result.push_back(v);
        for(Vertex neighbor: graph.edges_from(v)){
            if(!label[neighbor]){
                label[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    return result;
}

//MST: Minimum Spanning Tree
int sum_weights(EdgeList const& L){
    int sum = 0;
    for (const Edge& edge: L){
        sum += edge.weight;
    }
    return sum;
}

EdgeList Kruskals(const Graph& G){
    EdgeList MST;
    Graph sorted = G.sort_edges();
    DisjointSet ds(G.numVertices);
    for(const Edge& edge: sorted){
        if (ds.findSet(edge.u) != ds.findSet(edge.v)){
            MST.push_back(edge);
            ds.unionSets(edge.u, edge.v);
        }
    }
    return MST;
}