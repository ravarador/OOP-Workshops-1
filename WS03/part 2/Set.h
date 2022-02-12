/*
    Name: Jexequiel Ravni Arador
    Email: jrarador@myseneca.ca
    ID: 127168219
    Date Completed: February 03, 2022

    I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_SET_H
#define SDDS_SET_H
#include <cmath>
#include <iostream>
#include <string>

#include "Pair.h"
#include "Collection.h"

namespace sdds {
    template<class T>
    class Set : public Collection<T, 100> {

        // the Set will always have a capacity of 100 items
        const size_t CAPACITY = 100;
    public:
        Set() {};

        // override the inherited function add to prevent adding an item if it already exists in the Set.
        bool add(const T& item) {
            for (size_t i = 0; i < this->m_noOfElements; i++)
            {
                if (item == this->m_array[i])
                {
                    return false;
                }
            }

            return Collection<T, 100>::add(item);
        }
    };

    template<>
    bool Set<double>::add(const double& item) {
        for (size_t i = 0; i < this->m_noOfElements; i++)
        {
            // for T = double, the function add() should consider that two numbers are the same 
            // if their difference in the absolute value is smaller or equal to 0.01.
            // std::fabs is used in floating points values
            if (std::fabs(item - this->m_array[i]) <= 0.01)
            {
                return false;
            }
        }

        return Collection<double, 100>::add(item);
    };

}
#endif