#include "Graph.h"
#include "DataBase.h"
#include "Connection.h"
#include <boost/tokenizer.hpp>
#include <iostream>

void Graph::connectNodes(const std::string &_lhs, const std::string &_rhs)
{
	boost::tokenizer<> ltok(_lhs);
	boost::tokenizer<>::iterator lbeg = ltok.begin();

	std::string lnode = *lbeg;
	std::string lslot = *++lbeg;
	std::cout<<"tokenizer : "<<lnode<<'\t'<<lslot<<'\n';

	boost::tokenizer<> rtok(_rhs);
	boost::tokenizer<>::iterator rbeg = rtok.begin();

	std::string rnode = *rbeg;
	std::string rslot = *++rbeg;
	std::cout<<"tokenizer : "<<rnode<<'\t'<<rslot<<'\n';

	Node *lhs = getNode(lnode);
	if(lhs->getName()=="empty")
		std::cout<<"lhs is empty\n";

	Node *rhs = getNode(rnode);
	if(rhs->getName()=="empty")
		std::cout<<"rhs is empty\n";

	m_connections.push_back(new Connection(lhs->get(lslot), rhs->get(rslot)));

}
void Graph::addNode(const std::string &_name)
{
	m_nodes.push_back(m_db->get(_name));
}	

Node *Graph::getNode(const std::string &_name)
{
	NodeVec::iterator it;
	for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
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


void Graph::exportXML()
{


/*
Graph::NodeMap::iterator Graph::begin()
{
	return m_nodes.begin();
}

Graph::NodeMap::iterator Graph::end()
{
	return m_nodes.end();
}
*/
