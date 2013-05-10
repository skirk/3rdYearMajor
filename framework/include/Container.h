#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include <string>

template <typename T>
class Container
{
	protected:
		typedef std::vector<T*> ElemVec;
		ElemVec m_elems;
	public:
		Container();
		virtual ~Container();

		virtual void add(T *_elem);
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

#include "ContainerImpl.h"

#endif
