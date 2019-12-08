#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
    newid = n.id;//update the newid
};

void GraphAnalyzer::insert(Edge e) {
    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
    int a = 0;
    int b = 0;
    bool newedge = true;
    if (newid == e.IdA) {//let b =  new node's id
        a = e.IdB;
        b = e.IdA;
    }
    else if(newid == e.IdB){
        a = e.IdA;
        b = e.IdB;
    }
    else newedge = false;
    if(newedge){// case under new node
    for (int i = 0; i <G.hashtableedge[a].size(); i++) {
        if (G.hashtableedge[a][i] !=nullptr) {
            if (G.hashtableedge[i][b] != nullptr) {
                close += 1.0;
            }
            else open += 1.0;
            
        }
    }
    }
    else{//case under adding edge to original graph
        for (int i = 0; i <G.hashtableedge[a].size(); i++) {
            if (G.hashtableedge[a][i] !=nullptr) {
                if (G.hashtableedge[i][b] != nullptr ) {
                    close += 1.0;
                }
                else {
                    open += 1.0;
                    int weight = e.weight + G.hashtableedge[a][i]->weight;
                    Triangle *temp = new Triangle(a,i,b,weight);
                    openlist.emplace(*temp);
                }
                
            }
            else if (G.hashtableedge[b][i] !=nullptr){
                if (G.hashtableedge[i][a] != nullptr ) {
                    close += 1.0;
                }
                else {
                    open += 1.0;
                    int weight = e.weight + G.hashtableedge[b][i]->weight;
                    Triangle *temp = new Triangle(a,i,b,weight);
                    openlist.emplace(*temp);
                }
            }
        }
    }
    modify = true;
    
};

int GraphAnalyzer::diameter() {
      vector<int> dis;
    vector<int> q;
    int result;
    dis.resize(G.hashtable.size()+1);
    bool check[G.hashtable.size()];
    for (int i = 0 ; i < G.hashtable.size(); i++) {
        if (G.hashtable[i]!=nullptr)
        {
            q.push_back(G.hashtable[i]->id);
            check[G.hashtable[i]->id] = false;
        }
    }
    for (int i = q[0]; i < q.size(); i++) {//set distance to infinity
        dis[q[i]] = INT8_MAX;
    }
    vector<int> visited;
    int j = 0;
    int index2 = 0;
    
    while (!q.empty()) {
        bool newneighbor = false;
        if (index2 == 0) {// only for first run
        dis[q[0]] = 0;
        visited.push_back(q[0]);
        j = q[0];
        q.erase(q.begin());
        index2++;
        }
        else{// add missing node
            bool findconnectednode = false;
            int target = 0;
            int u = q[0+target];
            do{
                u = q[0+target];
            for (int m = 0; m < visited.size(); m++) {
                cout<<u<<" "<<visited[m]<<" ?\n";
                if (G.hashtableedge[u][visited[m]] != nullptr) {
                    if (dis[visited[m]] + G.hashtableedge[u][visited[m]]->weight < dis[u]) {
                        dis[u] = dis[visited[m]] + G.hashtableedge[u][visited[m]]->weight;
                        findconnectednode = true;
                    }
                }
            }
                target ++;
            }while(!findconnectednode && target < q.size());// break when find the node or none node can add to the path
            if (target > q.size()) {
                break;
            }
            else{
                visited.push_back(u);
                cout<<"add "<<u;
                q.erase(q.begin()+target -1);
            }
        }
        if(!q.empty()){
            int secondleast = INT8_MAX;
            int originalnodeid = INT8_MAX;
    do {
            
    vector<int> neighbordis;
    vector<int> neighborid;
    newneighbor = false;
        int dispass = 0;
    for (int k = j+1; k< G.hashtableedge[j].size(); k++) {
        
        if (G.hashtableedge[j][k]!=nullptr &&  !check[k]){// if k still in unexplore list, then do
            cout<<k<<"\n";
            if (dis[k]>dis[j] + G.hashtableedge[j][k]->weight) {//push all neighbor has less distance in vector
                cout<<j<<" "<<k<<" "<<"\n";
                dispass = dis[j] + G.hashtableedge[j][k]->weight;
                neighborid.push_back(k);
                neighbordis.push_back(dispass);
                newneighbor = true;
            }
        }
    }
        if (newneighbor) {// if newneighbor is added
            
        
        int leastid = neighborid[0];
        int leastdis = neighbordis[0];
        for (int l = 1; l < neighborid.size(); l++) {
            if (leastdis > neighbordis[l]) {// find leastdis neighbor
                leastdis = neighbordis[l];
                leastid = neighborid[l];
            }
            
        }
            if (secondleast>=leastdis) {
            
            for (int l = 1; l < neighborid.size(); l++) {
                if (secondleast>neighbordis[l] && neighbordis[l]>=leastdis) {
                    secondleast = neighbordis[l];
                    cout<<"new secondleast"<<secondleast;
                }
            }
        visited.push_back(leastid);//make the leastid visited
            cout<<newneighbor<<"add :"<<leastid<<"\n";
            cout<<leastid<<" old dis: "<<dis[leastid]<<"\n";
            dis[leastid] = dispass;
            cout<<leastid<<" has new dis: "<<dis[leastid]<<"\n";
            int temp = 0;
            for (temp = 0; temp < q.size(); temp++) {
                if (q[temp] == leastid) {
                    break;
                }
            }
                originalnodeid=j;
        q.erase(q.begin()+temp);
        index2++;
        j = leastid;
            cout<<j<<" j \n";
        check[j] = true;
            }
            else{
                j = originalnodeid;
                cout<<" go to check original node "<<j <<"\n";
            }
                
        }
    }while (newneighbor);// if new neighbor added, explore new neighbor
    }
    }
    printf("Vertex Distance from Source\n");
    result = dis[0];
    for (int i = 0; i < visited.size(); ++i){
         printf("%d \t\t %d\n", visited[i], dis[visited[i]]);
        if (result < dis[visited[i]]) {
            result = dis[visited[i]];
        }
        
    }
       
    return result;
};


