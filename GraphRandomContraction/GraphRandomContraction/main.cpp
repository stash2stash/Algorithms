//
//  main.cpp
//  GraphRandomContraction
//
//  Created by Stas Shumeyko on 07/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
// Realisation of graph randomized contraction algorithm for the min cut problem

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;


struct Edge
{
	int fromNode;
	int toNode;
};


void removeLoops (vector<Edge>& edges)
{
	for (vector<Edge>::iterator i=edges.begin (); i!=edges.end ();) {
		if (i->fromNode == i->toNode)
			i = edges.erase (i);
		else
			++i;
	}
}


void randomContraction (vector<Edge>& edges)
{
	// pick random edge
	int edge = rand() % edges.size ();

	// only for good reading
	int firstNode = edges[edge].fromNode;
	int secondNode = edges[edge].toNode;

	// replace second node by first node (keep only first node)
	for (int i = 0; i < edges.size (); ++i) {
		if (edges[i].fromNode == secondNode)
			edges[i].fromNode = firstNode;
		if (edges[i].toNode == secondNode)
			edges[i].toNode = firstNode;
	}

	// remove loops
	removeLoops (edges);
}



int main(int argc, const char * argv[])
{
	srand (unsigned(time (0)));

	string fileName = "/Users/StasH/Downloads/kargerMinCut.txt";
//	cout << "Input array file name: ";
//	cin >> fileName;

	ifstream inputFile;
	inputFile.open (fileName.c_str ());

	if (!inputFile) {
		cout << "Error opening file: " << fileName << endl;
		return -1;
	}

	vector<Edge> edges;
	int nodes = 0;

	while (!inputFile.eof ()) {
		string fileString;
		getline (inputFile, fileString);
		stringstream stringStream (fileString);

		int fromNode = -1;
		int toNode = -1;
		stringStream >> fromNode;

		if (fromNode <= 0)
			break;

		while (stringStream >> toNode) {
			Edge edge;
			edge.fromNode = fromNode;
			edge.toNode = toNode;
			edges.push_back (edge);
		}

		++nodes;
	}

	inputFile.close ();

	cout <<"Read " << nodes << " nodes and " << edges.size () << " edges" << endl;

	removeLoops (edges);


	// run a lot of turns to get a min result
	int result = edges.size ();
	for (int turn=0; turn < 2*nodes; ++turn)
	{
	    vector<Edge> workEdges = edges;
		int workNodes = nodes;

		while (workNodes > 2)
		{
			randomContraction (workEdges);
			--workNodes;
		}

		// result divided by 2 because each edge has it inverted twin (eg 1-2 and 2-1)
		cout << "Result [" << turn+1 << "] " << workEdges.size ()/2 << endl;
		if (result > workEdges.size ()/2)
			result = workEdges.size ()/2;
	}

	cout << "Minimum result: " << result << endl;

	return 0;
}
