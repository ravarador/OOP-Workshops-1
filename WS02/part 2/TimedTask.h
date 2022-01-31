/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: 27/01/2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_TIMEDTASK_H
#define SDDS_TIMEDTASK_H 
#include<chrono>
#include<string>
#include<iostream>

namespace sdds {
	class TimedTask {
		struct Task {
			std::string name;
			std::string unitsOfTime;
			std::chrono::steady_clock::duration duration;
		};

		int m_noOfRecords = 0;
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
		Task m_tasks[10]{};

		
	public:
		TimedTask();

		void startClock();
		void stopClock();
		void addTask(const char* taskName);

	friend std::ostream& operator<<(std::ostream& os, const TimedTask& obj);
	};


}

#endif