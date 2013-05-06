#include "Graph.h"
#include "DataBase.h"
#include "Input.h"
#include "Output.h"
#include "Connection.h"
#include <boost/tokenizer.hpp>
#include <iostream>

void Graph::connectNodes(const std::string &_lhs, const std::string &_rhs)
{

	BaseSlot *lhs = getSlotFromString(_lhs);
	if(lhs->getName()=="empty")
	{
		std::cout<<"target slot doesn't exist"<<'\n';
		return;
	}
	BaseSlot *rhs = getSlotFromString(_rhs);
	if(rhs->getName()=="empty")
	{
		std::cout<<"source slot doesn't exist"<<'\n';
		return;
	}

	if( lhs->isInput() ^ rhs->isInput())
	{
		//could do with better solution
		if(lhs->isInput())
		{
			Input *i1 = dynamic_cast<Input*>(lhs);
			if(i1==NULL)
			{
				std::cout<<"couldn't convert Slot to Input\n";
				return;
			}
			Output *o1 = dynamic_cast<Output*>(rhs);
			if(o1==NULL)
			{
				std::cout<<"couldn't convert Slot to Output\n";
				return;
			}
			i1->linkToOutput(*o1);
			std::cout<<"connection formed!"<<'\n';
			return;
		}
		else if (rhs->isInput())
		{
			Input *i1 = dynamic_cast<Input*>(rhs);
			if(i1==NULL)
			{
				std::cout<<"in else couldn't convert Slot to Input\n";
				return;
			}
			Output *o1 = dynamic_cast<Output*>(lhs);
			if(o1==NULL)
			{
				std::cout<<"couldn't convert Slot to Output\n";
				return;
			}
			i1->linkToOutput(*o1);
			std::cout<<"connection formed!"<<'\n';
			return;
		}
	}
	else
	{
		std::cout<<"connection invalid\n";
		return;
	}
	std::cout<<"connection not formed\n";
}

void Graph::addNode(const std::string &_name)
{
	int id = 0;
	std::cout<<"adding node "<< _name <<'\n';
	while(getNode(_name, id)->getName() != "empty")
	{
		id++;
		std::cout<<"increment "<< id <<'\n';
	}
	Node *n = new Node(*m_db->get(_name));
	n->setID(id);
	std::cout<<"node added  "<<n->getName()<<n->getID() <<'\n';
	m_nodes.push_back(n);
	for(unsigned int i = 0; i<m_nodes.size(); i++)
	{
		std::cout<<"node in vec  "<<m_nodes[i]->getName()<<m_nodes[i]->getID() <<'\n';
	}
}	

BaseSlot *Graph::getSlotFromString(const std::string &_name)
{
	boost::tokenizer<> tok(_name);
	boost::tokenizer<>::iterator beg = tok.begin();

	std::string node = *beg;
	std::string id   = *++beg;
	std::string slot = *++beg;
	int i = std::stoi(id);
	std::cout<<"tokenizer : "<<node<<'\t'<<id<<'\t'<<slot<<'\n';
	Node *n = getNode(node, i);
	if(n->getName()=="empty")
	{
		std::cout<<"Couldn't find "<<node<<"\n";
		return new BaseSlot;
	}
	return n->get(slot);
}


Node *Graph::getNode(const std::string &_name, int _id)
{
	NodeVec::iterator it;

	std::cout<<"getting node "<< _name<< _id <<'\n';
	int its = 0;
	for (it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		Node *n = *it;
		std::cout<<"looking at "<<n->getName()<<n->getID()<<'\n';
		if(n->getName() == _name)
		{
			std::cout<<"name matched\n";
			int i = std::stoi(n->getID());
			std::cout<<i<<" "<<_id;
			if(i == _id)
			{
				std::cout<<"id matched\n";
				return n;
			}
		}
		its++;
		std::cout<<its<<'\n';
	}
	static Node empty;
	return &empty;	
}


Graph::NodeVec::iterator Graph::NodeBegin()
{
	return m_nodes.begin();
}

Graph::NodeVec::iterator Graph::NodeEnd()
{
	return m_nodes.end();
}

/*

   Slot *Graph::searchOutputToInput(const std::string &_name)
   {
   std::vector<Connection*>::iterator it;
   for(it = m_connections.begin() 

*/
