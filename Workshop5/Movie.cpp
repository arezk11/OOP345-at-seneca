/*
*****************************************************************************
                        Workshop 5 - Part 2
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
#include <iostream>
#include <iomanip>
#include "Movie.h"

using namespace sdds;
namespace sdds
{
    const std::string& Movie::title() const 
    {
        return m_title;
    }

    Movie::Movie(const std::string& strMovie) {
       

        std::string temp = strMovie;
        size_t t_index = 0;

        //a lambda function to remove the leading and the trailing spaces
        auto removeSpace = [](std::string& src) 
        {
            src.erase(0, src.find_first_not_of(' '));
            src.erase(src.find_last_not_of(' ') + 1);
        };

        //a lambda function to extract the field from the string
        auto extractField = [&temp, &t_index, removeSpace]() 
        {
            removeSpace(temp);
            t_index = temp.find(',');
            std::string field = temp.substr(0, t_index);
            removeSpace(field);
            temp.erase(0, t_index + 1);
            return field;
        };

        m_title = extractField();
        m_year = std::stoi(extractField());

        //remove the leading and trailing spaces from the remaining description
        removeSpace(temp);
        removeSpace(temp);

        //store the remaining description
        m_desc = temp;
    }


    std::ostream& operator<<(std::ostream& os, const Movie& src) 
    {
        os << std::setw(40) << std::right << src.m_title << " | ";
        os << std::left << std::setw(4) << src.m_year << " | " << src.m_desc << std::endl;

        return os;
    }
}