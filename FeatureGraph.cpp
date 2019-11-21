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
    Node* temp= new Node(node);
    int i = node.id;
    hashtable.resize(hashtable.size()+i);
    hashtable[i] = temp;
    //test cout
    cout<<"Inserted Node to "<<node.id<<"\n";
    return;
};
    
void FeatureGraph::insert(Edge edge){
    //TODO
    Edge* temp = new Edge(edge);
    int i = edge.IdA;
    int j = edge.IdB;
    int size = i;
    if(j > i) size = j;
    hashtableedge.resize(hashtableedge.size()+size);
    hashtableedge[i].resize(hashtableedge[i].size()+j);
    hashtableedge[j].resize(hashtableedge[j].size()+i);
    hashtableedge[i][j] = temp;
    hashtableedge[j][i] = temp;
    //test cout
    cout<<"Inserted to "<<i<<" "<<j<<"\n";
    return;
    
    
};



