/*  \author Tuomo Rinne
 *  \version 0.1
 *  \date 11/04/2013 
 *  \class Container
 *  \brief Container is a generic template class to contain elements that can be iterated with Boost Python
 */

#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include <string>

template <typename T>
class Container
{
	protected:
		typedef std::vector<T*> ElemVec;
		//! \brief Vector of elements
		ElemVec m_elems;
	public:
		//! \brief Default constructor
		Container();
		//! \brief Default destructor
		virtual ~Container();
		/* \brief Add element to the vector
		 *
		 * \param _elem element to add
		 */
		virtual void add(T *_elem);
		/* \brief Get element from a vector
		 *
		 * \param _name get element with corresponding name, if not found
		 * return an empty element
		 */
		virtual T *get(const std::string &_name);
		/* \brief Returns and iterator to the first element of m_elems vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		typename ElemVec::const_iterator begin() const;
		/* \brief Returns and iterator to the last element of m_elems vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		typename ElemVec::const_iterator end() const;	

		typedef typename ElemVec::const_iterator iterator;
};
//Header to contain the implementation details
#include "ContainerImpl.h"

#endif
