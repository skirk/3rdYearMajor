//! A DataBase Class
/*!
  Database holds are the nodes that are accessible to the user
  */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
#include <string>

class Node;

class DataBase
{
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

		typedef std::vector<Node*> NodeMap;
		NodeMap::iterator begin();
		NodeMap::iterator end();

		void addNode(Node *_n);
		const Node *getNode(const std::string &_name);

	private:
		NodeMap m_nodes;

};
#endif
