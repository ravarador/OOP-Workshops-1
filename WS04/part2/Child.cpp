/*
    Name: Jexequiel Ravni Arador
    Email: jrarador@myseneca.ca
    ID: 127168219
    Date Completed: February 13, 2022

    I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Child.h"
#include <iostream>

using namespace std;

namespace sdds {
	Child::~Child() {
        for (u_int i = 0; i < m_noOfToys; i++)
            delete m_toys[i];

        delete[] this->m_toys;
	}

	// COPYING

	Child::Child(const Child& src) {
        *this = src; // call operator=
	}

	Child& Child::operator=(const Child& src) {
        if (this != &src) {
            set(src.m_childname, src.m_age, src.m_toys, src.m_noOfToys);
        }

        return (*this);
	}

	// MOVING

	Child::Child(Child&& src) noexcept {
        *this = move(src);
	}

	Child& Child::operator=(Child&& src) noexcept {
        if (this != &src) {
            delete[] this->m_toys;
            m_toys = src.m_toys;
            src.m_toys = nullptr;

            m_childname = src.m_childname;
            m_age = src.m_age;
            m_noOfToys = src.m_noOfToys;

            src.m_age = 0;
            src.m_noOfToys = 0;
        }

        return (*this);
	}

    void Child::set(std::string name, int age, const Toy * toys[], size_t count) {
        if (toys != nullptr) {

            for (u_int i = 0; i < m_noOfToys; i++)
                delete m_toys[i];

            delete[] this->m_toys;
            
            m_toys = new const sdds::Toy*[count];

            for (u_int i = 0; i < count; i++) {
                m_toys[i] = new const sdds::Toy(*toys[i]);
            }

            m_childname = name;
            m_age = age;
            m_noOfToys = count;
        }
    }

    std::ostream& Child::display(std::ostream& os)const {
        static u_int counter = 1;

        os << "--------------------------" << endl;
        os << "Child " << counter++ << ": " << m_childname << " " << m_age << " years old:" << endl;
        os << "--------------------------" << endl;

        if (m_noOfToys) {
            for (size_t i = 0; i < m_noOfToys; i++) {
                m_toys[i]->display(cout);
            }
        }
        else {
            os << "This child has no toys!" << endl;
        }

        os << "--------------------------" << endl;

        return os;
    }

    Child::Child(std::string name, int age, const Toy* toys[], size_t count) {
        if (toys != nullptr) {
            set(name, age, toys, count);
        }
    }

    size_t Child::size() const {
        return m_noOfToys;
    }

    std::ostream& operator<<(std::ostream& os, Child& src) {
        return src.display(os);
    }
}