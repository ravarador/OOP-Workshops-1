/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 13, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H

#include "Toy.h"
#include <string>

namespace sdds {
	class Child {
	private:
		// An attribute of type const sdds::Toy** representing the dynamically allocated array of pointers
		const sdds::Toy** m_toys{};

		std::string m_childname;
		u_int m_age{};
		u_int m_noOfToys{};

		void set(std::string name, int age, const Toy* toys[], size_t count);
		
	public:
		// Rule of 5: Copying and Moving
		~Child();
		Child(const Child& src);
		Child& operator=(const Child& src);
		Child(Child&& srC) noexcept;
		Child& operator=(Child&& src) noexcept;

		Child(std::string name, int age, const Toy* toys[], size_t count);


		// a query that returns the number of toys stored in the array attribute.
		size_t size() const;

		std::ostream& display(std::ostream& os)const;
	};

	// overload the insertion operator to insert the content of a Child object into an ostream object.
	std::ostream& operator<<(std::ostream& os, Child& src);
}
#endif