/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 03, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include"Pair.h"

using namespace std;

namespace sdds {

	ostream& Pair::display(ostream& os)const {
		// Sample output
		//        static memory: memory allocated during the compilation time
		//          programmer: a person who writes code
		//      dynamic memory: memory allocated during the runtime
		//   client of a class: a piece of code that uses the class
		//      dynamic memory: memory allocated with 'new' operator

		os << right << setw(20) << getKey();
		os << ": ";
		os << left << getValue();

		return os;
	}

	bool Pair::operator==(const Pair& pair) const {
		return m_key == pair.getKey();
	}

	std::ostream& operator<<(std::ostream& os, const Pair& pair) {
		return pair.display(os);
	}
};