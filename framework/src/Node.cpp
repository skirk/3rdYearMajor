#include "Node.h"
#include "Slot.h"

Node::Node()
	:m_name("empty")
{
}
Node::~Node()
{}

/*
Slot *Node::getSlot(const std::string &_name)
{
	std::vector<Slot*>::iterator it;
	for (it = m_slots.begin(); it != m_slots.end(); ++it)
	{
		Slot *s = *it;
		if(s->getName() == _name)
		{
			return s;
		}
	}
	static Slot empty;
	return &empty;
}
*/
/*
void Node::addOutputSlot(Slot *_in)
{
	m_outputSlots.push_back(_in);
}

Node *Node::clone() const 
{
	return new Node(*this);
}

*/
std::string Node::getName() const
{
	return m_name;
}

void Node::setName(const std::string &_name)
{
	m_name = _name;
}
