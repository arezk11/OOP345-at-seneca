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
#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>

namespace sdds {
	class Timer {
		std::chrono::steady_clock::time_point startTime;

	public:
		void start();
		long long stop();
	};
}
#endif