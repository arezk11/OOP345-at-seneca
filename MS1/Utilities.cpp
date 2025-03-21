// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:11-11-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter = ' ';

    //sets the field width of the current object to the value of parameter newWidth
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    //returns the field width of the current object
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    //extracts a token from string str referred to by the first parameter.
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) 
    {
        std::string token = "";
        size_t position = next_pos;

        next_pos = str.find(m_delimiter, position);


        //use the delimiter to extract the next token from str starting position at next_pos.
        if (next_pos == std::string::npos)
        {
            token = str.substr(position);
            more = false;
        }
        else 
        {
            token = str.substr(position, next_pos - position);
            more = true;
        }

        //reports an exception if a delimiter is found at next_pos.
        if (position == next_pos) 
        {
            more = false;
            throw ("DELIMITER FOUND!");
        }

        //trim spaces 
        token.erase(token.find_last_not_of(" ") + 1);
        token.erase(0,token.find_first_not_of(" "));

        //update the current object's m_widthField data member if its current value is less than the size of the token extracted.
        if (token.length() > m_widthField)
        {
            m_widthField = token.length();
        }

        next_pos++;

        return token;
    }

    //sets the delimiter for this class to the character received
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    //returns the delimiter for this class.
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}