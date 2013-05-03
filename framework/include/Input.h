#ifndef _INPUT_H
#define _INPUT_H_
#include <memory>

#include "Slot.h"
class Output;

class Input : public BaseSlot
{
	public:
		Input(const char *_name, const SVariable &_var); 
		void linkToOutput(Output &_s);
		Output *getLink();

	private:
		Output *m_ref;
		
};

#endif
