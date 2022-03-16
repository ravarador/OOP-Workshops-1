/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <fstream>
#include <string>

#include"Filesystem.h"
#include"Directory.h"
#include"File.h"

namespace sdds {
	std::string& Filesystem::trimLeft(std::string& stringToTrim)
	{
		return stringToTrim.erase(0, stringToTrim.find_first_not_of(this->WHITESPACES));
	}
	std::string& Filesystem::trimRight(std::string& stringToTrim)
	{
		return stringToTrim.erase(stringToTrim.find_last_not_of(this->WHITESPACES) + 1);
	}
	std::string& Filesystem::trim(std::string& stringToTrim)
	{
		return trimLeft(trimRight(stringToTrim));
	}

	void Filesystem::tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
	{
		size_t start;
		size_t end = 0;

		if (str.find(delim) != std::string::npos) {
			while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
			{
				end = str.find(delim, start);
				out.push_back(str.substr(start, end - start + 1));
			}
		}
		else {
			out.push_back(str);
		}
	}

	Filesystem::Filesystem(std::string fileName, std::string rootDirName)
	{
		bool isDirectory = false;

		// TODO : Filesystem custom constructor
		std::ifstream file;
		file.open(fileName);

		if (file.is_open()) {
			m_root = new Directory(rootDirName);
			m_current = m_root;

			while (file.peek() != EOF) {
				std::string file_path = "";
				std::string file_contents = "";
				std::string directory_path = "";

				char ch {};

				file >> file_path;

				if (file_path.compare(0, 3, "\xEF\xBB\xBF") == 0) // Check if UTF-8
				{
					file_path.erase(0, 3); 
				}

				file >> ch;

				directory_path = file_path;

				if (ch != '|') { // Directory only
					file.putback(ch); // return this black sheep back to the flock 
				}
				else { 
					getline(file, file_contents, '\n'); 

					this->trim(file_contents);
				}

				// TODO
				// Get tokens ex: images/pngs/elephant.png
				// token 1: images/ token 2: pngs/ token 3: elephant.png
				// add images/ to dir
				// use find() 'images/' then add pngs/ to the returned dir
				// use find() 'pngs/' then add elephant.png to the returned dir

				//directory_path = "ravni/denise/loona/ginger/coco.jpg";

				if (!directory_path.empty()) {
					// Get tokens
					std::vector<std::string> tokens;
					tokenize(directory_path, '/', tokens);

					// Loop in tokens
					for (auto token : tokens) {
						// Check if directory or file (a directory contains '/')
						size_t indexPos = token.find_first_of('/');

						if (indexPos == std::string::npos) { // Not found means this is a file.
							isDirectory = false;
						}
						else { // This is a directory
							isDirectory = true;
						}

						// Check if resource exist in current dir
						if (m_current->find(token) != nullptr) { // Found
							// Set dir to that token
							if (isDirectory) {
								m_current = dynamic_cast<Directory*>(m_current->find(token));
							}
						}
						else {
							if (isDirectory) {
								m_current->operator+=(new Directory(token));

								m_current = dynamic_cast<Directory*>(m_current->find(token));
							}
							else {
								m_current->operator+=(new File(token, file_contents));
							}
						}
					}

					m_current = m_root;
				}
			}

			file.close();
		}
		else {
			throw std::exception();
		}
	}
	Filesystem& Filesystem::operator+=(Resource* resource)
	{
		// adds a resource to the current directory.
		m_current->operator+=(resource);

		return *this;
	}
	Directory* Filesystem::change_directory(const std::string& dir)
	{
		// the parameter is optional (defaults to an empty string).
		// if an empty string is passed, change the current directory to the root directory.
		if (dir.empty()) {
			// thanks for the help prof Hong!
			m_current = m_root;
			return m_current;
		}

		auto dirFound = dynamic_cast<Directory*>(m_current->find(dir));

		// if no directory with the specified name exists (useDirectory::find() to locate the directory), 
		if (dirFound == nullptr || dirFound->count() == 0) {
			// report an std::invalid_argument exception with the message Cannot change directory! DIR_NAME not found!".
			throw std::invalid_argument("Cannot change directory! " + dir + " not found!");
		}
		else {
			// changes the current directory to the directory (located in the current directory) whose name matches argument.
			m_current = dirFound;
			return m_current;
		}

		return nullptr;
	}
	Filesystem::~Filesystem()
	{
		// a destructor that deallocates memory for the root directory.
		delete m_root;
	}

	// Move

	Filesystem::Filesystem(Filesystem&& src) noexcept
	{
		*this = std::move(src);
	}

	Filesystem& Filesystem::operator=(Filesystem&& src) noexcept
	{
		if (this != &src) {
			delete m_current;
			delete m_root;

			m_current = src.m_current;
			m_root = src.m_root;

			src.m_current = nullptr;
			src.m_root = nullptr;
		}

		return (*this);
	}
}