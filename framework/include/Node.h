//! A Node Class
/*!
	Node represents an expression or a state
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <string>

#include "Slot.h"

//! An enum
/*!
	Determines the node type
*/
enum nodeType {
	NETWORK, /*!< Enum value NETWORK. */
	STATE /*!< Enum value STATE. */
};

class Node {
	protected:
		//! name of the node
		std::string m_name;
		//! id of the node
		int m_id;
		//! type
		nodeType m_type;
		//! inputSlots
		std::vector<Slot> m_inputSlots;
		//! outputSlots
		std::vector<Slot> m_outputSlots;

	public:
		Node();
		virtual	~Node();
		std::string getName() const;
		virtual Node *clone() const;
		void addInputSlot(const Slot&);
		void addOutputSlot(const Slot&);
};

#endif
