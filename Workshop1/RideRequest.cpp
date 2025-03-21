/*
*****************************************************************************
						Workshop 1- Part 2
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
#define MAX_CUST_SIZE 10

#include "RideRequest.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

double g_taxrate = 0.0;
double g_discount = 0.0;

using namespace std;
namespace sdds {

	int RideRequest::s_counter = 0;

	RideRequest::RideRequest()
	{
		m_customerName[0] = '\0';
		m_rideDescription = nullptr;
		m_price = 0.0;
		m_discount = false;
	}

	void RideRequest::clear()
	{
		delete[] m_rideDescription;
		m_rideDescription = nullptr;

	}

	//rule of three (destructor)
	RideRequest::~RideRequest() 
	{
		if (m_rideDescription != nullptr)
		{
			clear();
		}
	}

	//rule of three(copy constructor)
	RideRequest::RideRequest(const RideRequest& src)
	{

		m_price = src.m_price;
		m_discount = src.m_discount;
		strcpy(m_customerName, src.m_customerName);

		//deep copying
		m_rideDescription = new char[strlen(src.m_rideDescription) + 1];
		strcpy(m_rideDescription, src.m_rideDescription);


	}

	//rule of three(copy assignment operator)
	RideRequest& RideRequest::operator=(const RideRequest& src)
	{
		if (this != &src)
		{
			m_price = src.m_price;
			m_discount = src.m_discount;
			strcpy(m_customerName, src.m_customerName);

			clear();

			m_rideDescription = new char[strlen(src.m_rideDescription) + 1];
			strcpy(m_rideDescription, src.m_rideDescription);

		}

		return *this;
	}


	void RideRequest::read(std::istream& is)
	{
		if (is) 
		{
			is.getline(m_customerName, MAX_CUST_SIZE, ',');


			clear();

			//read the description into a temp string
			string t_description;
			getline(is, t_description, ',');

			m_rideDescription = new char[t_description.length() + 1];
			strcpy(m_rideDescription, t_description.c_str());

			char delimiter;
			is >> m_price >> delimiter;

			char discount;
			is >> discount;
			m_discount = (discount == 'Y');
		}
	}


	void RideRequest::display() const
	{
		s_counter++;

		cout << left << setw(2) << s_counter << ". ";

		if (m_customerName[0] != '\0')
		{
			cout << left << setw(10) << m_customerName << "|";
			cout << left << setw(25) << m_rideDescription << "|";

			double priceWithTax = m_price + (m_price * g_taxrate);
			cout << left << fixed << setprecision(2) << setw(12) << priceWithTax << "|";

			if (!m_discount)
			{
				cout << endl;
			}
			else
			{
				double priceWithDiscount = priceWithTax - g_discount;
				cout << right << fixed << setw(13) << priceWithDiscount << endl;
			}
		}
		else
		{
			cout << "No Ride Request" << endl;
		}
	}
}
