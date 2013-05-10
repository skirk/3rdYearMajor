#include "Context.h"
#include "Slot.h"
#include "Graph.h"
#include "NodeFactory.h"
#include "Exporter.h"

#include <iostream>
#include <cstdlib>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

Context::Context()
{
	m_current = new Graph();
	m_current->setName("root");

	NodeFactory &fact = NodeFactory::getInstance();
	fact.InitDB();
}

void Context::connectSlots(const std::string &_lhs, const std::string &_rhs)
{

	Slot *lhs = getSlotFromString(_lhs);
	if(lhs->getName()=="empty")
	{
		std::cout<<"target slot doesn't exist"<<'\n';
		return;
	}
	Slot *rhs = getSlotFromString(_rhs);
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
			/*
			if (castAndConnect(lhs, rhs))
			{
				std::cout<<"connection succesfull\n";
				return;
			}
			else
			{
				std::cout<<"connection failed\n";
				return;
			}
			*/

		}
		else if (rhs->isInput())
		{
			/*
			if(castAndConnect(rhs, lhs))
			{
				std::cout<<"connection successful\n";
				return;
			}
			else
			{
				std::cout<<"connection failed\n";
				return;
			}
			*/
		}
	}
	else
	{
		std::cout<<"connection invalid\n";
		return;
	}
	std::cout<<"connection not formed\n";
}

void Context::disconnectSlots(const std::string &_inputSlot)
{
	Slot *input = getSlotFromString(_inputSlot);
	input->removeLink();
}

Slot *Context::getSlotFromString(const std::string &_name)
{
	boost::tokenizer<> tok(_name);
	boost::tokenizer<>::iterator beg = tok.begin();
	boost::tokenizer<>::iterator beg1 = beg;

	int i = 0;
	//this solution could be done a bit better
	for(; beg != tok.end(); beg++)
	{
		i++;
	}
	//the slot has to be either graphs or some of its slots
	//the graph requires one token , where the node slot path requires 3
	if(i == 1)
	{
		//when the context is inside the node the desired node is the opposite slot
		std::string slotname = *beg1;
		slotname = slotname + "Pair";	
		return m_current->get(slotname);
	}
	else if(i == 3)
	{
		std::string node = *beg1;
		std::string id   = *++beg1;
		std::string slot = *++beg1;
		int i = std::stoi(id);
		Node *n = m_current->getNode(node, i);
		if(n->getName()=="empty")
		{
			std::cout<<"Couldn't find "<<node<<"\n";
			return new Slot;
		}
		return n->get(slot);
	}
	else
	{
		std::cout<<"Slot path is wrong\n";
		return new Slot;
	}
}
/*

   Slot *Context::searchOutputToInput(const std::string &_name)
   {
   std::vector<Connection*>::iterator it;
   for(it = m_connections.begin() 

*/

void Context::addInputSlot(const std::string &_name, const SVariable &_var)
{
	//m_current.addNode();
}
void Context::addOutputSlot(const std::string &_name,const SVariable &_var)
{
	//m_current.addNode(new Pair(this,_name.c_str(), Stype::output, _var));	
}

void Context::addNode(const std::string &_name)
{
	NodeFactory &fact = NodeFactory::getInstance();
	m_current->addNode(fact.createNode(_name, nodeType::GRAPH));
}

void Context::writeNode(const std::string &_file)
{
	XMLExporter exp;
	exp.open(_file);
	exp.writeNode(m_current);
}
