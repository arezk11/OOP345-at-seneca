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
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>
#include <string>


namespace sdds
{
	class Book
	{
		std::string m_author = "";
		std::string m_title = "";
		std::string m_country = "";
		size_t m_year = 0;
		double m_price = 0.0;
		std::string m_description = "";

	public:
		Book() {}
		Book(const std::string& strBook);
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();

		template <typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_description);
		}

		friend std::ostream& operator<<(std::ostream& os, const Book& src);
	};
}

#endif // !SDDS_BOOK_H