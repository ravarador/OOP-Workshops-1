/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 03, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#pragma once
#include <iostream>
#include <string>
#include <iomanip>

namespace sdds {
	class Pair {
		std::string m_key{};
		std::string m_value{};

	public:
		const std::string& getKey() const {
			return m_key;
		}

		const std::string& getValue() const {
			return m_value;
		}

		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value } {};

		// Default constructor
		// Initiliaze members to default value
		Pair() : m_key{}, m_value{} {};

		// TODO: Add here the missing the prototypes for the members
		//           that are necessary if this class is to be used
		//           with the template classes described below.
		//       Implement them in the Pair.cpp file.

		virtual std::ostream& display(std::ostream& os = std::cout) const;

		// Used in part 2 to check if value is equal
		bool operator==(const Pair& pair) const;
	};

	std::ostream& operator<<(std::ostream& os, const Pair& pair);
}