#include "Input.h"
#include "Output.h"
#include <iostream>

Input::Input(Node *_parent, const char *_name, const SVariable &_var) :
	Slot(_parent, _name, _var),
	m_override(false)
{
	m_type = Stype::input;
}

Input::~Input()
{
}


