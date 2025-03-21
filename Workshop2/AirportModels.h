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
#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

namespace sdds {
	struct Airport {
		std::string code;
		std::string name;
		std::string city;
		std::string state;
		std::string country;
		double latitude;
		double longitude;

		//to check if in empty state
		bool isEmpty() const;
		
	};

	std::ostream& operator<<(std::ostream& os, const Airport& airport);

	class AirportLog {
		Airport* m_airports{ nullptr }; 
		size_t m_count = 0; 

	public:
        //default constructor
		AirportLog(); 
		
		//file Constructor
		AirportLog(const char* filename);

		//rule of thhree: destructor
		~AirportLog(); 

		//to append the parameter to the dynamic array of airports held by the current object
		void addAirport(const Airport& airport);

		AirportLog findAirport(const char* state, const char* country) const;

		//to acess airports by index
		Airport operator[](size_t index);

		//convert the current object to a size_t value
		operator size_t() const;

		//rule of three:copy constructor and copy assignment operator &
		AirportLog(const AirportLog& src);
		AirportLog& operator=(const AirportLog& src);

		//rule of five:move constructor and move assignment operator &&
		AirportLog(AirportLog&& src) noexcept;
		AirportLog& operator=(AirportLog&& src) noexcept;
	};

}

#endif 
