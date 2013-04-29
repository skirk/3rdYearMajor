#include <Node.h>
Node::Node()
	:m_name("empty")
{
}
Node::~Node()
{}

void Node::addInputSlot(const Slot &_in)
{
	m_inputSlots.push_back(_in);
}

void Node::addOutputSlot(const Slot &_in)
{
	m_outputSlots.push_back(_in);
}

Node *Node::clone() const 
{
	return new Node(*this);
}

std::string Node::getName() const
{
	return m_name;
}

void Node::setName(const std::string &_name)
{
	m_name = _name;
}
