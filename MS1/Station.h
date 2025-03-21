// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:11-11-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

using namespace std;
namespace sdds
{
    class Station
    {
        //the id of the station
        int m_id=0; 

        //the name of the item handled by the station
        string m_itemName = ""; 

        //the description of the station
        string m_itemDesc = "";

        // the next serial number to be assigned to an item at this station
        size_t m_serialNum = 0; 
         
        // the number of items currently in stock
        size_t m_currentItems = 0; 

        //class Variables:
        //the maximum number of characters required to print to the screen
        static size_t m_widthField;

        //variable used to generate IDs for new instances of type Station.
        static size_t id_generator;

    public:
        //custom 1-argument constructor
        Station(const std::string& src);

        //returns the name of the current Station object
        const std::string& getItemName() const;

        //returns the next serial number
        size_t getNextSerialNumber();

        //returns the remaining quantity of items
        size_t getQuantity() const;

        //subtracts 1 from the available quantity
        void updateQuantity();

        void display(std::ostream& os, bool full) const;
    };
}
#endif