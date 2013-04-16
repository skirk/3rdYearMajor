//! A DataBase Class
/*!
  Database holds are the nodes that are accessible to the user
  */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>

#include <libxml/tree.h>

#ifndef _NODE_H_
#include "Node.h"
#endif

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
		void addNode(xmlDocPtr _doc, xmlNodePtr _cur);
	private:
		std::vector<Node> m_nodes;

};
#endif
