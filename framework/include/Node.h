//! A Node Class
/*!
	Node represents an expression or a state
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <vector>

#include "Slot.h"

//! An enum
/*!
	Determines the node type
*/
enum nodeType {
	DIAGRAM, /*!< Enum value DIAGRAM. */
	STATE /*!< Enum value STATE. */
};

class Node {
	private:
		//! id of the node
		int m_id;
		//! node name
		std::string m_name;
		//! type
		nodeType m_type;
		//! inputSlots
		std::vector<Slot> m_inputSlots;
		//! outputSlots
		std::vector<Slot> m_outputSlots;

	public:
		Node(const std::string &_filename);
		~Node();
};

#endif
