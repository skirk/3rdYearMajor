#include "Input.h"
#include "Output.h"

Input::Input(const char *_name, const SVariable &_var) : BaseSlot(_name, _var)
{
	m_type = Stype::input;
}

void Input::linkToOutput(Output &_s)
{
	m_ref = &_s;
}

Output* Input::getLink()
{
	return m_ref;
}

