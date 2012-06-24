//
//  main.cpp
//  QuickSort
//
//  Created by Stas Shumeyko on 06/23/12.
//  Copyright (c) 2012. All rights reserved.
//
// Quick sort realisation


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

static long comparisons = 0;



int choosePivot (vector<int>& input, int first, int last)
{
	// 3
	int middle = (last-first)/2 + first;

	int maxValue = max (max (input[first], input[middle]), input[last]);
	int minValue = min (min (input[first], input[middle]), input[last]);

	if (input[middle] != minValue && input[middle] != maxValue)
		swap (input[middle], input[first]);
	else {
		if (input[last] != minValue && input[last] != maxValue)
			swap (input[last], input[first]);
	}

//	// 2
//	swap (input[first], input[last]);

	return input [first];
}


void quickSort (vector<int>& input, unsigned first, unsigned last)
{
	int size = (last - first) + 1;

	if(size <= 1)
		return;

	comparisons += size - 1;

	int p = choosePivot (input, first, last);

	// partition

	unsigned less_p = first + 1;

	for (unsigned more_p = less_p; more_p <= last; ++more_p)
		if (input[more_p] < p) {
			swap (input[less_p], input[more_p]);
			++less_p;
		}
	swap (input[less_p-1], input[first]);

	quickSort (input, first, less_p-2);
	quickSort (input, less_p, last);

}


int main(int argc, const char * argv[])
{
	string fileName = "";
	cout << "Input array file name: ";
	cin >> fileName;

	ifstream inputFile;
	inputFile.open (fileName.c_str ());

	if (!inputFile) {
		cout << "Error opening file: " << fileName << endl;
		return -1;
	}

	vector<int> inputArray;

	while (!inputFile.eof ()) {
		int data=0;
		inputFile >> data;
		inputArray.push_back (data);
	}

	inputFile.close ();

//	// TEST
//	inputArray.clear ();
//	inputArray.push_back (3);
//	inputArray.push_back (8);
//	inputArray.push_back (2);
//	inputArray.push_back (5);
//	inputArray.push_back (1);
//	inputArray.push_back (4);
//	inputArray.push_back (7);
//	inputArray.push_back (6);

	cout <<"Read " << inputArray.size () << " elements" << endl;

	cout << "Input:  ";
	for (int i = 0; i < inputArray.size (); ++i)
		cout << inputArray[i] << " ";
	cout << endl;

	quickSort (inputArray, 0, inputArray.size ()-1);

	cout << "Output: ";
	for (int i = 0; i < inputArray.size (); ++i)
		cout << inputArray[i] << " ";
	cout << endl;

	cout << "Comparisons: " << comparisons << endl;

	return 0;
}
