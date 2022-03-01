/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 26, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iomanip>

#include"Job.h"


namespace sdds {
	// a default constructor that sets the job to an empty, inactive state.
	Job::Job() {
		m_active = false;
	}

	// a custom constructor that receives the title of the job.
	// For simplicity, the number of units of work to be done to finish the job is equal to the remainder from dividing the number of characters in the title by 10 and adding 1.
	Job::Job(const std::string title) {
		m_title = title;

		// longer version

		//std::div_t dv{}; // can get remainder and quotient

		//std::size_t noOfChar = title.length();

		//dv = std::div(noOfChar, 10);

		//m_unitsToFinish = dv.rem + 1; // .rem returns the remainder

		m_pendingUnitsToFinish = m_unitsToFinish = (title.length() % 10) + 1;

		m_active = true;
	}

	// a query that returns whether the job is active or not.
	bool Job::is_active() const {
		return m_active;
	}

	// a query that returns whether the job is complete or not (no remaining units of work).
	bool Job::is_complete() const {
		return m_pendingUnitsToFinish == 0;
	}

	// a query that returns a copy of the title of the job.
	std::string Job::name() const {
		return m_title;
	}

	//  inserts the job details into the output stream (received as an argument) and returns nothing.
	// The output should be displayed in the following format:
	// `JOB NAME` [XX/XX remaining]
	void Job::display(std::ostream& os) const {
		os << "`" << m_title << "` ";
		os << "[" << std::setw(2) << std::setfill('0') << m_pendingUnitsToFinish;
		os << "/" << std::setw(2) << std::setfill('0') << m_unitsToFinish;
		os << " remaining]";
	}

	// When called, this function takes the units of work handled (as a positive number) 
		// as its only argument and reduces the remaining work by it. 
	void Job::operator()(size_t unitsOfWorkHandled) {
		if (unitsOfWorkHandled > m_unitsToFinish ) {
			m_pendingUnitsToFinish = 0;
			throw std::underflow_error("Job queue is full");
		}
		else {
			m_pendingUnitsToFinish -= unitsOfWorkHandled;

			if (m_pendingUnitsToFinish <= 0) {
				m_pendingUnitsToFinish = 0;
			}
		}

	}

	// displays the job details.
	std::ostream& operator<<(std::ostream& os, Job& job) {
		job.display(os);
		return os;
	}
} 