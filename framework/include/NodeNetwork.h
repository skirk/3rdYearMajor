//! A NodeNetwork class
/*!
 * NodeNetwork represents a graph of nodes 
*/

#ifndef _NODENETWORK_H_
#define _NODENETWORK_H_

#include "Node.h"
class DataBase;
class NodeNetwork : public Node
{
	private:
		DataBase *m_db;
	public:
		NodeNetwork(DataBase *_db)
			:m_db(_db) {}
		void connectNodes();
		void addNode(const Node &_node);

};

#endif
