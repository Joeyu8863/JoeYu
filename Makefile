CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

tester: GraphTest.o GraphAnalyzer.o FeatureGraph.o
	$(CXX) $(CXXFLAGS) -o GraphTester.o GraphTest.o GraphAnalyzer.o FeatureGraph.o

GraphTest.o: GraphTest.cpp GraphAnalyzer.h FeatureGraph.h GraphHelper.h
	$(CXX) $(CXXFLAGS) -c GraphTest.cpp

GraphAnalyzser.o: GraphAnalyzer.cpp FeatureGraph.h GraphHelper.h
	$(CXX) $(CXXFLAGS) -c GraphAnalyzer.cpp

FeatureGraph.o: FeatureGraph.cpp GraphHelper.h
	$(CXX) $(CXXFLAGS) -c FeatureGraph.cpp



.PHONY: clean
clean:
	rm -f *.o
