/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 13, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "ConfirmOrder.h"
#include<iostream>

using namespace std;

namespace sdds {
	// IMPLEMENT RULE OF 5

	ConfirmOrder::ConfirmOrder() {
		
	}

	ConfirmOrder::~ConfirmOrder() {
		//delete m_toys;
		delete[] m_toys;
		
	}

	// COPYING

	ConfirmOrder::ConfirmOrder(const ConfirmOrder& src) {
		*this = src; // call operator=
	}

	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src) {
		/*if (this != &obj) {
			this->m_strings = new string[obj.m_noOfStrings];

			unsigned int i;
			for (i = 0; i < obj.m_noOfStrings; i++) {
				this->m_strings[i] = obj.m_strings[i];
			}

			this->m_noOfStrings = obj.m_noOfStrings;
		}

		return (*this);*/

		if (this != &src) {
			// deallocate m_toys
			delete[] this->m_toys;
			// delete this->m_toys;

			// then set it to fresh array pointer of Toy
			this->m_toys = new const Toy * [src.size];

			// iterate to copy data from src.m_toys
			for (u_int i = 0; i < src.size; i++) {
				this->m_toys[i] = src.m_toys[i];
			}

			this->size = src.size;
		}
		return (*this);
	}

	// MOVING

	ConfirmOrder::ConfirmOrder(ConfirmOrder&& src) noexcept {
		*this = move(src);
	}

	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src) noexcept {
		/*if (this != &src) {
			delete this->m_strings;
			this->m_strings = src.m_strings;
			src.m_strings = nullptr;

			this->m_noOfStrings = src.m_noOfStrings;
			src.m_noOfStrings = 0;

		}

		return (*this);*/


		// rule in moving:
		// after copying the value from src,
		// always set to default value or nullptr

		if (this != &src) {
			delete[] m_toys;

			m_toys = src.m_toys;

			/*for (u_int i = 0; i < src.size; i++) {
				this->m_toys[i] = src.m_toys[i];
				src.m_toys[i] = nullptr;
			}*/

			src.m_toys = nullptr;

			size = src.size;
			src.size = 0;
		}

		return (*this);
	}

	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
		bool toyExists = false;

		for (u_int i = 0; i < size; i++) {
			// if the address of toy is already in the array, this operator does nothing
			toyExists = &toy == m_toys[i];
		}

		if (!toyExists) {
			// resizes the array to make room for toy if necessary
			
			// create a temp array with a +1 size to store the new Toy
			const Toy** tempArray = new const Toy * [size + 1];

			for (u_int i = 0; i < size; i++) {
				// stores the address of toy in the array (your function should not make copies of the toy itself)
				tempArray[i] = m_toys[i];
			}

			delete[] m_toys;
			m_toys = tempArray;

			// stores the new toy
			tempArray[size] = &toy;
			size++;
		}
		return (*this);
	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
		// if the address of toy is not in the array, this operator does nothing
		
		// iterate all toys and check for if toy exists
		for (u_int i = 0; i < toy.getNoOfOrders(); i++) {

			// searches the array for the address of toy
			if (&toy == m_toys[i]) {
				//  sets the pointer in the array to nullptr if toy is found
				m_toys[i] = nullptr;

				// since a toy is deleted, reduce size by one
				size--;

				// TODO: Reduce size of array 
				// Psuedo: 
				// Create temp array with one less size
				// Delete m_toys
				// Instantiate m_toys with one less size
				// m_toys = temp array
			}
		}

		return (*this);
	}

	ostream& ConfirmOrder::display(ostream& os) const {
		// if there are no toys to confirm: OR size = 0
		/*
		--------------------------
		Confirmations to Send
		--------------------------
		There are no confirmations to send!
		--------------------------
		*/

		// if there are toys to confirm OR size > 0
		/*
		--------------------------
		Confirmations to Send
		--------------------------
		TOY
		TOY
		...
		--------------------------
		*/
		os << "--------------------------" << endl;
		os << "Confirmations to Send" << endl;
		os << "--------------------------" << endl;

		if (size) { // true if size is more than 0
			for (u_int i = 0; i < size; i++) {
				m_toys[i]->display(cout);
			}
		}
		else {
			os << "There are no confirmations to send!" << endl;
		}

		os << "--------------------------" << endl;
		
		return os;
	}

	ostream& operator<<(ostream& os, const ConfirmOrder& obj) {
		return obj.display(os);
	}
}