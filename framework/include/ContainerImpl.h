#ifndef _IMPLEMENTATION_H_
#define _IMPLEMENTATION_H_

#include <iostream>

template<typename T>
Container<T>::Container()
{}

template<typename T>
Container<T>::~Container()
{}

template<typename T>
typename Container<T>::ElemVec::const_iterator Container<T>::begin() const
{
	return m_elems.begin();
}

template<typename T>
typename Container<T>::ElemVec::const_iterator Container<T>::end() const 
{
	return m_elems.end();
}
template<typename T>
void Container<T>::add(T *_elem)
{
	m_elems.push_back(_elem);
}

template<typename T>
T *Container<T>::get(const std::string &_name)
{
	iterator it;
	for (it = m_elems.begin(); it != m_elems.end(); ++it)
	{
		T *t = *it;
		if(t->getName() == _name)
		{
			return t;
		}
	}
	static T empty;
	return &empty;	

}
#endif
