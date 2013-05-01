//! A Node Class
/*!
	Node represents an expression or a state
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>
#include "Enum.h"
#include "Container.h"
#include "Slot.h"

//class Slot;

class Node : public Container<Slot>
{
	protected:
		//! id of the node
		int m_id;
		//! name of the node
		std::string m_name;
		//! type
		nodeType m_type;
		//! slots
		//std::vector<Slot*> m_slots;

	public:
		Node();
		virtual	~Node();
		//virtual Node *clone() const;

		void setName(const std::string &_name); 
		std::string getName() const;

		//void addSlot(Slot*);
		//Slot* getSlot(const std::string &_name);
};

#endif
