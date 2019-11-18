# PA2
UCSB 130A Fall 2019 PA2 starter code

Notes: ve
*Be sure to read the "Policy on Academic Integrity" in the course syllabus.

*If you are confused, ask on Piazza, during office hours, or during discussion sections.

*Remember no late assignments will be accepted. at all.

*Submit your answers on Gradescope (keep your eye out for further instructions in the next few days)

*Read the entire README before starting

*Start Early

## Overview
In this project, you will implement a number of Graph operations. 

You are allowed and highly encouraged to work in pairs on this project. You may partner with any one in the class and may use Piazza to find a partner. If you do not have a partner by Friday, November 16th, please email one of the TAs.

There will be a small deadline on November 23rd with 10% of your grade. The rest of the assignment will be due Decemember 7th at 11:59 pm.

This project will be graded using Gradescope's autograder. More instuctions on that will come in the next few days. 

## Tasks
You will write code which maintains infomration about a weighted, undirected, graph where each node has an integer id and a skill 
.

You must implement the following methods:

**M1**: Return the diameter of the graph. The distance between two nodes is given by the sum of the edge weights on the shortest path between them.

**M2**: Return the ratio of open triangles to closed triangles.

**M3**: Return the top k open triangles. A triangle is given higher prioirty if it has a larger total edge weight. Store the triangles in a heap (see M7)

**M4**: (Early Deadline) Given a seed node with id i, and weight vector w (unrelated to edge weights), find the top k-skilled individuals around i.
If the weight vector w = \[w1, w2, w3 ... wd] and the skill fector of a neighboring node f = \[f1, f2, ....\], then the prioirity of a node is given by dot(w, f) = w1f1 + w2f2 + .... + wdfd

**M5**: Given a seed node i and weight vector w, give the highest scoring node that does not have an edge connecting to i

**M6**: Given two seed nodes i, j and weight vector w, compute the similarites of their top-k neighborhoods unsing the Jacard Index

**M7**: Insert a node into the graph. Insert an edge into the graph. Incrementally compute M2 and M3 such that the cost of the insert plus the cost of the next call to M2 or M3 will be exponentiall faster than if the results were calculated from scratch.

Bonus:

**M8**: Remove a node  and edge from the graph. Incrementally compute M2 and M3 such that the cost of the insert plus the cost of the next call to M2 or M3 will be exponentiall faster than if the results were calculated from scratch. will only be evaluated if M1-M7 are completed. Will only receive points if incremental computation of M2 and M3 are implemented.

## The Code
Included in this repo are 3 header files: `GraphHelper.h`, `FeatureGraph.h` and `GraphAnalyzer.h`, and three .cpp files: `FeatureGraph.cpp`, `GraphAnalyzer.cpp` and `GraphTest.cpp`. 

`GraphHelper.h` contains an edge struct and a Triangle class to help you build your graph class. You may only edit the Triangle class.

The `FeatureGraph` files are meant to matinain the graph information.  You will have to determine the appropriate fields and implement the basic graph operations including the constructor and insert.

The `GraphAnalyzer` files are meant to be a wrapper around the `FeatureGraph` so the code to build the graph and analyze the graph are separated. This class contains all of the methods M1-M8 outlined above. 

Note that both the `GraphAnalyzer` and the `FeatureGraph` have an insert function. you will implement the actual insertion into the graph in the `FeatureGraph` class stored in the `GraphAnalyzer` because that is where the graph is stored. The `GraphAnalyzer` has its own insert function so it can follow the cost constriants on M2 and M3 at each insert as outlined in M7. In order to meet these constraints, you will need to have a heap as a private field in `GraphAnalyzer`.

Our testing code will always follow the following the pattern:

1. Build a graph using the `FeatureGraph` constructor

2. Make a `GraphAnalyzer` by passing in the above graph into the `GraphAnalyzer` constructor

3. Call all functions, including insert, on `GraphAnalyzer`

`GraphAnalyzer` will insert the node or edge into its graph and then make updates for fast computation of M2 and M3. We have already placed the call to `FeatureGraph` insert in the `GraphAnalyzer` inserts.

`GraphTest.cpp` gives an example for how we call each of your GraphAnalyzer methods. 

To run `GraphTest`, run the following commands:
```
make
./GraphTester.o
```
It is highly recommended that you do not edit the make file, and instead add your own tests to GraphTester.

## Submission:
Please submit to Gradescope, unzipped:
`FeatureGraph.cpp`, `FeatureGraph.h`, `GraphAnalyzer.cpp`, `GraphAnalyzer.h`, and `GraphHelper.h`. Do not dubmit any other files.

## Deadlines
**Novemebr 23rd**: In order to encourage you to start early 10% of your grade will be given for passing autograded testing for M4 by November 23rd at 11:59pm.

**December 7th**: The entire assignment will be due December 7th at 11:59pm
