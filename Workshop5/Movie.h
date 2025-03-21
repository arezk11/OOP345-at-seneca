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
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <iostream>
#include <string>


namespace sdds
{
    class Movie
    {
        std::string m_title = "";
        size_t m_year = 0;
        std::string m_desc = "";


    public:
        Movie() {}
        const std::string& title() const;
        Movie(const std::string& strMovie);

        template <typename T>
        void fixSpelling(T& spellChecker) 
        {
            spellChecker(m_title);
            spellChecker(m_desc);
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& src);
    };
}
#endif // !SDDS_MOVIE_H