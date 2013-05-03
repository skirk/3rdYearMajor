/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 29/04/2013 Initialisation 
 *  \class Graph
 *  \brief  Graph is a set of nodes and their connections
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Node.h"
#include <vector>
#include <map>
#include <string>

class DataBase;
class Connection;

class Graph : public Node
{
	private:
		/*! \brief DataBase
		 *
		 * DataBase that the graph gets its nodes from
		 */
		DataBase *m_db;
		typedef std::vector<Node*> NodeVec;
		/*! \brief Vector of Nodes
		 *
		 * Nodes inside the graph
		 */
		NodeVec m_nodes;
		/*! \brief Vector of Connections
		 *
		 *  Successful connections inside the Graph
		 */
	private:
		Node *getNode(const std::string &_name);
	public:
		/* \brief A constructor
		 *
		 *  Inject dependency to a DataBase object
		 */
		Graph(DataBase *_db):
			m_db(_db) {}
		/* \brief Connect two slots together
		 *
		 * \param _lhs left hand side Slot
		 * \param _rhs right hand side Slot
		 */
		void connectNodes(const std::string &_lhs, const std::string &_rhs);
		/* \brief Add node to the Graph from the Database
		 *
		 * \param _name name of the node to add
		 */
		void addNode(const std::string &_name);
		
		/* \brief Returns and iterator to the first element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeVec::iterator begin();
		/* \brief Returns and iterator to the last element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeVec::iterator end();

};

#endif
