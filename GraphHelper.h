#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <queue>
using namespace std;

struct Node {
    // NOTE: Do not edit node struct
    int id;
    vector<float> features;
    
    Node(int id, vector<float> features): id(id), features(features) {}
    Node(const Node &n2) { id = n2.id; features=n2.features;}
};


struct Edge {
    // NOTE: Do not edit Edge struct
    int IdA, IdB, weight;
    
    Edge(int IdA, int IdB, int weight): IdA(IdA), IdB(IdB), weight(weight) {}
};

class Triangle {
    // TODO make a Triangle class with appropriate fields and methods
public:

// TODO make appropriate constuctor
    Triangle(){id1=0;id2=0;id3=0;weight=0;}
    Triangle(int i,int j,int k,int w){
        id1 = i;
        id2 = j;
        id3 = k;
        weight = w;
        
    }
    
    int id1,id2,id3;
   
    int weight ;
    
    bool operator <(const Triangle& other){
      if(this->weight<other.weight) return true;
      return false;
    }

};
inline bool operator <(const Triangle& other, const Triangle& other2){
    if(other.weight<other2.weight) return true;
    return false;
};

#endif

    




    
