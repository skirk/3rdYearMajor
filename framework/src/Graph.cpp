#include "Graph.h"
#include "DataBase.h"

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

	int its = 0;
	NodeVec::iterator it;
	std::cout<<"accessing iterators\n";
	for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		std::cout<<"in get Node\n";
		Node *n = *it;
		if(n->getName() == _name)
		{
			std::cout<<"name matches\n";
			int i = std::stoi(n->getID());
			if(i == _id)
			{
				std::cout<<"id matches\n";
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
	_n->setParent(this);
	m_nodes.push_back(_n);
}	

Graph *Graph::clone()
{
	return  new Graph(*this);
}
