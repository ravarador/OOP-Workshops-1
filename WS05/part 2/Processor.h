/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 26, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

#include <string>

#include "Job.h"
#include "CentralUnit.h"

namespace sdds {
	class Processor {
		// stores the address of the hosting central unit that specifically hosts processors.
		std::string m_host{};

		// stores the name of the brand of microprocessor, representing the unit type.
		std::string m_brand{};

		// stores a short text descriptor of the microprocessor, representing the unit name.
		std::string m_code{};

		// stores the number of work units that the microprocessor can process for a job in a single run, representing the unit's work capacity.
		size_t m_power{};

		// stores the address of the job currently assigned to the microprocessor to be processed.
		Job* m_current{}; 

		void set(std::string, std::string, std::string, size_t);
	public:
		// a custom constructor that takes the address of the hosting central unit, the brand, code, 
		// and power of the microprocessor as arguments and uses this data to initialize the processor.
		Processor(std::string, std::string, std::string, size_t);

		void run();

		// a true/false representation of the processor that returns true if a job is assigned to it, false otherwise.
		explicit operator bool() const;

		// assigns a job to the processor. Report an exception if there is a job already assigned.
		Processor& operator+=(Job*&);

		// a query that returns the job currently assigned to the processor.
		Job* get_current_job() const;

		// makes the processor available by unassigning the current job (do not clear any memory allocated for it) and returning the address of the job that was unassigned.
		//void free();

		// used with operator<< for display
		void display(std::ostream& ostr = std::cout);

		Processor(CentralUnit<sdds::Processor>*, std::string, std::string, size_t);
	};

	// inserts the details about this processor into the output stream in the following format: 
	// (POWER) BRAND CODE processing CURRENT_JOB_DETAILS
	std::ostream& operator<<(std::ostream&, Processor&);
}
#endif // !SDDS_PROCESSOR_H