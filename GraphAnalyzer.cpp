#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <iostream>
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
    vector<int> listid;
    vector<float> listscore;
    listid.resize(k);
    listscore.resize(k);
    int index = 0;
    int id = 0;
    for (int i = 0; i<G.hashtableedge[nodeID].size(); i++) {//access every edge contains nodeid
       //
        id=0;
        if (G.hashtableedge[nodeID][i] != nullptr){
        if (G.hashtableedge[nodeID][i]->IdA == nodeID) {// if ida in the edge is nodeid, then idb is the search target
            id = G.hashtableedge[nodeID][i]->IdB;
            cout<<G.hashtableedge[nodeID][i]->IdB<<"\n";
        }
        else if (G.hashtableedge[nodeID][i]->IdB == nodeID){// if idb in the edge is nodeid, then idb is the search target
            id = G.hashtableedge[nodeID][i]->IdA;
            cout<<G.hashtableedge[nodeID][i]->IdA<<"\n";
            
            }
         
            float score = 0;//initial score
            for (int j = 0; j<G.sizeskill; j++) { // compute the score of neighbor id
                score += w[j]*G.hashtable[id]->features[j];
            }
            if (index<k && score!=0) {// if the list have less than k items just add it
                listid[index]=i;
                listscore[index]= score;
                //then sort it
                sortlist(index+1, listid,listscore);
                index++;
            }
            else if(score!=0 &&score > listscore[k-1])// if list have k items, replace the smallest one
            {
                                            
                listid[k-1]=i;//G.hashtable[i]->id;
                listscore[k-1]= score;
                sortlist(k, listid,listscore); // sort list
                index++;
                
            }
        }
        
        
    }
    vector<int> result;
    
    int size = 0;
    if (k>index) { // take the min of k & neighbors
        size = index;
        cout<<"This node only have "<< index<<" neighbors"<<"\n";
    }
    else
        size = k;
    result.resize(size);
    for (int l = 0; l < size ; l++) { //move ordered id to vector result and return
        result[l]=listid[l];
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
void GraphAnalyzer::sortlist(int k, vector<int>&listid,vector<float> &listscore){ 
    for (int i = 0; i < k; i++) {
        for (int j = i; j < k; j++) {
            if (listscore[i]<listscore[j]) {
                int idtemp = listid[i];
                float scoretemp = listscore[i];
                listid[i] = listid[j];
                listscore[i] = listscore[j];
                listid[j] = idtemp;
                listscore[j] = scoretemp;
            }
        }
        
    }
};




