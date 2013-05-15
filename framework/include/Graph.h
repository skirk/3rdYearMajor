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
class Slot;

class Graph : public Node
{
	private:
		
		typedef std::vector<Node*> NodeVec;
		/*! \brief Vector of Nodes
		 *
		 * Nodes inside the graph
		 */
		NodeVec m_nodes;


	public:
		/* \brief A constructor
		 *
		 *  Inject dependency to a DataBase object
		 */
		Graph()
		{
			m_type = nodeType::GRAPH;
		}
		/* \brief Add node to the Graph from the Database
		 *
		 * \param _name name of the node to add
		 */
		void addNode(Node *_n);

		/* \brief Returns and iterator to the first element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeVec::const_iterator NodeBegin() const; 
		/* \brief Returns and iterator to the last element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeVec::const_iterator NodeEnd() const;
		/* \brief Returns and iterator to the last element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		typedef NodeVec::const_iterator nodeiterator;
		/* \brief Add a input slot to the graph
		 *
		 */
		Node *getNode(const std::string &_name, int id);
		//! \brief Prototype Pattern
		virtual Graph *clone();
};

#endif
