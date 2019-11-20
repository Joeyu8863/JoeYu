#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"

using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

int GraphAnalyzer::diameter() {
    //TODO
    return 2;
};


float GraphAnalyzer::openClosedTriangleRatio() {
    //TODO
    return .5;
};

string GraphAnalyzer::topKOpenTriangles(int k) {
    //TODO
    return "2,3,4";
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
    //TODO
    vector<vector<int>> list;
    int index = 0;
    int id = 0;
    for (int i = 0; i<G.hashtableedge[nodeID].size(); i++) {//access every edge contains nodeid
        if (G.hashtableedge[nodeID][i]->IdA == nodeID) {// if ida in the edge is nodeid, then idb is the search target
            //question would empty G.hashtableedge[nodeID][i] break this line?
            id = G.hashtableedge[nodeID][i]->IdB;
        }
        else if (G.hashtableedge[nodeID][i]->IdB == nodeID){// if idb in the edge is nodeid, then idb is the search target
            id = G.hashtableedge[nodeID][i]->IdA;
            
            }
    
            int score = 0;//initial score
            for (int j = 0; j<G.hashtable[id]->features.size(); j++) { // compute the score of neighbor id
                score += w[j]*G.hashtable[id]->features[j];
            }
            if (list.size()<k && score!=0) {// if the list have less than k items just add it
                list[index][0]= G.hashtable[i]->id;
                list[index][1]= score;
                //then sort it
                sortlist(index+1, list);
            }
            else// if list have k items, replace the smallest one
            {
                
                
                    if (score > list[k-1][1]) {
                        list[index][0]= G.hashtable[i]->id;
                        list[index][1]= score;
                    }
                sortlist(k, list); // sort list
                
            }
            
        }
    vector<int> result;
    int size = 0;
    if (k>index+1) { // take the min of k & neighbors
        size = index +1;
    }
    else
        size = k;
    for (int l = 0; l < size ; l++) { //move ordered id to vector result and return
        result[l]=list[l][1];
    }
        
    
    
    return result;
    //return vector<int> {3};
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    //TODO
    return 1;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBiID, int k, vector<float> w) {
    //TODO
    return 0;
};
void GraphAnalyzer::sortlist(int k, vector<vector<int>> list){
    for (int i = 0; i < k; i++) {
        for (int j = 1; j < k; j++) {
            if (list[i][1]<list[j][1]) {
                int idtemp = list[i][0];
                int scoretemp = list[i][1];
                list[i][0] = list[j][0];
                list[i][1] = list[j][1];
                list[j][0] = idtemp;
                list[j][1] = scoretemp;
            }
        }
        
    }
    return;
    
};





