/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include"Resource.h"
#include"Flags.h"

namespace sdds {
	class File : public sdds::Resource {
	private:
		std::string m_contents;

	public:
		// a custom constructor that receives two strings as parameters :
		// the name of the file
		// a text representation of the contents of a file(optional, with empty string as a default value).
		File(std::string fileName, std::string fileContents = "");

		// sets the parent path to the parameter.
		void update_parent_path(const std::string&);

		// a query that returns Flags::FILE.
		NodeType type() const {
			return sdds::NodeType::FILE;
		}

		// a query that returns the full absolute path of the file (concatenates the absolute path location and the file name).
		std::string path() const {
			return Resource::m_parent_path + Resource::m_name;
		}

		// a query that returns the name of the file.
		std::string name() const {
			return Resource::m_name;
		}

		// a query that returns -1.
		int count() const {
			return -1;
		}

		// a query that returns the size of the file in bytes. For simplicity, this is the number of characters in m_contents attribute.
		size_t size() const {
			return m_contents.length();
		}
	};
}

#endif // !SDDS_FILE_H