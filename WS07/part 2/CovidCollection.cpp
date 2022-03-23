/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 20, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

#include"CovidCollection.h"

namespace sdds {
	CovidCollection::CovidCollection(std::string fileName)
	{
		auto trimmedToken = [&](std::string srcString, std::string& targetString, size_t firstPos, size_t len) {

			targetString = srcString.substr(firstPos, len);

			return trim(targetString);
		};

		Covid covid;

		std::ifstream file;
		file.open(fileName);

		if (file.is_open()) {
			while (file.peek() != EOF) {
				std::string file_content = {};
				std::string year;
				std::string cases;
				std::string deaths;

				getline(file, file_content, '\n');

				if (!file_content.empty()) 
				{
					trimmedToken(file_content, covid.m_country, 0, 25);
					trimmedToken(file_content, covid.m_city, 25, 25);
					trimmedToken(file_content, covid.m_variant, 50, 25);
					trimmedToken(file_content, year, 75, 5);
					trimmedToken(file_content, cases, 80, 5);
					trimmedToken(file_content, deaths, 85, 5);

					covid.m_year = stoi(year);
					covid.m_cases = stoi(cases);
					covid.m_deaths = stoi(deaths);

					m_covidDetails.push_back(covid);
				}
			}

			file.close();
		}
	}
	
	void CovidCollection::display(std::ostream& out) const
	{
		int cases = 0;
		int deaths = 0;

		std::for_each(m_covidDetails.begin(), m_covidDetails.end(), 
			[&](Covid covid) { 
				cases += covid.m_cases;
				deaths += covid.m_deaths;
				out << covid << std::endl; 
			});

		out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' '); // stole this from printbar function in w7_p2.cpp

		out << "|"
			<< std::right << std::setw(79) << "Total Cases Around the World: "
			<< std::setw(6) << cases << " |"
			<< "\n"
			<< "|"
			<< std::right << std::setw(79) << "Total Deaths Around the World: "
			<< std::right << std::setw(6) << deaths << " |"
			<< std::endl;
	}

	std::ostream& operator<<(std::ostream& out, const Covid& covid) {
		std::string year = "";

		if (covid.m_year > 0) {
			year = std::to_string(covid.m_year);
		}

		out << "| "
			<< std::left << std::setw(20 + 1) << covid.m_country // the +1 is weird. it should only be 20, but the +1 is there to match the output. 
			<< " | "
			<< std::left << std::setw(15) << covid.m_city
			<< " | "
			<< std::left << std::setw(20) << covid.m_variant
			<< " | "
			<< std::right << std::setw(6) << year
			<< " | "
			<< std::right << std::setw(4) << covid.m_cases
			<< " | "
			<< std::right << std::setw(3) << covid.m_deaths
			<< " |";

		return out;
	}

	// part 2 

	void CovidCollection::sort(std::string sortBy)
	{
		std::sort(m_covidDetails.begin(), m_covidDetails.end(),
			[sortBy](const Covid& left, const Covid& right) -> bool
			{
				if (sortBy == "country") {
					return left.m_country < right.m_country;
				}
				else if (sortBy == "variant") {
					return left.m_variant < right.m_variant;
				}
				else if (sortBy == "cases") {
					return left.m_cases < right.m_cases;
				}
				else if (sortBy == "deaths") {
					return left.m_deaths < right.m_deaths;
				}
				else {
					return false;
				}
			});


		/*if (sortBy == "country") {
			std::sort(m_covidDetails.begin(), m_covidDetails.end(),
				[](const Covid& left, const Covid& right) -> bool 
				{
					return left.m_country < right.m_country;
				});
		}
		else if (sortBy == "variant") {
			std::sort(m_covidDetails.begin(), m_covidDetails.end(),
				[](const Covid& left, const Covid& right) -> bool
				{
					return left.m_variant < right.m_variant;
				});
		}
		else if (sortBy == "cases") {
			std::sort(m_covidDetails.begin(), m_covidDetails.end(),
				[](const Covid& left, const Covid& right) -> bool
				{
					return left.m_cases < right.m_cases;
				});
		}
		else if (sortBy == "deaths") {
			std::sort(m_covidDetails.begin(), m_covidDetails.end(),
				[](const Covid& left, const Covid& right) -> bool
				{
					return left.m_deaths < right.m_deaths;
				});
		}*/
	}

	void CovidCollection::cleanList()
	{
		std::transform(m_covidDetails.begin(), m_covidDetails.end(), m_covidDetails.begin(),
			[](Covid& covid) 
			{ 
				if (covid.m_variant == "[None]") {
					covid.m_variant = "";
				}

				return covid; 
			});
	}

	bool CovidCollection::inCollection(std::string variant) const
	{
		return std::any_of(m_covidDetails.begin(), m_covidDetails.end(), [variant](Covid covid) {
			return covid.m_variant == variant;
			});
	}

	std::list<Covid> CovidCollection::getListForCountry(std::string countryName) const
	{
		std::list<Covid> tempCovids;

		std::copy_if(m_covidDetails.begin(), m_covidDetails.end(), std::back_inserter(tempCovids),
			[countryName](const Covid& covid) {
				return covid.m_country == countryName;
			});

		return tempCovids;
	}

	std::list<Covid> CovidCollection::getListForVariant(std::string variant) const
	{
		std::list<Covid> tempCovids;

		std::copy_if(m_covidDetails.begin(), m_covidDetails.end(), std::back_inserter(tempCovids),
			[variant](const Covid& covid) {
				return covid.m_variant == variant;
			});

		return tempCovids;
	}

}