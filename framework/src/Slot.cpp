#include "Slot.h"
#include "Enum.h"

Slot::Slot() : 
	m_name("empty"),
	m_override(false)
{
}
Slot::Slot(Node *_parent, const char *_name, const Stype &_type,  const SVariable &_var)
	:m_name(_name), m_var(_var), m_type(_type), m_parent(_parent),
	m_override(false)
{
}

Slot::~Slot()
{
}

Slot::Slot(const Slot &_other)
{ m_name = _other.m_name;
	m_var = _other.m_var;
	m_type = _other.m_type;
	m_parent = _other.m_parent;
	m_link = _other.m_link;
	m_override = _other.m_override;
}



Slot& Slot::operator=(const Slot& _other)
{
	m_name = _other.m_name;
	m_var = _other.m_var;
	return *this;
}

std::string Slot::getName() const
{
	return m_name;
}

Stype Slot::getType() const
{
	return m_type;
}

bool Slot::isInput() const
{
	return  m_type == Stype::input;
}

Slot *Slot::clone()
{
	return new Slot(*this);
}

Node *Slot::getParent()
{
	return m_parent;
}

void Slot::linkToSlot(Slot *_s)
{
	m_link = _s;
	m_override=true;
}

void Slot::removeLink()
{
	m_link = NULL;
	m_override=false;
}

Slot* Slot::getLink()
{
	return m_link;
}

bool Slot::isOverwritten()
{
	return m_override;
}

