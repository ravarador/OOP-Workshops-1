/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: 27/01/2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

/*
	Member variables:
		m_noOfRecords
		m_startTime
		m_endTime
*/
#include"TimedTask.h"
#include<chrono>
#include<string>
#include<iostream>
#include<iomanip>

using namespace std::chrono;

namespace sdds {
	TimedTask::TimedTask() {
	}

	void TimedTask::startClock() {
		m_startTime = steady_clock::now();
	}

	void TimedTask::stopClock() {
		m_endTime = steady_clock::now();
	}

	void TimedTask::addTask(const char* taskName) {
		// stores into the name attribute the C-style string received as parameter
		m_tasks[m_noOfRecords].name = std::string(taskName);

		// stores "nanoseconds" as the units of time
		m_tasks[m_noOfRecords].unitsOfTime = "nanoseconds";

		// calculates and stores the duration of the event (use std::chrono::duration_cast<std::chrono::nanoseconds>(), see documentation here)
		m_tasks[m_noOfRecords].duration = duration_cast<nanoseconds>(m_endTime - m_startTime);

		m_noOfRecords++;
	}

	std::ostream& operator<<(std::ostream& os, const TimedTask& obj) {
		os << "--------------------------" << std::endl;
		os << "Execution Times:" << std::endl;
		os << "--------------------------" << std::endl;

		// TASK_NAME DURATION UNITS
		// The name of the task should be in a field of size 21, aligned on the left; the duration should be in a field of size 13, aligned on the right.
		int i;
		for (i = 0; i < obj.m_noOfRecords; i++) {
			os << std::left << std::setw(21) << obj.m_tasks[i].name << std::right << std::setw(13) << obj.m_tasks[i].duration.count() << std::endl;
		}

		os << "--------------------------" << std::endl;

		return os;
	}
}