float GraphAnalyzer::openClosedTriangleRatio() {
    //TODO
    open =0.0;
    close=0.0;
    int index = 0;
    int size = G.nnode;
    vector<Triangle> trilist;
    trilist.resize(size*(size-1)*(size-1));
    if(modify){
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
                             }}
                         if(add && !triangleexist(i, j, k,trilist)){
                             open += 1.0;
                             Triangle *temp = new Triangle(i,j,k,weight);
                             trilist[index] = *temp;
                             index++;
                             openlist.emplace(*temp); 
                             

                             }
                 }
          
             }
        }
        
    }
    }
    }
    return float(open/(close));
}
;

string GraphAnalyzer::topKOpenTriangles(int k) {
    //TODO pirority queue
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
        }
        else if (G.hashtableedge[nodeID][i]->IdB == nodeID){// if idb in the edge is nodeid, then idb is the search target
            id = G.hashtableedge[nodeID][i]->IdA;
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
    int nonneighbor = -1;
    float max = 0.0;
    //for every single node in hashtable, compute its weight with w*features. if weight > max, check that there are no edges between that node and nodeID
    for(int i = 0; i < G.hashtable.size(); i++){
      if(G.hashtable[i]!=nullptr){
        float currentmax = 0.0;
        for(int j = 0; j < G.hashtable[i]->features.size() && j < w.size(); j++){
          currentmax+=w[j]*G.hashtable[i]->features[j];
        }
        if(currentmax > max && G.hashtableedge[i][nodeID]==nullptr && G.hashtableedge[nodeID][i]==nullptr){//check all edges between nodeID and i to make sure none exist
          nonneighbor = i;
          max = currentmax;
        }
      }
    }
    return nonneighbor;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w) {
    vector<int> neighborsA;
    vector<int> neighborsB;
    if(G.hashtable[nodeAID]!=nullptr){
      neighborsA = topKNeighbors(nodeAID, k, w);
    }
    if(G.hashtable[nodeAID]!=nullptr){
      neighborsB = topKNeighbors(nodeBID, k, w);
    }
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



