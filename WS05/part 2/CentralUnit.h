/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 26, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CENTRALUNIT_H
#define SDDS_CENTRALUNIT_H

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iomanip>
#include <fstream>

#include "Job.h"

// Not a good practice? Hmmm. 
// TODO : Implement std without using namespace std
using namespace std;

namespace sdds {

	const size_t MAX_JOB_COUNT = 4;

	template <typename T>
	class CentralUnit {
		std::string m_type{};
		T** m_items{}; 
		Job* m_jobs[MAX_JOB_COUNT]{};
		size_t m_size{}; 
		size_t m_count{};

	public:
		// a class member that stores a reference to an output stream that will be used for logging information. Defaults to std::cout
		std::ostream& log = std::cout;

		CentralUnit();

		// custom constructor that receives the type of work handled by the central unit as its first argument and 
		// a C-style null-terminated string holding the name of a file that will initialize this object as its second argument. 
		CentralUnit(std::string, std::string);

		// takes the name of a job as an argument, creates a new Job object that is added to the job queue, and returns a reference to the current central unit. 
		// If the queue is full, report an error of type std::string.
		CentralUnit<T>& operator+=(std::string);

		// receives the address of a unit (takes ownership) 
		CentralUnit<T>& operator+=(T*);

		// Part 2 : Update the run() function to run the unit by using it as a functor
		void run();

		// a query that returns if there are any jobs assigned to its units or waiting to be assigned to a unit. 
		// This query does not change the state of the central unit.
		bool has_jobs() const;

		size_t get_available_units() const;

		// a query that receives the title of a job as a C-style null-terminated string and 
		// returns a pointer to the unit that is currently assigned a job that matches the given title. 
		T* operator[](string);

		// a query that receives and returns nothing and displays the central unit's current state.
		void display();

		// This design does not support copy operations -- 
		// if creating a new instance from a copy, report an exception, and assigning a copy of a CentralUnit should result in a compile-time error
		CentralUnit(const CentralUnit&);

		// Error, must support move operators
		// TODO: Move 
		// MOVE

		CentralUnit(CentralUnit<T>&&);
		CentralUnit<T>& operator=(const CentralUnit<T>&&);

		~CentralUnit() {
			for (size_t i = 0; i < m_size; i++) {
				delete m_items[i];
			}

			delete[] m_items;
		}
	};

	template<typename T>
	T* sdds::CentralUnit<T>::operator[](string jobName)
	{

		for (size_t i = 0; i < m_size; i++)
		{
			if (m_items[i]->get_current_job() != nullptr)
			{
				string currentJobName = m_items[i]->get_current_job()->name();

				if (currentJobName == jobName) {
					return m_items[i];
				}
			}
		}

		throw std::out_of_range("Job is not being handled by a unit.");
	}

	template<typename T>
	void sdds::CentralUnit<T>::display() {

		cout << "Central Processing Unit list\n";

		for (size_t i = 0; i < m_size; i++) {
			cout << "[" 
				<< std::setfill('0') << std::setw(4) << i + 1 
				<< "] " << *m_items[i] << endl;
		}

	}

	template<typename T>
	CentralUnit<T>::CentralUnit(std::string type, std::string name) {
		std::ifstream file;
		file.open(name);

		// UNIT_TYPE | UNIT_NAME | WORK_CAPACITY

		std::string unit_type;
		std::string unit_name;
		std::string work_capacity;

		if (file.is_open()) {
			m_items = new T * [7];
			m_type = type;

			while (!file.eof()) {

				char ch;
				// Create a store the individual units based on each line

				// Unit type
				file >> unit_type;
				file >> ch;

				// Unit name
				file >> unit_name;
				file >> ch;

				// Work capacity
				getline(file, work_capacity, '\n');

				size_t temp_work_capacity = 1;

				// Capture and handle this error by defaulting to a work capacity of 1.
				try
				{
					temp_work_capacity = std::stoi(work_capacity);
				}
				catch (...)
				{
					
				}

				m_items[m_size++] = new T(type, unit_type, unit_name, temp_work_capacity);
			}
		}
		else {
			// If the file cannot be opened, report an std::invalid_argument error with the messsage File cannot be opened.
			throw std::invalid_argument("File cannot be opened.");
		}
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(std::string jobName) {
		if (m_count >= MAX_JOB_COUNT) {
			// If the queue is full, report an error of type std::string
			std::string badGuy = "will cause error";
			throw std::stoi(badGuy);
		}
		else
		{
			// takes the name of a job as an argument, creates a new Job object that is added to the job queue, 
			m_jobs[m_count++] = new Job(jobName);
		}

		// returns a reference to the current central unit. 
		return *this;
	}

	template<typename T>
	void sdds::CentralUnit<T>::run() {
		// runs a cycle for each individual unit
		for (size_t i = 0; i < m_size; i++) {
			if (m_count > 0 && m_count <= MAX_JOB_COUNT) {
				// Goes through every unit and runs it once
				// While going through every unit, if there are jobs queued up and a unit is available (has no job assigned)
				if (*m_items[i])
				{
					
				}
				else {
					// remove the last job from the queue and assign it to the unit before running the unit.
					*m_items[i] += m_jobs[--m_count];
				}
			}

			bool currentJobNotNull = m_items[i]->get_current_job() != nullptr ? 1 : 0;

			m_items[i]->run();

			if (m_items[i]->get_current_job() == nullptr && currentJobNotNull) {
				size_t unitsAvail = 0;

				for (size_t i = 0; i < m_size; i++) {
					if (m_items[i]->get_current_job() == nullptr) {
						unitsAvail++;
					}
				}

				cout << unitsAvail << " units available.\n";
			}

		}

	}

	template<typename T>
	bool CentralUnit<T>::has_jobs() const {
		// returns if there are any jobs assigned to its units or waiting to be assigned to a unit
		for (size_t i = 0; i < m_size; i++) {
			if (m_items[i]->get_current_job() != nullptr) {
				return 1;
			}
		}

		return 0;
	}

	template<typename T>
	size_t CentralUnit<T>::get_available_units() const {
		size_t availableUnits = 0;
		for (size_t i = 0; i < m_size; i++) {
			// returns the number of units without jobs assigned to them.
			if (m_items[i]->get_current_job() == nullptr) {
				availableUnits++;
			}
		}

		return availableUnits;
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(const CentralUnit<T>& src) {
		// if creating a new instance from a copy, report an exception, and assigning a copy of a CentralUnit should result in a compile-time error.
		throw std::exception();
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(T* processor)
	{
		m_items[m_size++] = processor;

		return *this;
	}

	// MOVE

	template<typename T>
	CentralUnit<T>::CentralUnit(CentralUnit<T>&& src) {
		*this = std::move(src);
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator=(const CentralUnit<T>&& src) {
		if (this != &src) {
			m_type = src.m_type;
			src.m_type = nullptr;
			

			m_jobs = src.m_jobs;
			src.m_jobs = nullptr;

			m_size = src.m_size;
			src.m_size = nullptr;

			m_count = src.m_count;
			src.m_count = nullptr;

			for (size_t i = 0; i < m_size; i++) {
				delete m_items[i];
			}

			delete[] m_items;
			m_items = src.m_items;
			src.m_items = nullptr;
		}

		return *this;
	}

}
#endif // !SDDS_CENTRALUNIT_H
