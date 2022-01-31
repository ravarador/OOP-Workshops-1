/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: 27/01/2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <fstream>
#include <iostream>

/*
	Member variables:
		string *m_strings;
		int noOfString;
*/
#include"ProteinDatabase.h"

using namespace std;

namespace sdds {
	ProteinDatabase::ProteinDatabase() {

	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& obj) {
		if (obj.m_strings != nullptr) {
			this->m_strings = new string[obj.m_noOfStrings];
				
			unsigned int i;
			for (i = 0; i < obj.m_noOfStrings; i++) {
				this->m_strings[i] = obj.m_strings[i];
			}

			this->m_noOfStrings = obj.m_noOfStrings;
		}
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& obj) {
		if (this != &obj) {
			this->m_strings = new string[obj.m_noOfStrings];

			unsigned int i;
			for (i = 0; i < obj.m_noOfStrings; i++) {
				this->m_strings[i] = obj.m_strings[i];
			}

			this->m_noOfStrings = obj.m_noOfStrings;
		}

		return (*this);
	}

	ProteinDatabase::~ProteinDatabase() {
		delete[] m_strings;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) noexcept {
		*this = std::move(src);
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) noexcept {
		if (this != &src) {
			delete this->m_strings;
			this->m_strings = src.m_strings;
			src.m_strings = nullptr;

			this->m_noOfStrings = src.m_noOfStrings;
			src.m_noOfStrings = 0;

		}

		return (*this);
	}

	ProteinDatabase::ProteinDatabase(const char* fileName) {
		string line;

		std::ifstream f(fileName);

		// i. reads the file to count the number of protein sequence present in the file.
		unsigned int proteinCount = 0;
		if (f.is_open()) {
			while (getline(f, line))
			{
				if (line[0] == '>')
					proteinCount++;
			}

			m_noOfStrings = proteinCount;
			f.close();
		}

		// ii. allocates memory for that number of protein sequences in the array
		m_strings = new string[m_noOfStrings + 1];

		// iii. re-reads the file and loads the protein sequences (i.e., string of characters not sequence names) into the array.
		proteinCount = 0;
		f.open(fileName);
		if (f.is_open()) {
			while (getline(f, line) && proteinCount < m_noOfStrings)
			{
				if (line[0] != '>') {
					m_strings[proteinCount] += line;
				}

				if (line[0] == '>' && !m_strings[proteinCount].empty()) {
					proteinCount++;
				}
			}

			f.close();
		}
	}

	std::size_t ProteinDatabase::size() { 
		return m_noOfStrings; 
	}

	std::string ProteinDatabase::operator[](size_t i) {
		if (i > m_noOfStrings - 1 || i < 0 || m_noOfStrings == 0) {
			// Invalid index
			return "";
		}

		return m_strings[i];
	}
}