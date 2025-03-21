// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:11-11-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    //Initial value is 0.
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;


    Station::Station(const std::string& src) {
        Utilities utilityObj;

        //increment the id_generator and assign the new value to the m_id variable
        m_id = ++id_generator;

        bool validRecord = true;

        //starting posistion
        size_t position = 0;

        //extract item name 
        m_itemName = utilityObj.extractToken(src, position, validRecord);

        //use stoi to convert the extracted tokens to integer
        m_serialNum = std::stoi(utilityObj.extractToken(src, position, validRecord));
        m_currentItems = std::stoi(utilityObj.extractToken(src, position, validRecord));

        //before extracting description, it updates Station::m_widthField to the maximum
        //value of Station::m_widthField and Utilities::m_widthField.
        m_widthField = std::max(utilityObj.getFieldWidth(), m_widthField);
        m_itemDesc = utilityObj.extractToken(src, position, validRecord);

    }

    //returns the name of the current Station object
    const std::string& Station::getItemName() const
    {
        return m_itemName;
    }

    //returns the next serial number to be used on the assembly line and increments
    size_t Station::getNextSerialNumber()
    {
        ++m_serialNum;
        return m_serialNum - 1;
    }

    //returns the remaining quantity of items in the Station object
    size_t Station::getQuantity() const
    {
        return m_currentItems;
    }

    //ubtracts 1 from the available quantity; should not drop below 0.
    void Station::updateQuantity()
    {
        if (m_currentItems > 0)
        {
            --m_currentItems;
        }
    }


    void Station::display(std::ostream& os, bool full) const
    {
        os << right << setw(3) << setfill('0') << m_id;
        os << " | " << left << setw(m_widthField) << setfill(' ') << m_itemName;
        os << " | " << right << setw(6) << setfill('0') << m_serialNum << " | ";

        if (full)
        {
            os << right << setw(4) << setfill(' ') << m_currentItems << " | " << m_itemDesc;
        }
        os << endl;
    }
}