/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 13, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_TOY_H
#define SDDS_TOY_H

#include <string>

namespace sdds {
	typedef unsigned int u_int;
	typedef const unsigned int c_u_int;

	class Toy {
	private:
		
		// order id the order id of the toy (a positive number)
		u_int m_orderId{};

		// the name the name of the toy
		std::string m_name{};

		// the number of items the number of toys of this type to be ordered
		u_int m_noOfOrder{};

		// the price the price of this toy
		double m_price{};

		// the harmonized sales tax assume the HST is equal to 13%
		const double hst = .13;

		// used by trim function
		const char* whitespaces = " \n\t";

		// private setter function
		void set(c_u_int orderId, const std::string name, c_u_int noOfOrder, const double price);

		// trim functions

		// Remove all leading whitespace characters from string
		std::string& trimLeft(std::string& stringToTrim);

		// Remove all trailing whitespace characters from string
		std::string& trimRight(std::string& stringToTrim);

		// Remove all leading and trailing whitespace characters from string
		std::string& trim(std::string& stringToTrim);

	public:
		// Rule of 5 for copying and moving
		// Commented out because I realized that rule of 5 is not needed for this class

		Toy();
		/*Toy& operator=(const Toy& obj);*/
		~Toy();
		/*Toy(Toy&& obj) noexcept;
		Toy& operator=(Toy&& src) noexcept;*/

		// a modifier that receives as a parameter the number of toys of this type to be ordered and updates the number of items attribute with the received value. 
		// Assume the parameter is correct and doesn't require validation.
		void update(int numItems);

		// A constructor that receives the toy attributes as a string; 
		// this constructor is responsible for extracting information about the toy from the string and storing the tokens in the instance's attributes.
		// The string will always have the following format:
		// ID:NAME:NUM:PRICE
		// This constructor should remove all leading and trailing spaces from the beginning and end of any token extracted from the string.
		Toy(const std::string& toy);

		std::ostream& display(std::ostream& os)const;

		u_int getNoOfOrders()const;
	};

	// overload the insertion operator to insert the contents of a toy object into an ostream object :
	std::ostream& operator<<(std::ostream& os, const Toy& toy);
}

#endif