/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: 27/01/2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_PROTEINDATABASE_H
#define SDDS_PROTEINDATABASE_H 

#include<string>

namespace sdds {

	class ProteinDatabase {
		std::string *m_strings{};
		unsigned int m_noOfStrings = 0;

	public:
		ProteinDatabase();

		// RULE OF FIVE : Copy Constructor, User Defined Copy Assignment Operator, Destructor, Move Constructor, Move Operator
		ProteinDatabase(const ProteinDatabase& obj);
		ProteinDatabase& operator=(const ProteinDatabase& obj);
		~ProteinDatabase();
		ProteinDatabase(ProteinDatabase&& obj) noexcept;
		ProteinDatabase& operator=(ProteinDatabase&& src) noexcept;



		ProteinDatabase(const char* fileName);

		std::size_t size();

		std::string operator[](size_t);
	};
}

#endif