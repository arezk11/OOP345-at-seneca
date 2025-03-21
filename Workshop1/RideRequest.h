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
#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#define MAX_CUST_SIZE 10

#include <iostream>
#include <iomanip>


extern double g_taxrate; 
extern double g_discount;

namespace sdds {
	class RideRequest {
        static int s_counter;

		char m_customerName[MAX_CUST_SIZE];
		char* m_rideDescription;
		double m_price;
		bool m_discount;


	public:
		RideRequest();
		~RideRequest();
		
        //Copy constructor
		RideRequest(const RideRequest& src); 

        //Copy assignment operator
		RideRequest& operator=(const RideRequest& src); 
        
		void clear();
		void read(std::istream& is);
		void display() const;
		
	};
}

#endif // SDDS_RIDEREQUEST_H
