//
//  main.cpp
//  Strongly Connected Components
//
//  Created by Stas Shumeyko on 07/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
// Realisation of Strongly Connected Components calculation on graph

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>


using namespace std;


struct Node
{
	vector<int> edges;
	bool isVisited;
};


static int times = 0; // # of processed nodes
static int currentNode = -1; // current source vertex
static map<int, int> leaders;
static map<int, int> finishTimes;


void DFS (map<int, Node>& nodes, int node)
{
	nodes[node].isVisited = true;
	leaders[node] = currentNode;

	for (int i = 0; i < nodes[node].edges.size(); ++i) {
		int toNode = nodes[node].edges[i];
		if (nodes [toNode].isVisited != true) {
			DFS (nodes, toNode);
		}
	}
	++times;
	finishTimes [node] = times;
}



void DFS_loop (map<int, Node>& nodes)
{
	times = 0;
	currentNode = -1;

	for (map<int, Node>::reverse_iterator i = nodes.rbegin (); i != nodes.rend (); ++i) {
		if (i->second.isVisited != true) {
			currentNode = i->first;
			DFS (nodes, i->first);
		}
	}
}



int main(int argc, const char * argv[])
{
	string fileName = "/Users/StasH/Downloads/SCC.txt";
//	cout << "Input array file name: ";
//	cin >> fileName;

	ifstream inputFile;
	inputFile.open (fileName.c_str ());

	if (!inputFile) {
		cout << "Error opening file: " << fileName << endl;
		return -1;
	}

	map<int, Node> nodes_rev;
	int edges = 0;

	while (!inputFile.eof ()) {
		string fileString;
		getline (inputFile, fileString);
		stringstream stringStream (fileString);

		int fromNode = -1;
		int toNode = -1;
		stringStream >> fromNode;

		if (fromNode <= 0)
			break;

		stringStream >> toNode;

		// reverse
		swap (toNode, fromNode);

		if (nodes_rev.find (fromNode) == nodes_rev.end ()) {
			Node node;
			node.isVisited = false;
			nodes_rev [fromNode] = node;
		}
		nodes_rev [fromNode].edges.push_back (toNode);
		// sort edges
		sort (nodes_rev [fromNode].edges.begin (), nodes_rev [fromNode].edges.end ());
		++edges;
	}

	inputFile.close ();

	cout <<"Read " << nodes_rev.size () << " nodes and " << edges << " edges" << endl;

	DFS_loop (nodes_rev);

	cout << "----- times" << endl;

//	for (map<int,int>::iterator i = finishTimes.begin (); i!=finishTimes.end (); ++i) {
//		cout << "[" << i->first << "] = " << i->second << endl;
//	}

	// reverse and replace nodes by finish times

	// 1. construct new nodes using finish times
	map<int, Node> nodes;

	cout << "Construct new nodes" << endl;
	for (map<int,int>::iterator i = finishTimes.begin (); i!=finishTimes.end (); ++i) {
		Node node;
		node.isVisited = false;
		nodes [i->second] = node;
	}

	// 2. reverse edges
	cout << "Reversing edges" << endl;
	for (map<int, Node>::iterator i=nodes_rev.begin (); i!=nodes_rev.end (); ++i)
		for (int node = 0; node < (i->second).edges.size(); ++node) {
			int fromNode = finishTimes [i->first];
			int toNode = finishTimes [(i->second).edges[node]];

			swap (fromNode, toNode);

//			cout << i->first << "," << (i->second).edges[node] << ": " << fromNode << " -> " << toNode << endl;

			nodes [fromNode].edges.push_back (toNode);

			// sort edges
			sort (nodes_rev [fromNode].edges.begin (), nodes_rev [fromNode].edges.end ());
		}

	cout << "Run DFS" << endl;

	DFS_loop (nodes);

	cout << "----- leaders" << endl;

//	for (map<int,int>::iterator i = leaders.begin (); i!=leaders.end (); ++i) {
//		cout << "[" << i->first << "] = " << i->second << endl;
//	}

	map<int,int> scc; // Strongly Connected Components - <leader node, number of nodes>

	for (map<int,int>::iterator i = leaders.begin (); i!=leaders.end (); ++i) {
		++scc[i->second];
	}

	cout << "----- maximum SCCs" << endl;

	struct IntCompare {
		bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
			return lhs.second < rhs.second;
		}
	};

	// make vector from map and sort it
	vector< pair<int, int> > cssVector(scc.begin(), scc.end());
	sort (cssVector.begin(), cssVector.end(), IntCompare());

	// show last displayNumber elements
	int displayNumber = 5;
	if (cssVector.size () < displayNumber)
		displayNumber = cssVector.size ();

	for (int i = cssVector.size () - displayNumber; i < cssVector.size (); ++i) {
		std::cout
				<< (cssVector.size () - i) << ": leader (" << cssVector[i].first
				<< ") = " << cssVector[i].second << endl;
	}

	return 0;
}
