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
#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#define  MAXSIZE 6 

#include <iostream>
#include <string>


namespace sdds
{

    class SpellChecker
    {
        std::string m_badWords[MAXSIZE]{};
        std::string m_goodWords[MAXSIZE]{};
        size_t m_replacementCount[MAXSIZE]{};

    public:
        SpellChecker() {}
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}
#endif // !SDDS_SPELLCHECKER_H