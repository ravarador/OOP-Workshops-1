/*
	Name: Jexequiel Ravni Arador
	Email: jrarador@myseneca.ca
	ID: 127168219
	Date Completed: March 12, 2022

	I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include"Resource.h"
#include"Flags.h"

namespace sdds {
	class Directory : public sdds::Resource {
	private:
		// an object of type std::vector that holds pointers to Resource objects. Each element of the vector can either be a Directory or a File.
		std::vector<Resource*> m_contents{};
	public:
		// a custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
		Directory(std::string dirName);

		// sets the parent path to the parameter. For each resource that this directory holds, 
		// this member should also set their absolute path locations to the full absolute path of this directory.
		void update_parent_path(const std::string&);

		// a query that returns Flags::DIR
		NodeType type() const {
			return NodeType::DIR;
		}

		// a query that returns the full absolute path of the directory (a concatenation of the absolute path location and the directory name).
		std::string path() const {
			return m_parent_path + m_name;
		}

		// a query that returns the name of the directory.
		std::string name() const {
			return m_name;
		}

		// a query that returns the number of resources that this directory holds.
		int count() const {
			return m_contents.size();
		}

		// a query that returns the size of the directory in bytes. 
		// The size of the directory is the sum of the individual sizes of each resource that this directory holds. 
		// This member returns 0u if the directory is empty.
		size_t size() const;

		// adds a resource to the directory and returns a reference to the current directory. 
		// This member should check for existing resources in the directory with the same name:
		// if a match is found, throw and exception and do nothing else;
		// if no match is found, add the resource and update the absolute path location of the added resource with the directory's full absolute path.
		Directory& operator+=(Resource*);

		// finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found.
		// This member also takes an optional vector of flags that determine how the find is performed(defaults to an empty collection).
		// if the RECURSIVE flag is in the second parameter, this member will also attempt to recursively find a match in each directory that is in the m_contents vector. 
		// HINT: If an element in m_contents is a directory, use its find() member function to find a match.
		// NOTE: If the current directory holds another directory named src which contains a file named sample.txtand we want to find sample.txt, 
		// this member will only return the sample.txt resource if the RECURSIVE flag is set, nullptr otherwise.
		Resource* find(const std::string&, const std::vector<OpFlags> & = {});

		// a destructor that deallocates memory for each resource that this directory holds.
		virtual ~Directory() {
			for (auto i : m_contents) {
				delete i;
			}

			m_contents.clear();
		}

		// this class should not allow copy / move operations./
		
		// disable copy constructor
		Directory(const Directory&) = delete;

		// // disable copy assignment operator
		Directory& operator=(const Directory&) = delete;

		// disable move constructor
		Directory(Directory&& src) = delete;

		// // disable move assignment operator
		Directory& operator=(Directory&& src) = delete;

		// PART 2

		// deletes a resource from the directory whose name matches the first argument (removing it from its contents and deallocating memory for it).
		void remove(const std::string&, const std::vector<OpFlags> & = {});

		// good 'ol classic display
		void display(std::ostream&, const std::vector<FormatFlags>& = {}) const;
	};
};

#endif // !SDDS_DIRECTORY_H