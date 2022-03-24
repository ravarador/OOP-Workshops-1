/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 23, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;

		// TODO: Add your code here to build a list of employees
		//         using raw pointers
		for (size_t i = 0; i < emp.size(); i++) {
			for (size_t y = 0; y < sal.size(); y++) {
				// For each active employee found in both lists, dynamically create a new object of type EmployeeWage
				if (emp[i].id == sal[y].id) {
					if (emp.isSINValid(emp[i].id)) {
						EmployeeWage* empWage = new EmployeeWage(emp[i].name, sal[y].salary);

						try {
							empWage->rangeValidator();
							activeEmp += empWage;
							delete empWage;
						}
						catch (std::string msg) {
							delete empWage;
							throw std::string(msg);
						}
						
					}
				}
			}
		}

		return activeEmp;
	}

	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees
		//         using smart pointers
		for (size_t i = 0; i < emp.size(); i++) {
			for (size_t y = 0; y < sal.size(); y++) {
				// For each active employee found in both lists, dynamically create a new object of type EmployeeWage
				if (emp[i].id == sal[y].id) {
					if (emp.isSINValid(emp[i].id)) {
						std::unique_ptr<EmployeeWage> empWage(new EmployeeWage(emp[i].name, sal[y].salary));

						empWage->rangeValidator();
						activeEmp += std::move(empWage);

					}
				}
			}
		}

		return activeEmp;
	}
}