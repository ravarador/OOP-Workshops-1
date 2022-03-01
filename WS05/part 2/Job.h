/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 26, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include<iostream>

namespace sdds {
	class Job {
		std::string m_title{};
		size_t m_unitsToFinish{};
		size_t m_pendingUnitsToFinish{};
		bool m_active = false;

	public:
		// a default constructor that sets the job to an empty, inactive state.
		Job();

		// a custom constructor that receives the title of the job.
		// For simplicity, the number of units of work to be done to finish the job is equal to the remainder from dividing the number of characters in the title by 10 and adding 1.
		Job(const std::string title);

		// a query that returns whether the job is active or not.
		bool is_active() const;

		// a query that returns whether the job is complete or not (no remaining units of work).
		bool is_complete() const;

		// a query that returns a copy of the title of the job.
		std::string name() const;

		//  inserts the job details into the output stream (received as an argument) and returns nothing.
		// The output should be displayed in the following format:
		// `JOB NAME` [XX/XX remaining]
		void display(std::ostream& os) const;

		// When called, this function takes the units of work handled (as a positive number) 
		// as its only argument and reduces the remaining work by it. 
		void operator()(size_t unitsOfWorkHandled);

		~Job() {};
	};

	// displays the job details.
	std::ostream& operator<<(std::ostream&, Job&);
}

#endif // !SDDS_JOB_H