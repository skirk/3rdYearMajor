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

class Node : public Container<BaseSlot>
{
	protected:
		//! id of the node
		int m_id;
		//! name of the node
		std::string m_name;
		//! type
		nodeType m_type;

	public:
		Node();
		virtual	~Node();
		Node(const Node&);
		//virtual Node *clone() const;

		void setName(const std::string &_name); 
		std::string getName() const;

		void setID(int _id);
		std::string getID() const;

		nodeType getType();

		virtual void write(const std::string &_file);

		//void addSlot(Slot*);
		//Slot* getSlot(const std::string &_name);
};

#endif
