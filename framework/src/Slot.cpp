#include "Slot.h"
#include "Enum.h"

Slot::Slot(const char *_name, const SlotVar &_var)
	:m_name(_name), m_var(_var)
{
}

Slot& Slot::operator=(const Slot& _other)
{
	m_override = _other.m_override;
	m_name = _other.m_name;
	m_var = _other.m_var;
	return *this;
}
