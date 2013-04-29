/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 29/03/2013 Initialisation 
 *  \class DataBase
 *  \brief DataBase collects all the defined nodes in the program and contains them
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
#include <string>

class Node;

class DataBase
{
	private:
		typedef std::vector<Node*> NodeMap;
		NodeMap m_nodes;
	public:
		/*! \brief A constructor
		 *
		 * Call for Loader class to generate all the nodes that have been implemented
		 */
		DataBase();
		/*! \brief add Node to database
		 *
		 * Call for Loader class to generate all the nodes that have been implemented
		 */
		void listNodes();

		/* \brief Returns and iterator to the first element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeMap::iterator begin();
		/* \brief Returns and iterator to the first element of m_nodes vector.
		 *
		 * This method is used by PythonWrapper to iterate through the vector
		 */
		NodeMap::iterator end();

		/* \brief Add node to the DataBase
		 *
		 * \param _n The node to add to the Database
		 */
		void addNode(Node *_n);
		/* \brief Get node from the DataBase
		 *
		 *
		 * \param _name  name of the node to get
		 */
		Node *getNode(const std::string &_name);


};
#endif
