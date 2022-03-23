/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 20, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <vector>
#include <list>

namespace sdds {
	struct Covid {
		std::string m_country;
		std::string m_city;
		std::string m_variant;
		int m_cases;
		int m_year;
		int m_deaths;
	};

	class CovidCollection {
		std::vector<Covid> m_covidDetails{};

		// Start of Private Helpers

		const char* WHITESPACES = " \n\t";

		std::string& trimLeft(std::string& stringToTrim)
		{
			return stringToTrim.erase(0, stringToTrim.find_first_not_of(this->WHITESPACES));
		}
		std::string& trimRight(std::string& stringToTrim)
		{
			return stringToTrim.erase(stringToTrim.find_last_not_of(this->WHITESPACES) + 1);
		}
		std::string& trim(std::string& stringToTrim)
		{
			return trimLeft(trimRight(stringToTrim));
		}

		// End of Private Helpers

	public:
		CovidCollection(std::string fileName);
		void display(std::ostream& out) const;

		// part 2
		void sort(std::string sortBy);
		void cleanList();
		bool inCollection(std::string variantName) const;
		std::list<Covid> getListForCountry(std::string countryName) const;
		std::list<Covid> getListForVariant(std::string variantName) const;

	};

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
};

#endif // !SDDS_COVIDCOLLECTION_H