/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include"File.h"
#include"Resource.h"

namespace sdds {
	File::File(std::string fileName, std::string fileContents) : Resource() {
		// a custom constructor that receives two strings as parameters :
		// the name of the file
		// a text representation of the contents of a file(optional, with empty string as a default value).
		this->m_contents = fileContents;
		this->m_name = fileName;
	}

	void File::update_parent_path(const std::string& parentPath) {
		this->m_parent_path = parentPath;
	}
}