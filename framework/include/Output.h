#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "Enum.h"
#include "Slot.h"
class Node;

class Output : public BaseSlot
{
	public:
		Output(Node *_parent, const char *_name, const SVariable &_var);
		Node *getParent();
		Output *clone();
	private:
		Node *m_parent;

};

#endif
