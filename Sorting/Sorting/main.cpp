//
//  main.cpp
//  Sorting
//
//  Created by Stas Shumeyko on 06/12/12.
//  Copyright (c) 2012. All rights reserved.
//

#include "Timer.h"

#include <vector>
#include <iostream>
#include <iomanip>


static const unsigned vectorSize = 500; // starting size of vector
static const unsigned repetitionCount = 7; // how much times repeat calculation


// Merge sorting algorithm (using recursion)
// O(nlogn)
void mergeSort (std::vector<int>& array)
{
	// check for end of recursion
	if (array.size () == 1)
		return;

	// split array into two parts and sort each part separately
	std::vector<int> part1 (array.begin (), array.begin () + array.size ()/2);
	std::vector<int> part2 (array.begin () + array.size ()/2, array.end ());

	mergeSort (part1);
	mergeSort (part2);

	// merge parts together
	std::vector<int>::iterator iter1 = part1.begin ();
	std::vector<int>::iterator iter2 = part2.begin ();

	array.clear ();

	do
	{
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
		}

	} while (true);

}


// Bubble sort (just for fun)
// O(n^2)
void bubleSort (std::vector<int>& array)
{
	for (int i = 0; i < array.size (); i++)
		for (int j = i; j < array.size (); j++)
		{
			if (array[i] > array [j])
				std::swap (array [i], array [j]);
		}
}



int main(int argc, const char * argv[])
{
	srand (unsigned (time (0)));

	Timer timer;

	// Умножение на два это хорошая идея, так как можно сразу посмотреть, как увеличивается
	// время работы с удвоением размера и примерно оценить сложность алгоритма.
	for (int N = 1; N < 10; N*=2)
	{
		// vector for sort
		std::vector<int> inputVector;
		inputVector.reserve (vectorSize*N);

		for (int i = 0; i < vectorSize*N; ++i)
			inputVector.push_back (i);

		std::random_shuffle (inputVector.begin (), inputVector.end ());


		std::vector<int> workVector;

		// Функция check () запоминает количество циклов, выполненых в секунду. И производит
		// repetitionCount количество замеров (т.е. делает замеры repetitionCount секунд).
		// Функция report() берет средний по времени замер (не вычисляет, а из имеющихся!)
		// и сохраняет его в качестве результата для указанного объема работы.

		// std::sort O(nlogn)
		timer.start (repetitionCount);
		do
		{
			workVector = inputVector;
			std::sort (workVector.begin (), workVector.end ());
		} while (timer.check ());

		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4)
			<< std::setw (12) << "std::sort "
			<< std::setw(4) << vectorSize*N << std::setw(12) << 1000.0 / timer.result () << " ms " << std::endl;


		// merge sort
		timer.start (repetitionCount);
		do
		{
			workVector = inputVector;
			mergeSort (workVector);
		} while (timer.check ());

		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4)
			<< std::setw (12) << "merge "
			<< std::setw(4) << vectorSize*N << std::setw(12) << 1000.0 / timer.result () << " ms " << std::endl;


		// bubble sort
		timer.start (repetitionCount);
		do
		{
			workVector = inputVector;
			bubleSort (workVector);
		} while (timer.check ());

		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4)
				<< std::setw (12) << "buble "
				<< std::setw(4) << vectorSize*N << std::setw(12) << 1000.0 / timer.result () << " ms " << std::endl;

	}

	return 0;
}
