//! A Node Class
/*!
	Node represents an expression or a state
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>
#include "Enum.h"

class Slot;

class Node {
	protected:
		//! id of the node
		int m_id;
		//! name of the node
		std::string m_name;
		//! type
		nodeType m_type;
		//! inputSlots
		std::vector<Slot*> m_inputSlots;
		//! outputSlots
		std::vector<Slot*> m_outputSlots;

	public:
		Node();
		virtual	~Node();
		std::string getName() const;
		void setName(const std::string &_name); 
		virtual Node *clone() const;
		void addInputSlot(const Slot&);
		void addOutputSlot(const Slot&);
};

#endif
