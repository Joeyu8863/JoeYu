#include <string>
#include <vector>
#include "FeatureGraph.h"
#include "GraphHelper.h"


using namespace std;


FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
    //TODO
    sizeskill = d;
    nnode = N;
    for (int i = 0; i < N; i++) {
        insert(nodes[i]);
    }
    cout<<"Nodes inserted\n";
    for (int j = 0 ; j < d; j++) {
        insert(edges[j]);
    }
    cout<<"Edges inserted\n";
};

void FeatureGraph::insert(Node node){
    //TODO
    Node* temp = new Node(node);
    int i = node.id;
    hashtable.resize(hashtable.size()+i+1);
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
    int size = i+j;
    hashtableedge.resize(hashtableedge.size()+size+1);
    hashtableedge[i].resize(hashtableedge[i].size()+size+1);
    hashtableedge[j].resize(hashtableedge[j].size()+size+1);
    hashtableedge[i][j] = temp;
    hashtableedge[j][i] = temp;
    //test cout
    cout<<"Inserted Edge to "<<i<<" "<<j<<"\n";
    return;
};



