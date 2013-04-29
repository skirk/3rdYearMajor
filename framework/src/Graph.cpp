#include "Graph.h"
#include "DataBase.h"
#include "Connection.h"
#include <iostream>

void Graph::connectNodes(const Slot &_lhs, const Slot &_rhs)
{
}

void Graph::addNode(const std::string &_name)
{
	m_nodes.push_back(m_db->getNode(_name));
}	

Graph::NodeMap::iterator Graph::begin()
{
	return m_nodes.begin();
}

Graph::NodeMap::iterator Graph::end()
{
	return m_nodes.end();
}
