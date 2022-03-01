/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: February 26, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Processor.h"

using namespace std;

namespace sdds {

	void Processor::set(std::string host, std::string brand, std::string code, size_t power) {
		m_host = host;
		m_brand = brand;
		m_code = code;
		m_power = power;
	}

	std::ostream& operator<<(std::ostream& os, Processor& obj) {
		obj.display(os);
		return os;
	}

	Processor::Processor(std::string host, std::string brand, std::string code, size_t power) {
		set(host, brand, code, power);
	}

	void Processor::run() {
		if (m_current != nullptr) {
			try
			{
				// if a job has been assigned to this processor first check if it has been completed
				if (m_current->is_complete())
				{
					cout << "[COMPLETE] " 
						<< *m_current 
						<< " using (" << m_power << ") " 
						<< m_brand 
						<< " " 
						<< m_code 
						<< endl;

					// it if has then it can be cleared and removed from this processor.
					delete m_current;
					m_current = nullptr;
				}
				else {
					// If it is incomplete then perform m_power units of work on the job assigned to this processor. 
					Job& j = *m_current;
					j(m_power);

					if (m_current->is_complete())
					{
						cout << "[COMPLETE] " 
							<< *m_current 
							<< " using (" << m_power << ") " 
							<< m_brand 
							<< " " 
							<< m_code 
							<< endl;

						// then clearing and removing the job assigned to this processor
						delete m_current;
						m_current = nullptr;
					}
				}

			}
			catch (const exception& ex) {
				cout << "Failed to complete job " << m_current->name() << endl;

				delete m_current;
				m_current = nullptr;
			}
		}
		
	}

	Processor::operator bool() const {
		return m_current != nullptr;
	}

	Processor& Processor::operator+=(Job*& job) {
		m_current = m_current == nullptr ? job : throw;

		return *this;
	}

	Job* Processor::get_current_job() const {
		return m_current;
	}

	void Processor::display(std::ostream& os)
	{
		os << "(" << m_power << ") " 
			<< m_brand 
			<< " " 
			<< m_code;

		if (m_current != nullptr) {
			os << " processing " << *m_current;
		}
	}

	Processor::Processor(CentralUnit<sdds::Processor>* cpu, std::string brand, std::string code, size_t power) {
		set("Process", brand, code, power);
	}
}