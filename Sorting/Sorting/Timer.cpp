//
// Created by StasH on 12/06/12.
//
// Timer class for analyzing algorithm performance
// (originally by David R. Musser)
//

#include <iostream>
#include "Timer.h"


void Timer::start (const unsigned int r)
{
	reps = r;
	count = 0;
	iterations.clear();
	iterations.reserve(reps);
	initial = time(0);
}


// TODO: what if it takes more than 1 second?
bool Timer::check()
{
	++count;
	final = time(0);

	// only if 1 second pass
	if (initial < final)
	{
		iterations.push_back(count);
		initial = final;
		count = 0;
	}
	return (iterations.size() < reps);
}


long Timer::result()
{
	bool isDebug = false;

	std::sort(iterations.begin(), iterations.end());

	if (isDebug) {
		std::cout << "Sorted counts:" << std::endl;
		for (unsigned int k = 0; k < iterations.size(); ++k) {
			std::cout << iterations[k] << " ";
			if ((k+1) % 10 == 0)
				std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	long selected_count = iterations[reps/2];

	if (isDebug)
		std::cout << "Selected count: " << selected_count << std::endl;

	return selected_count;

//	double calculated_time, growth_factor;
//
//	// result = 1000 ms (1 sec) / count;
//	result_map[problem_size] = calculated_time = 1000.0/selected_count;
//
//	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4)
//		<< std::setw(35) << problem_size << std::setw(12) << calculated_time << " ms ";
//
//	if (result_map.find(problem_size/2) != result_map.end())
//	{
//		growth_factor = result_map[problem_size] / result_map[problem_size/2];
//
//		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4) << std::setw(8) << growth_factor;
//	}
//	std::cout << std::endl;
}

