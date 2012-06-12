//
//  main.cpp
//  Sorting
//
//  Created by Stas Shumeyko on 06/12/12.
//  Copyright (c) 2012. All rights reserved.
//
// For sorting is used shuffled vector with increasing numbers, starting from 1
// Perform N measurements of sorting vector of size vectorSize using each algorithm
// and get average time of work


#include <vector>
#include <iostream>
#include <iomanip>
#include "Timer.h"


static const unsigned vectorSize = 10; // size of vector
static const unsigned repetitionCount = 7; // how much times repeat calculation


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

	for (int i = 1; i < vectorSize*N; ++i)
		inputVector.push_back (i);

	std::random_shuffle (inputVector.begin (), inputVector.end ());


	std::vector<int> workVector;

	// Функция check () запоминает количество циклов, выполненых в секунду. И производит
	// repetitionCount количество замеров (т.е. делает замеры repetitionCount секунд).
	// Функция report() берет средний по времени замер (не вычисляет, а из имеющихся!)
	// и сохраняет его в качестве результата для указанного объема работы.
	timer.start (repetitionCount);
	do
	{
		workVector = inputVector;
		std::sort (workVector.begin (), workVector.end ());
	} while (timer.check ());

	double calculated_time = 1000.0 / timer.result ();

	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4)
			<< std::setw(4) << vectorSize*N << std::setw(12) << calculated_time << " ms " << std::endl;

	}
	return 0;
}
