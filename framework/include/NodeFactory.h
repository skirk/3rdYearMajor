#ifndef _NODEFACTORY_H_
#define _NODEFACTORY_H_

#include <libxslt/xsltutils.h>
#include <libxml/tree.h>
#include "Enum.h"
#include <string>

class Node;
class DataBase;

class NodeFactory
{
	public:

		static const char* SHEET;
		static const char* NAME;
		static const char* NODE;

	public:
		/*! \brief A constructor
		 *
		 * The constructor calls InitDB which initialises the database according to the nodes in the folder
		 */
		NodeFactory();
		/*! \brief A destructor
		 *
		 * The destructor deletes the DataBase
		 */
		~NodeFactory();
		/*! \brief get the Database of NodeFactory
		 *
		 * 
		 */
		DataBase* getDB();
		/*! \brief Factory method for creating Nodes
		 *
		 * 
		 */
		Node *createNode(const std::string &_name, const NodeType&);

	private:
		DataBase *m_db;
		void InitDB();
		void addNodeToDB(xmlDocPtr _doc, xmlNodePtr _cur) const;
};

#endif
