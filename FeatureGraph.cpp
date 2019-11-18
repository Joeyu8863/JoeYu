#include <string>
#include <vector>
#include "FeatureGraph.h"
#include "GraphHelper.h"


using namespace std;


FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
    //TODO
    nnode=N;
    sizenode=d;
    for (int i = 0; i < nnode; i++) {
        insert(nodes[i]);
    }
    for (int j = 0 ; j<sizenode; j++) {
        insert(edges[j]);
    }
};

void FeatureGraph::insert(Node node){
    //TODO
    Node *temp= new Node(node);
    int i = node.id;
    hashtable[i] = temp;
    return;
};
    
void FeatureGraph::insert(Edge edge){
    //TODO
    Edge *temp = new Edge(edge);
    int i = edge.IdA;
    int j = edge.IdB;
    hashtableedge[i][j] = temp;
    hashtableedge[j][i] = temp;
    return;
    
    
};



