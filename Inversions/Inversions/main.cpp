//
//  main.cpp
//  Inversions
//
//  Created by Stas Shumeyko on 06/15/12.
//  Copyright (c) 2012. All rights reserved.
//
// Counting Inversions in given array
//


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


// Using merge sort, count inversions in the given array
long sortAndCount (vector<int>& array)
{
	if (array.size () <= 1)
		return 0;

	vector<int> part1 (array.begin (), array.begin () + array.size ()/2);
	vector<int> part2 (array.begin () + array.size ()/2, array.end ());

	long count1 = sortAndCount (part1);
	long count2 = sortAndCount (part2);

	// merge and count

	long count3 = 0;
	vector<int>::iterator iter1 = part1.begin ();
	vector<int>::iterator iter2 = part2.begin ();

	array.clear ();
	while (true) {
		// end of part1
		if (iter1 == part1.end ()) {
			array.insert (array.end (), iter2, part2.end ());
			break;
		}

		// end of part2
		if (iter2 == part2.end ()) {
			array.insert (array.end (), iter1, part1.end ());
			break;
		}

		if (*iter1 < *iter2) {
			array.push_back (*iter1);
			++iter1;
		}
		else {
			array.push_back (*iter2);
			++iter2;

			// count of the rest elements in part1
			count3 += (part1.end () - iter1);
		}
	}

	return count1 + count2 + count3;
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
//	inputArray.push_back (1);
//	inputArray.push_back (3);
//	inputArray.push_back (5);
//	inputArray.push_back (2);
//	inputArray.push_back (4);
//	inputArray.push_back (6);
//	// ANSWER: 3

	cout <<"Read " << inputArray.size () << " elements" << endl;

	long inversions = sortAndCount (inputArray);

	cout << "Inversions: " << inversions << endl;

	return 0;
}
