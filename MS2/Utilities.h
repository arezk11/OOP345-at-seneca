// Name:Ali Rezk
// Seneca Student ID:105593222
// Seneca email:arezk1@myseneca.ca
// Date of completion:11-11-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

namespace sdds
{
    class Utilities
    {
        //specifies the length of the token extracted
        size_t m_widthField = 1;

        //separates the tokens in any given std::string object.
        static char m_delimiter;

    public:
        //sets the field width of the current object to the value of parameter newWidth
        void setFieldWidth(size_t newWidth);

        //returns the field width of the current object
        size_t getFieldWidth() const;

        //extracts a token from string str referred to by the first parameter.
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        //sets the delimiter for this class to the character received
        static void setDelimiter(char newDelimiter);

        //returns the delimiter for this class.
        static char getDelimiter();
    };
}
#endif