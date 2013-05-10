#include "Graph.h"
#include "DataBase.h"
#include "Connection.h"

#include <iostream>

Graph::NodeVec::const_iterator Graph::NodeBegin() const
{
	return m_nodes.begin();
}

Graph::NodeVec::const_iterator Graph::NodeEnd() const
{
	return m_nodes.end();
}

Node *Graph::getNode(const std::string &_name, int _id)
{
	NodeVec::iterator it;

	int its = 0;
	for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		Node *n = *it;
		if(n->getName() == _name)
		{
			int i = std::stoi(n->getID());
			if(i == _id)
			{
				return n;
			}
		}
		its++;
	}
	static Node empty;
	return &empty;	
}

void Graph::addNode(Node *_n)
{
	int id = 0;
	while( getNode(_n->getName(), id)->getName() != "empty")
	{
		id++;
	}
	_n->setID(id);
	m_nodes.push_back(_n);
}	
