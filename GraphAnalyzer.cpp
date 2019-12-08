#include "GraphAnalyzer.h"
#include <iostream>
using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
    // i think i misunderstood this, ignore for now
    /*
    //if node is in a triangle (is connected to another node that is connected to another node) is closed if third node also connects to new node
    if(!G.hashtableedge[n.id].empty()){ //left check
      for(int i = 0; i < G.hashtableedge[n.id].size(); i++){
        if(G.hashtableedge[n.id][i]!=nullptr && G.hashtable[G.hashtableedge[n.id][i]->IdB]!=nullptr){
          //at this stage, we know an edge points from node to another node. now check if other node has any edges that point from/to it. know other node exists
          int node2id = G.hashtableedge[n.id][i]->IdB;
          for(int j = 0; j < G.hashtableedge[node2id].size(); j++){//left/left check
            if(G.hashtableedge[node2id][j]!=nullptr && G.hashtable[G.hashtableedge[node2id][j]->IdB]!=nullptr){
              int node3id = G.hashtableedge[node2id][j]->IdB;
              //triangle of new node - other node - this node exists, check if closed
              if(G.hashtableedge[G.hashtable[G.hashtableedge[n.id][i]->IdB][j]].id][n.id]!=nullptr){//close check
                closed+=1;
              }
              else{
                openlist.
              }
            }
          }
        }
      }
    }
    for(int i = 0; i < G.hashtableedge.size(); i++){ //right check
      for(int j = 0; j < G.hashtableedge[i].size(); j++){
      
      }
    }
    */
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
    /*open =0.0;
    close=0.0;
    int index = 0;
    int size = G.nnode;
    vector<Triangle> trilist;
    trilist.resize(size*(size-1)*(size-1));
    for (int i=0 ; i<G.hashtable.size(); i++) {
        for (int j = 0; j < G.hashtableedge[i].size(); j++) {
             if (G.hashtableedge[i][j] != nullptr)
             {
                 int weight = G.hashtableedge[i][j]->weight;
                 for (int k = 0; k < G.hashtableedge[j].size(); k++) {
                     if (G.hashtableedge[j][k] != nullptr && k != i)
                     {
                         bool add = true;
                         weight += G.hashtableedge[j][k]->weight;
                         for (int l = 0; l < G.hashtableedge[k].size(); l++) {
                             
                             if (G.hashtableedge[k][l] != nullptr && l != j) {
                               if ((G.hashtableedge[k][l]->IdA == i ||G.hashtableedge[k][l]->IdB == i) && !triangleexist(i, j, k, trilist)) {
                                 close += 1.0;
                                 add = false;
                                 weight +=G.hashtableedge[k][l]->weight;
                                 Triangle *temp = new Triangle(i,j,k,weight);
                                 trilist[index]=*temp;
                                 index++;
                               }
                             }
                         }
                         if(add && !triangleexist(i, j, k,trilist)){
                             open += 1.0;
                             Triangle *temp = new Triangle(i,j,k,weight);
                             trilist[index]=*temp;
                             index++;
                             openlist.emplace(*temp);

                        }
                   }
               }
            }
        }
    }
    return float(open/(close));*/
    return 0;
};

string GraphAnalyzer::topKOpenTriangles(int k) {
    //TODO
  string list= "";
    if (openlist.empty()) {
        list += "there is no open triangle in the list";
    }
    else{
       
    for (int i =0; i<k; i++) {
        /*string temp1 = to_string(openlist.top().id1);
        cout<<temp1<<"temp1\n";
        int temp2= openlist.top().id2;
        cout<<temp2<<"twmp2\n";
        int temp3 = openlist.top().id3;
        cout<<temp3<<"temp3\n";*/
        list += to_string(i + 1);
        list += " open triangle is: ";
        list += to_string(openlist.top().id1);
        list += " ";
        list += to_string(openlist.top().id1);
        list += " ";
        list += to_string(openlist.top().id1);
        list += "\n";
        openlist.pop();
    }
        
    }
    return list;
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
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
            for (int j = 0; j<2; j++) { // compute the score of neighbor id
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
        cout<<"This node only has "<< index<<" neighbors"<<"\n";
    }
    else{
        size = k;
    }
    result.resize(size);
    for (int l = 0; l < size ; l++) { //move ordered id to vector result and return
        result[l]=listid[l];
    }
    return result;
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    int nonneighbor = -1;
    float max = 0.0;
    //for every single node in hashtable, compute its weight with w*features. if weight > max, check that there are no edges between that node and nodeID
    for(int i = 0; i < G.hashtable.size(); i++){
      if(G.hashtable[i]!=nullptr){
        float currentmax = 0.0;
        currentmax+=w[0]*G.hashtable[i]->features[0];
        currentmax+=w[1]*G.hashtable[i]->features[1];
        if(currentmax > max && G.hashtableedge[i][nodeID]==nullptr && G.hashtableedge[nodeID][i]==nullptr){//check all edges between nodeID and i to make sure none exist
          nonneighbor = i;
          max = currentmax;
        }
      }
    }
    return nonneighbor;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w) {
    vector<int> neighborsA = topKNeighbors(nodeAID, k, w);
    vector<int> neighborsB = topKNeighbors(nodeBID, k, w);
    float jindex = 0.0;
    vector<int> intersect;
    for(int i = 0; i < neighborsA.size(); i++){
      for(int j = 0; j < neighborsB.size(); j++){
        if(neighborsA[i]==neighborsB[j]) intersect.emplace_back(neighborsA[i]);
      }
    }
    jindex = intersect.size()/(neighborsA.size()+neighborsB.size()-intersect.size());
    return jindex;
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

bool GraphAnalyzer::triangleexist(int i, int  j, int k, vector<Triangle> trilist){ 
    
    for (int z = 0; z < trilist.size(); z++) {
        if (trilist[z].id1 == i && trilist[z].id2 ==j && trilist[z].id3 ==k) {
            return true;
        }
        else if (trilist[z].id1 == i && trilist[z].id3 ==j && trilist[z].id2 ==k){
            return true;
        }
        else if (trilist[z].id2 == i && trilist[z].id1 ==j && trilist[z].id3 ==k){
            return true;
        }
        else if (trilist[z].id2 == i && trilist[z].id3 ==j && trilist[z].id1 ==k){
            return true;
        }
        else if (trilist[z].id3 == i && trilist[z].id2 ==j && trilist[z].id1 ==k){
            return true;
        }
        else if (trilist[z].id3 == i && trilist[z].id1 ==j && trilist[z].id2 ==k){
            return true;
        }
    }
    return false;
};
