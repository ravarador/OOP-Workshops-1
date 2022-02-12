/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 03, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <string>

#include "Pair.h"

// using namespace std; // Adding this results to ambigious issue. Why?

namespace sdds {

	template<class T, size_t CAPACITY>
	class Collection {
	protected: // will also work on public but protected is much safer, i guess
		size_t m_noOfElements{};
		T m_dummy{};
		T m_array[CAPACITY];

	public:
		Collection() {};

		virtual ~Collection() {};

		// a query that returns the current number of elements in the collection
		size_t size() const {
			return m_noOfElements;
		}

		// a query that receives as the parameter an output stream (with default value std::cout) 
		void display(std::ostream& ostr = std::cout)const {
			/* Sample output
			----------------------
			| Collection Content |
			----------------------
			16
			12
			*/

			ostr << "----------------------" << std::endl;
			ostr << "|" << " Collection Content " << "|" << std::endl;
			ostr << "----------------------" << std::endl;

			// inserts into the stream all items from the collection
			for (unsigned int i = 0; i < m_noOfElements; i++) {
				ostr << m_array[i] << std::endl;
			}
			ostr << "----------------------" << std::endl;
		}

		// a mutator that adds a copy of the parameter to the collection if there still is capacity.
		// If the item has been added, this function return true; false otherwise.
		virtual bool add(const T& item) {
			bool isAdded = false;

			if (m_noOfElements < CAPACITY) {
				m_array[m_noOfElements] = item;
				m_noOfElements++;
				isAdded = true;
			}

			return isAdded;
		}

		// a query that receives an index as parameter
		T& operator[](unsigned int index) {
			// returns a copy of the element stored in the collection at the specified index.
			// If the index is not valid (outside the boundaries of the collection), this query returns the dummy object.
			return index >= 0 && index < m_noOfElements ? m_array[index] : m_dummy;
		}
	};

	// Specialize the dummy object when type T = Pair and CAPACITY = 100 so the key is "No Key" and the value is "No Value".
	template<>
	Collection<Pair, 100>::Collection() {
		Pair a("No Key", "No Value");
		m_dummy = a;

	};
}

#endif