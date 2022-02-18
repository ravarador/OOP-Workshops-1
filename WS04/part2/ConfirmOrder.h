/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 13, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H

#include "Toy.h"

namespace sdds {
	class ConfirmOrder {
		// An attribute of type const sdds::Toy** representing the dynamically allocated array of pointers
		const Toy** m_toys{};

		// Add as many private members as your design requires
		// size of Toy array
		u_int size{};

	public:
		// Rule of 5: Copying and Moving

		ConfirmOrder();
		~ConfirmOrder();
		ConfirmOrder(const ConfirmOrder& src);
		ConfirmOrder& operator=(const ConfirmOrder& src);
		ConfirmOrder(ConfirmOrder&& srC) noexcept;
		ConfirmOrder& operator=(ConfirmOrder&& src) noexcept;

		// adds the toy toy to the array by adding its address.
		// if the address of toy is already in the array, this operator does nothing
		// resizes the array to make room for toy if necessary
		// stores the address of toy in the array(your function should not make copies of the toy itself)
		ConfirmOrder& operator+=(const Toy& toy);

		// removes the toy toy from the array by removing its address
		// if the address of toy is not in the array, this operator does nothing
		// searches the array for the address of toy, sets the pointer in the array to nullptr if toy is found.
		ConfirmOrder& operator-=(const Toy& toy);

		std::ostream& display(std::ostream& os) const;
	};

	// overload the insertion operator to insert the content of a ConfirmOrder object into an ostream object: 
	std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& C);
}

#endif 