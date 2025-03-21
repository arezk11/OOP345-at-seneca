/*
*****************************************************************************
						Workshop 2- Part 2
Full Name  : Ali Rezk
Student ID#: 105593222
Email      : arezk1@myseneca.ca
Section    : ZBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#include "Timer.h"
using namespace std;
namespace sdds {
	void Timer::start() 
	{
		//get the current time and store it in the 'startTime' member variable
		startTime = std:: chrono::steady_clock::now();
	}

	long long Timer::stop()
	{
		std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

		std::chrono::nanoseconds timePassed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
		return timePassed.count();
	}

}