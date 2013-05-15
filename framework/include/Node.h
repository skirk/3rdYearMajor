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

class Node : public Container<Slot>
{
	protected:
		//! id of the node
		int m_id;
		//! name of the node
		std::string m_name;
		//! type
		nodeType m_type;
		//! The Parent node
		Node *m_parent;

	public:
		Node();
		virtual	~Node();
		Node(const Node&);

		/*! \brief set m_name
		 *
		 * \param _name new name to be set to m_name
		 */
		void setName(const std::string &_name); 
		//! \brief Get the name of the Node
		std::string getName() const;
		/*! \brief set m_id
		 *
		 * \param _id new id to be set to m_id
		 */
		void setID(int _id);
		//! \brief Get the id of the Node
		std::string getID() const;
		//! \brief Get the type of the Node
		nodeType getType() const;
		//! \!brief set m_type
		void setType(const nodeType&);
		//! \brief Get the parent of the Node
		Node *getParent() const;
		//! \!brief set m_parent
		void setParent(Node *);
		//! \brief Prototype pattern
		virtual Node *clone();


};

#endif
