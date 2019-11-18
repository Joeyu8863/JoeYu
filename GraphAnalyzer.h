#ifndef ANALYZER_H
#define ANALYZER_H

#include "FeatureGraph.h"


using namespace std;



class GraphAnalyzer {


public:	
		
	FeatureGraph G;
	//TODO: Store a heap of triangeles using cpp prioirty_queue

    //constructor
	// 
	// G: FeatureGraph to build on
    GraphAnalyzer(FeatureGraph& G): G(G) {};


    // Insert given node and corresponding features into graph
    // You may assume the number of features is the same as all other nodes in the graph
    void insert(Node n);


    //Insert given edge into graph
    // You may assume that the edge contains nodes already inserted into the graph
    void insert(Edge e);

   	// Return the diameter of the network.
    int diameter();

    // Return the ratio of open triangles to closed triangles.
    float openClosedTriangleRatio();   

    // Return the top k open triangles ranked by the total weight on their edges.
    // 
    // K: number of triangles to return
    string topKOpenTriangles(int k);

    // Return the top k skilled individuals around a given node based on a given weighting
    //
    // nodeID: Id of seed node
    // k: number of nodes to return
    // w: weight vector
    vector<int> topKNeighbors(int nodeID, int k,  vector<float> w);

    // Return the most skilled individual that does not share an edge with the seed node
    // nodeId: Id of seed node
    // w: weight vector
    int topNonNeighbor(int nodeID, vector<float> w);
    
    // Return the Jacard Index of the top-k neighbors of two seed nodes
    //
    // nodeA: id of first node
    // nodeB id of second node
    // k: number of neighbors to evaluate for each node
    // w: weight vector
    float jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w);

};

#endif
