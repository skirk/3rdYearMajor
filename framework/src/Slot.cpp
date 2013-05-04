#include "Slot.h"
#include "Enum.h"

BaseSlot::BaseSlot()
	:m_name("empty")
{
}

BaseSlot::~BaseSlot()
{
}

BaseSlot::BaseSlot(const char *_name, const SVariable &_var)
	:m_name(_name), m_var(_var)
{
}

BaseSlot& BaseSlot::operator=(const BaseSlot& _other)
{
	m_name = _other.m_name;
	m_var = _other.m_var;
	return *this;
}

std::string BaseSlot::getName() const
{
	return m_name;
}

bool BaseSlot::isInput() const
{
	return m_type == Stype::input; 
}
