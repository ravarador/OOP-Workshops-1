/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 13, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
	The trim function I learned from this stackoverflow question: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
*/

#include"Toy.h"
#include<iomanip>

using namespace std;

namespace sdds {
	// private setter function
	void Toy::set(c_u_int orderId, const std::string name, c_u_int noOfOrder, const double price) {
		if (orderId != 0) {
			m_orderId = orderId;
			m_name = name;
			m_noOfOrder = noOfOrder;
			m_price = price;
		}
		else {
			m_orderId = 0;
			m_noOfOrder = 0;
			m_price = 0;
		}
	}


	Toy::Toy() {
		
	}

	/*Toy& Toy::operator=(const Toy& obj) {
		if (this != &obj) {
			this->set(obj.m_orderId, obj.m_name, obj.m_noOfOrder, obj.m_price);
		}

		return (*this);
	}*/

	Toy::~Toy() {
		
	}

	/*Toy::Toy(Toy&& src) noexcept {
		*this = std::move(src);
	}

	Toy& Toy::operator=(Toy&& src) noexcept {
		if (this != &src) {
			this->set(src.m_orderId, src.m_name, src.m_noOfOrder, src.m_price);
			src.set(0, "", 0, 0);
		}

		return (*this);
	}*/

	std::string& Toy::trimLeft(std::string& stringToTrim) {
		return stringToTrim.erase(0, stringToTrim.find_first_not_of(this->whitespaces));
	}

	std::string& Toy::trimRight(std::string& stringToTrim) {
		return stringToTrim.erase(stringToTrim.find_last_not_of(this->whitespaces) + 1);
	}

	std::string& Toy::trim(std::string& stringToTrim) {
		return trimLeft(trimRight(stringToTrim));
	}

	void Toy::update(int numItems) {
		m_noOfOrder = numItems;
	}

	Toy::Toy(const std::string& toy) {
		// TODO: 
		// Pseudocode:
		// Extract tokens
		// Trim tokens
		// Set values

		//string tokens[4]{ {} };
		string temp = toy;
		string delimiter = ":";

		// Step 1: extract and store to tokens array

		u_int delimiterPos = 0;

		// SHORTER WAY DOESNT WORK DUE TO MEMORY LEAK - WILL TRY LONGER SOLUTION
		//u_int count = 0;
		//while ((delimiterPos = temp.find(delimiter)) != string::npos) {
		//	string token = temp.substr(0, delimiterPos);

		//	// Step 2: Trim whitespace characters in the tokens 
		//	tokens[count] = trim(token);
		//	
		//	temp.erase(0, delimiterPos + delimiter.length());

		//	count++;
		//}

		//if (!temp.empty()) {
		//	tokens[count] = temp;
		//	trim(tokens[count]);
		//}

		// LONGER SOLUTION:
		// Step 1: Find the index number of delimiter to be used on extracting the string to tokens
		// Step 2: Trim the token and store in temporary variable

		delimiterPos = temp.find(delimiter);
		string orderId = temp.substr(0, delimiterPos);
		trim(orderId);
		temp.erase(0, delimiterPos + delimiter.length());

		delimiterPos = temp.find(delimiter);
		string name = temp.substr(0, delimiterPos);
		trim(name);
		temp.erase(0, delimiterPos + delimiter.length());

		delimiterPos = temp.find(delimiter);
		string noOfOrder = temp.substr(0, delimiterPos);
		trim(noOfOrder);
		temp.erase(0, delimiterPos + delimiter.length());

		delimiterPos = temp.find(delimiter);
		string price = temp.substr(0, delimiterPos);
		trim(price);
		temp.erase(0, delimiterPos + delimiter.length());

		// Step 3: set the values
		this->set(
			stoi(orderId),		// order ID -> string to int
			name,				// toy name
			stoi(noOfOrder),	// order no -> string to int
			stod(price)			// toy price -> double to int
		);
	}

	std::ostream& Toy::display(std::ostream& os)const {
		// overload the insertion operator to insert the contents of a toy object into an ostream object :
		// The word Toy("Toy")
		os << "Toy";

		//	the ID of the toy should display on a field of size 8 followed by a colon(':')
		os << setw(8) << this->m_orderId << ":";

		//	The name of the toy should display on a field of size 18, aligned to the right
		os << setw(18) << right << this->m_name;

		//	The number of items should display on a field of size 3,
		os << setw(3) << this->m_noOfOrder;

		//	The word items preceded by a space(" items"),
		os << " items";

		//	The price of the toy should display on a field of size 8
		os << setw(8) << this->m_price;

		//	The words "/item subtotal:" should follow
		os << "/item  subtotal:";

		//	The subtotal should display on a field of size 7 (the price times the number of items)
		double subtotal = this->m_price * this->m_noOfOrder;
		os << setw(7) << subtotal;

		//	The word tax : should follow preceded by a space(" tax:")
		os << " tax:";

		//	The tax should display on a field of size 6 (the amount of tax paid on the subtotal)
		double tax = subtotal * this->hst;
		os << setw(6) << fixed << setprecision(2) << tax;

		//	The word total : should follow preceded by a space(" total:")
		os << " total:";

		//	The total should display on a field of size 7 (the subtotal plus the tax)
		double total = subtotal + tax;
		os << setw(7) << fixed << setprecision(2) << total;

		// ends here
		os << endl;

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Toy& toy) {
		return toy.display(os);
	}

	u_int Toy::getNoOfOrders()const {
		return m_noOfOrder;
	}
}