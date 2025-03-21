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
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"


using namespace sdds;
namespace sdds
{
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);

        if (file) {
         
            //to count the spaces
            int spaces{ 0u };

            //to read the lines from the file
            std::string lines{ "" };


            size_t counter{ 0u };
     
            while (counter < MAXSIZE && getline(file, lines)) {

                //remove the leading spaces
                lines.erase(0, lines.find_first_not_of(' '));

                //find the first space
                spaces = lines.find(' ');

                //store the bad word
                m_badWords[counter] = lines.substr(0, spaces);
                lines.erase(0, spaces);

                lines.erase(0, lines.find_first_not_of(' '));
                spaces = lines.find(' ');
                m_goodWords[counter] = lines.substr(0, spaces);
                ++counter;
            }
        }
        else 
        {
             throw "Bad file name!";
        }
    }

    void SpellChecker::operator()(std::string& text) 
    {
        for (auto i = 0; i < MAXSIZE; ++i) 
        {
            while (text.find(m_badWords[i]) != std::string::npos)
            {

                //find the bad words and replace them with good words
                text.replace(text.find(m_badWords[i]), m_badWords[i].size(), m_goodWords[i]);
                ++m_replacementCount[i];
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const 
    {
        out << "Spellchecker Statistics" << std::endl;
        for (auto i = 0u; i < MAXSIZE; ++i) {
            out << std::setw(15) << std::right << m_badWords[i] << ": " << m_replacementCount[i] << " replacements" << std::left << std::endl;
        }
    }
}