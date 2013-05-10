#include "Node.h"
#include "Output.h"
#include "Input.h"
#include "Slot.h"

#include <sstream>

Node::Node() :
	m_name("empty")
{
	m_id = 0;
}
Node::~Node()
{}

Node::Node(const Node &_n)
{
	m_name = _n.getName(); 
	m_id = std::stoi(_n.getID());
	for(iterator it =_n.begin(); it != _n.end(); it++)
	{
		m_elems.push_back((*it)->clone()); 
	}
}

std::string Node::getName() const 
{
	return m_name;
}

void Node::setName(const std::string &_name)
{
	m_name = _name;
}
void Node::setID(int _id)
{
	m_id = _id;
}

std::string Node::getID() const
{
	std::ostringstream convert;
	convert << m_id;
	return convert.str();
}
nodeType Node::getType() const
{
	return m_type;
}
