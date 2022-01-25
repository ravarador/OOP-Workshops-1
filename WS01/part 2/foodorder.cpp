/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: January 19, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

#include "foodorder.h"

using namespace std;

double g_taxrate;
double g_dailydiscount;

namespace sdds {
	static int counter = 0;

	void FoodOrder::set(const char* custName, const char* foodDesc, const double foodPrice, const char isDailySpecial) {
		strcpy(m_custName, custName);

		m_foodDesc = new char[strlen(foodDesc) + 1];
		strcpy(m_foodDesc, foodDesc);

		m_foodPrice = foodPrice;
		m_isDailySpecial = isDailySpecial == 'Y' ? true : false;
	}

	void FoodOrder::setEmpty() {
		m_foodDesc = nullptr;
		m_custName[0] = '\0';
		m_foodPrice = -1;
		m_isDailySpecial = false;
	}

	double FoodOrder::computeTax(double price, double tax) {
		return price + (price * tax);
	}

	double FoodOrder::computeDiscount(double price, double discount) {
		return price - discount;
	}

	bool FoodOrder::isCustomerEmpty() {
		return m_custName[0] == '\0';
	}

	FoodOrder::FoodOrder() {
		setEmpty();
	};


	FoodOrder::~FoodOrder() {
		if (m_foodDesc != nullptr)
			delete[] m_foodDesc;
	};

	void FoodOrder::read(istream& istr) {
		setEmpty();

		char custName[10];
		istr.get(custName, 10, ',');

		istr.ignore();

		string foodDesc;
		getline(istr, foodDesc, ',');

		double foodPrice = -1;
		istr >> foodPrice;

		istr.ignore();

		char dailySpecialStatus;
		istr >> dailySpecialStatus;

		if (!istr.fail()) {
			// all data were read successfully, use the set private function to set values of the object to read value
			this->set(custName, foodDesc.c_str(), foodPrice, dailySpecialStatus);
		}
	}

	void FoodOrder::display() {
		if (isCustomerEmpty()) {
			cout << left << setw(2) << ++counter
				<< ". "
				<< "No Order"
				<< endl;
		}
		else {
			double taxedFoodPrice = computeTax(m_foodPrice, g_taxrate);
			double discountedTaxedFoodPrice = computeDiscount(taxedFoodPrice, g_dailydiscount);

			cout << left << setw(2) << ++counter
				<< ". "
				<< left << setw(10) << m_custName
				<< "|"
				<< left << setw(25) << m_foodDesc
				<< "|"
				<< left << setw(12) << fixed << setprecision(2) << taxedFoodPrice
				<< "|";

			if (m_isDailySpecial)
				cout << right << setw(13) << discountedTaxedFoodPrice;

			cout << endl;
		}
	}
}