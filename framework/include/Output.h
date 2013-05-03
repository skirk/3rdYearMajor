#ifndef _INPUT_H
#define _INPUT_H_

class Output : public BaseSlot
{
	public:
		Output(const char *_name, const SVariable &_var): BaseSlot(_name, _var)
	{ m_type = Stype::output; }

};

#endif
