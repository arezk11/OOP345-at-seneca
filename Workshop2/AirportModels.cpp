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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include "AirportModels.h"
#include <cstring>

using namespace std;
namespace sdds {

	//for checking if empty 
	bool Airport::isEmpty() const {

		return (code == "" || name == "" || city == "" ||
			state == "" || country == "" ||
			latitude == 0.0 || longitude == 0.0);
	}

	std::ostream& operator<<(std::ostream& os, const Airport& airport)
	{
		if (airport.isEmpty())
		{
			os << "Empty Airport";
		}
		else {
			os << setfill('.') << setw(20) << right << "Airport Code" << " : " << left << setw(30) << airport.code << endl;
			os << setfill('.') << setw(20) << right << "Airport Name" << " : " << left << setw(30) << airport.name << endl;
			os << setfill('.') << setw(20) << right << "City" << " : " << left << setw(30) << airport.city << endl;
			os << setfill('.') << setw(20) << right << "State" << " : " << left << setw(30) << airport.state << endl;
			os << setfill('.') << setw(20) << right << "Country" << " : " << left << setw(30) << airport.country << endl;
			os << setfill('.') << setw(20) << right << "Latitude" << " : " << left << setw(30) << airport.latitude << endl;
			os << setfill('.') << setw(20) << right << "Longitude" << " : " << left << setw(30) << airport.longitude << endl;
		}
		return os;
	}

	AirportLog::AirportLog() : m_airports(nullptr), m_count(0) {}

	//file constructor
	AirportLog::AirportLog(const char* filename) : m_airports(nullptr), m_count(0)
	{
		ifstream file(filename);
		if (file.is_open()) {
			string line;
			getline(file, line, '\n');

			for (m_count = 0; getline(file, line, '\n');) {
				if (line.length()) {
					m_count++;
				}
			}

			//reset to beginning
			file.clear();
			file.seekg(0, std::ios::beg);

			m_airports = new Airport[m_count];
			getline(file, line, '\n');

			for (size_t i = 0; i < m_count && file; i++) 
			{
				getline(file, m_airports[i].code, ',');
				getline(file, m_airports[i].name, ',');
				getline(file, m_airports[i].city, ',');
				getline(file, m_airports[i].state, ',');
				getline(file, m_airports[i].country, ',');
				file >> m_airports[i].latitude;
				file.ignore();
				file >> m_airports[i].longitude;
				file.ignore();
			}
		}
		file.close();
	}

	AirportLog::~AirportLog() {
		delete[] m_airports;
	}

	//adding an airport to the dynamic array
	void AirportLog::addAirport(const Airport& airport) 
	{
		//create a new dynamic array with one more slot for the new airport
		Airport* newAirports = new Airport[m_count + 1];

		//coping existing airports to the new array
		for (size_t i = 0; i < m_count; i++)
		{
			newAirports[i] = m_airports[i];
		}

		newAirports[m_count] = airport;

		delete[] m_airports;
		m_airports = newAirports;

		m_count++;
	}

	AirportLog AirportLog::findAirport(const char* state, const char* country) const
	{
		AirportLog sortedAirports;

		for (size_t i = 0; i < m_count; i++)
		{
			if (strcmp(m_airports[i].state.c_str(), state) == 0 && 
				strcmp(m_airports[i].country.c_str(), country) == 0) 
			{
				sortedAirports.addAirport(m_airports[i]);
			}
		}
		return sortedAirports;
	}

	//access an airport by index
	Airport AirportLog::operator[](size_t index)
	{
		if (index < m_count) 
		{
			return m_airports[index];
		}
		//return an empty Airport 
		return Airport();
	}

	AirportLog::operator size_t() const
	{
		return m_count;
	}

	//rule of three:copy constructor 
	AirportLog::AirportLog(const AirportLog& src): m_count(src.m_count)
	{
		m_airports = new Airport[m_count];
		for (size_t i = 0; i < m_count; i++) 
		{
			m_airports[i] = src.m_airports[i];
		}
	}

	//rule of three: copy assignment
	AirportLog& AirportLog::operator=(const AirportLog& src)
	{
		if (this != &src) 
		{
			delete[] m_airports;

			m_count = src.m_count;

			m_airports = new Airport[m_count];

			for (size_t i = 0; i < m_count; i++)
			{
				m_airports[i] = src.m_airports[i];
			}
		}
		return *this;
	}

	//rule of five:move constructor
	AirportLog::AirportLog(AirportLog&& other) noexcept 
    : m_airports(other.m_airports), m_count(other.m_count) 
	{
		other.m_airports = nullptr;
		other.m_count = 0;
	}

	//rule of five: move assignment
	AirportLog& AirportLog::operator=(AirportLog&& other) noexcept 
	{
		if (this != &other)
		{
			delete[] m_airports;

			m_airports = other.m_airports;

			m_count = other.m_count;

			other.m_airports = nullptr;
			other.m_count = 0;
		}
		return *this;
	}

}
