#include <Node.h>
Node::Node()
{}
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
