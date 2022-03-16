/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include"Directory.h"

namespace sdds {
	class Filesystem {
	private:
		// a pointer to the root directory of the filesystem.
		Directory* m_root{};

		// a pointer to the current working directory in the filesystem from where operations are performed.
		Directory* m_current{};

		const char* WHITESPACES = " \n\t";

		// Remove all leading whitespace characters from string
		std::string& trimLeft(std::string& stringToTrim);

		// Remove all trailing whitespace characters from string
		std::string& trimRight(std::string& stringToTrim);

		// Remove all leading and trailing whitespace characters from string
		std::string& trim(std::string& stringToTrim);

		void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
	public:
		// a custom constructor that receives the name of a file as its first argument, and an optional string containing the name of the root directory (defaults to an empty string).
		Filesystem(std::string fileName, std::string rootDirName = "");

		// adds a resource to the current directory.
		Filesystem& operator+=(Resource*);

		// changes the current directory to the directory (located in the current directory) whose name matches argument.
		Directory* change_directory(const std::string& = "");

		// a query that returns the current directory.
		Directory* get_current_directory() const {
			return m_current;
		}

		// a destructor that deallocates memory for the root directory.
		virtual ~Filesystem();

		// this class should not allow copy operations./

		// disable copy constructor
		Filesystem(const Filesystem&) = delete;

		// // disable copy assignment operator
		Filesystem& operator=(const Filesystem&) = delete;

		// this module supports move operations.
		Filesystem(Filesystem&&) noexcept;

		Filesystem& operator=(Filesystem&&) noexcept;
	};
};

#endif // !SDDS_FILESYSTEM_H