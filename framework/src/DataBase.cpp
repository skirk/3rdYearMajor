#include "DataBase.h"
#include "FileInterface.h"
#include "Node.h"

#include <iostream>
#include <memory>
#include <cstdlib>

DataBase::DataBase()
{
}

/*
void DataBase::addNode(Node *_n)
{
	m_nodes.push_back(_n->clone());
}
*/


/*
Node *DataBase::getNode(const std::string &_name)
{
	ElemVec::iterator it;
	for (it = m_elems.begin(); it != m_elems.end(); ++it)
	{
		Node *n = *it;
		if(n->getName() == _name)
		{
			return n;
		}
	}
	static Node empty;
	return &empty;	
}
*/
/*
DataBase::NodeMap::iterator DataBase::begin()
{
	return m_nodes.begin();
}

DataBase::NodeMap::iterator DataBase::end()
{
	return m_nodes.end();
}
*/
