#include "Context.h"
#include "Slot.h"
#include "Graph.h"
#include "NodeFactory.h"
#include "DataBase.h"
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
	//could do with better solution
	bool b_lhs, b_rhs;
	b_lhs = lhs->isInput();
	b_rhs = rhs->isInput();
	std::cout<<b_lhs<<b_rhs<<'\n';
	//check whether the context is the current node, if so reverse the slot 
	if( lhs->getParent() == m_current )
	{
		std::cout<<"lhs parent node match\n";
		b_lhs = !b_lhs;
	}
	if( rhs->getParent() == m_current )
	{
		std::cout<<"rhs parent node match\n";
		b_rhs = !b_rhs;
	}

	std::cout<<b_lhs<<b_rhs<<'\n';
	if( b_lhs ^ b_rhs )
	{
		if(b_lhs)
		{
			lhs->linkToSlot(rhs);
			std::cout<<"connection formed\n";
			return;
		}
		else if (b_rhs)
		{
			rhs->linkToSlot(lhs);
			std::cout<<"connection formed\n";
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

Node *Context::getNodeFromString(const std::string &_name)
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
	if(i==2)
	{
		std::string node = *beg1;
		std::string id   = *++beg1;
		int i = std::stoi(id);
		Node *n = m_current->getNode(node, i);

		Graph *g = dynamic_cast<Graph*>(n);
		if(g == NULL)
		{
			std::cout<<"failed to transfer\n";
		}
		return n;
	}
	else
	{
		std::cout<<"Node path is wrong\n";
		return new Node;
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
	m_current->add(new Slot(m_current, _name.c_str(), Stype::input, _var));
}
void Context::addOutputSlot(const std::string &_name,  const SVariable &_var)
{
	m_current->add(new Slot(m_current ,_name.c_str(), Stype::output,_var));	
}

void Context::addNode(const std::string &_name)
{
	NodeFactory &fact = NodeFactory::getInstance();
	Node *n =fact.createNode(_name, nodeType::GRAPH)->clone();
	n->setParent(m_current);
	m_current->addNode(n);
	if(n->getType() == nodeType::GRAPH)
	{
		inputs.push_back(n);
	}
}

void Context::writeNode(const std::string &_file)
{
	XMLExporter exp;
	exp.open(_file);
	exp.write(m_current);
	exp.close();
}

void Context::goUpALevel()
{ 
	Graph *g = dynamic_cast<Graph*>(m_current->getParent());
	if(g == NULL)
	{
		std::cout<<"failed to go up\n";
		return;
	}
	m_current=g;
}

void Context::goDownALevel(const std::string &_name)
{
	Graph *g = dynamic_cast<Graph*>(getNodeFromString(_name));
	if(g == NULL)
	{
		std::cout<<"failed to go down\n";
		return;
	}
	m_current=g;
}

Graph *Context::getCurrent() const
{
	return m_current;
}

void Context::printDB() const
{
	NodeFactory &fact = NodeFactory::getInstance();
	DataBase *db = fact.getDB();
	Container<Node>::iterator it = db->begin();
	for(; it != db->end(); it++){
		std::cout<<(*it)->getName()<<'\n';
	}

}
