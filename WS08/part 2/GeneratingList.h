/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 23, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList() {}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const {
			return list.size();
		}
		const T& operator[](size_t i) const {
			return list[i];
		}

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
		bool isSINValid(const std::string SIN) const {
			
			// alternative algorithm:
			// computation = (sum(case1) + sum(case2)) % 10
			// if computation = 0 then SIN is valid
			// else SIN is invalid
			// 
			// case1 = sum of values from last index number going to first index in an interval of 2
			// example: 
			// 123456789
			// 9 -> is the value of last index number
			// 7 -> last index number - 2.. etc
			// case1 = 9 + 7 + 5 + 3 + 1
			//
			// case2 = sum of doubled values from 2nd to the last index number going to first index in an interval of 2
			// example:
			// 123456789
			// multiple the values from last index number going to first index in an interval of 2 by 0
			// 9 * 0, 7 * 0, 5 * 0, 3 * 0, 1 * 0
			// 020406080
			// multiply all remaining numbers by 2, if the number is double digit, add the digits
			// 2 * 2, 4 * 2, 6 * 2, 8 * 2
			// 4, 8, 12, 16
			// 12 -> 1 + 2 = 3
			// 16 -> 1 + 6 = 7
			// case2 = 4 + 8 + 3 + 7
			//

			// solution from: https://github.com/BudacaB/yt/blob/master/credit/credit.c

			std::string sinString = SIN;
			int sinNumber = std::stoi(sinString.c_str());
			int sum = 0;

			// case 1
			while (sinNumber > 0) {
				int lastDigit = sinNumber % 10;
				sum = sum + lastDigit;
				sinNumber = sinNumber / 100; // interval of 2
			}

			// case 2
			sinNumber = std::stoi(sinString.c_str()) / 10;
			while (sinNumber > 0) {
				int lastDigit = sinNumber % 10;
				int timesTwo = lastDigit * 2;
				sum = sum + (timesTwo % 10) + (timesTwo / 10);
				sinNumber = sinNumber / 100;
			}

			return (sum % 10 == 0);
		}

		//TODO: Overload the += operator with a smart pointer
		// as a second operand.
		void operator+=(std::unique_ptr<T> pointer) {
			list.push_back(std::move(*pointer));
		}

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		void operator+=(T* pointer) {
			if (pointer != nullptr) {
				list.push_back(*pointer);
			}
		}

		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
