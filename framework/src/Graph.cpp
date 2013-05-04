#include "Graph.h"
#include "DataBase.h"
#include "Input.h"
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
	{
		std::cout<<"lhs is empty\n";
		return;
	}
	Node *rhs = getNode(rnode);
	if(rhs->getName()=="empty")
	{
		std::cout<<"rhs is empty\n";
		return;
	}

	if(!(rhs->get(rslot)->isInput() ^ lhs->get(lslot)->isInput()))
	{
		//could do with better solution
		if(lhs->get(lslot)->isInput())
		{
			Input *i1 = (Input*)lhs->get(lslot);
			Output *o1 = (Output*)rhs->get(rslot);
			i1->linkToOutput(*o1);
		}
		else
		{
			Input *i1 = (Input*)rhs->get(rslot);
			Output *o1 = (Output*)lhs->get(lslot);
			i1->linkToOutput(*o1);
		}
		std::cout<<"connection formed!"<<'\n';
		return;
	}
	else
	{
		std::cout<<"connection invalid\n";
		return;
	}
}

void Graph::addNode(const std::string &_name)
{
	m_asd.push_back(m_db->get(_name));
}	

Node *Graph::getNode(const std::string &_name)
{
	NodeVec::iterator it;
	for (it = m_asd.begin(); it != m_asd.end(); ++it)
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


Graph::NodeVec::iterator Graph::NodeBegin()
{
	return m_asd.begin();
}

Graph::NodeVec::iterator Graph::NodeEnd()
{
	return m_asd.end();
}

/*

   Slot *Graph::searchOutputToInput(const std::string &_name)
   {
   std::vector<Connection*>::iterator it;
   for(it = m_connections.begin() 

*/
