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
#include <iomanip>
#include "Book.h"

using namespace sdds;
namespace sdds
{
    const std::string& Book::title() const {
        return m_title;
    }

    const std::string& Book::country() const {
        return m_country;
    }

    const size_t& Book::year() const {
        return m_year;
    }

    double& Book::price() {
        return m_price;
    }

    Book::Book(const std::string& strBook) {
        std::string _tempStr = strBook;
        int t_index = 0u;

        //a lambda function to remove the leading and the trailing spaces
        auto removeSpace = [](std::string& src) 
        {
            src.erase(0, src.find_first_not_of(' '));
            src.erase(src.find_last_not_of(' ') + 1);
        };

        //a lambda function to extract the field from the string
        auto extractField = [&]() 
        {
            removeSpace(_tempStr);
            t_index = _tempStr.find(',');
            std::string field = _tempStr.substr(0, t_index);
            removeSpace(field);
            _tempStr.erase(0, t_index + 1);
            return field;
        };

        //extract author title country price and year from the input string
        m_author = extractField();
        m_title = extractField();
        m_country = extractField();
        m_price = std::stod(extractField());
        m_year = std::stoi(extractField());

        removeSpace(_tempStr);
        m_description = _tempStr;
    }


    std::ostream& operator<<(std::ostream& os, const Book& src) {
        os << std::setw(20) << std::right << src.m_author << " | " << std::setw(22) << src.title() << " | ";
        os << std::setw(5) << src.country() << " | " << std::setw(4) << src.year() << " | ";
        os << std::setw(6) << std::fixed << std::setprecision(2) << src.m_price << " | ";
        os << std::left << src.m_description << std::endl;

        return os;
    }
}