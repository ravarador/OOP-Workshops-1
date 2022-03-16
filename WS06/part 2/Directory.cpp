/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <string>
#include <iomanip>

#include"Directory.h"
#include"File.h"
#include"Resource.h"

namespace sdds {
	Directory::Directory(std::string dirName) {
		for (auto i : m_contents) {
			i->update_parent_path(dirName);
		}

		m_name = dirName;
	}

	void Directory::update_parent_path(const std::string& parentPath) {
		for (auto i : m_contents) {
			i->update_parent_path(parentPath);
		}

		m_parent_path = parentPath;
	}

	size_t Directory::size() const {
		if (m_contents.size() == 0) {
			return 0u;
		}

		size_t sumSize = 0;
		for (auto i : m_contents) {
			sumSize += i->size();
		}
		return sumSize;
	}

	Directory& Directory::operator+=(Resource* resource) 
	{
		for (auto i : m_contents) {
			// if a match is found, throw and exception and do nothing else;
			if (i->name() == resource->name()) {
				throw std::exception();
			}
		}

		// if no match is found, add the resource and update the absolute path location of the added resource with the directory's full absolute path.
		resource->update_parent_path(this->path());

		m_contents.push_back(resource);
		
		return *this;
	}

	Resource* Directory::find(const std::string& dirName, const std::vector<OpFlags>& flags) {
		bool searchRecursively = false;

		// check vector of flags if recursive exists
		for (auto flag : flags) {
			if (flag == OpFlags::RECURSIVE) {
				searchRecursively = true;
			}
		}

		for (auto i : m_contents) {
			if (searchRecursively) {
				if (i->type() == NodeType::DIR) {
					return dynamic_cast<Directory*>(i)->find(dirName);
				}
				else {
					if (i->name() == dirName) {
						return i;
					}
				}
			}
			else {
				if (i->name() == dirName) {
					return i;
				}
			}
		}

		return nullptr;
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
	{
		bool hasRecursiveFlag = false;

		for (auto flag : flags) {
			if (flag == OpFlags::RECURSIVE) {
				hasRecursiveFlag = true;
			}
		}
			
		std::vector<Resource*> temp_contents{};

		for (auto i : m_contents) {
			if (i->name() == name) {
				if (i->type() == NodeType::DIR) { // If the matched resource is a directory, the RECURSIVE flag must be set,
					if (!hasRecursiveFlag) {
						// otherwise this member reports an std::invalid_argument exception with the message NAME is a directory. Pass the recursive flag to delete directories."
						throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
					}
					else {
						// thanks for the help prof Hong!
						auto foundDir = this->find(name, { OpFlags::RECURSIVE });

						if (foundDir != nullptr) {
							delete foundDir;
						}

						delete i;
					}
				}
				else {
					delete i; // Deallocate this resource since we don't need it anymore
				}
			}
			else {
				temp_contents.push_back(i);
			}
			
		}

		// Check if diff size, if diff size it means that a name matched and thus not pushed to temp container
		if (m_contents.size() != temp_contents.size()) {
			m_contents.clear(); // clear m_contents first
			m_contents = std::move(temp_contents); // move the contents of temp_contents to m_contents
		}
		else {
			// If no matching resource is found, report an exception of type std::string with the message NAME does not exist in DIRECTORY_NAME.
			throw(name + " does not exist in " + this->name());
		}
	}

	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const
	{
		bool hasLongFlag = false;


		for (auto flag : flags) {
			if (flag == FormatFlags::LONG) {
				hasLongFlag = true;
			}
		}

		// First inserts Total size: XX bytes and a newline into the output stream where XX is the size of the directory.
		os << "Total size: " << this->size() << " bytes" << std::endl;

		// For each resource in the directory, first add F or D to the output stream based on the resource type, 
		// then add the resource information to the output stream in the following format:
		// D | DIR_NAME |
		// F | FILE_NAME |
		// where the name of the resource is left-aligned within a field width of 15 characters.
		// If the LONG flag is in the second parameter, insert into the output stream additional information about the resource :
		// D | DIR_NAME | COUNT | XX bytes |
		// F | FILE_NAME |    | XX bytes |

		for (auto res : this->m_contents) {
			std::string count = "";
			std::string size = "";

			count = res->count() == -1 ? "" : std::to_string(res->count());
			size = std::to_string(res->size()) + " bytes";

			if (hasLongFlag) {
				if (res->type() == NodeType::DIR) {
					os << "D" << 
						" | " << 
						std::setw(15) << std::left << res->name() << 
						" | " << 
						std::setw(2) << std::right << count <<
						" | " << 
						std::right << std::setw(10) << size <<
						" | " <<
						std::endl;
				}
				else {
					os << "F" << 
						" | " << 
						std::setw(15) << std::left << res->name() << 
						" | " << std::right << std::setw(2) << count << 
						" | " << std::right << std::setw(10) << size <<
						" | " <<
						std::endl;
				}
			}
			else {
				if (res->type() == NodeType::DIR) {
					os << "D" << " | " << std::setw(15) << std::left << res->name() << " |" << std::endl;
				}
				else {

					os << "F" << " | " << std::setw(15) << std::left << res->name() << " |" << std::endl;
				}
				
			}
			
		}
	}
}