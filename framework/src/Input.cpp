#include "Input.h"
#include "Output.h"
#include <iostream>

Input::Input(const char *_name, const SVariable &_var) :
	BaseSlot(_name, _var),
	m_override(false)
	//BaseSlot::m_type(Stype::input)
{
	std::cout<<"Input constructor called"<<'\n';
	m_type = Stype::input;
}

void Input::linkToOutput(Output &_s)
{
	m_ref = &_s;
	m_override=true;
}

Output* Input::getLink()
{
	return m_ref;
}

bool Input::isOverwritten()
{
	return m_override;
}

