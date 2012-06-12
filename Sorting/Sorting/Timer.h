//
// Created by StasH on 12/06/12.
//
// Timer class for analyzing algorithm performance
// (originally by David R. Musser)
//

// TODO: Convert class to singletone

#ifndef __Timer_H_
#define __Timer_H_

#include <sys/types.h>
#include <vector>
#include <map>


class Timer
{
public:

	void start(unsigned int r); // Start a series of r trials
	bool check(); // Returns true if the trials have been completed, else false
	long result(); // Returns the average number of iterations per second

private:
	unsigned int reps;  // Number of trials
	std::vector<long> iterations; // For storing loop iterations of a trial
	time_t initial, final; // For saving initial and final times of a trial
	unsigned long count; // For counting loop iterations of a trial

};



#endif //__Timer_H_
