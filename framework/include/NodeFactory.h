/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 18/04/2013 
 *  \class NodeFactory
 *  \brief NodeFactory is a singleton class responsible for being a interface for the DataBase
 */

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
		static const char* ROOT;

	public:
		
		/*! \brief get a Pointer to the DataBase 
		 *
		 */
		DataBase* getDB();
		/*! \brief Factory method for creating Nodes
		 *
		 * If the node exists in the DataBase return it, if not create a new one.
		 *
		 * \param _name name of the node
		 * \param _type type of the node
		 */
		Node *createNode(const std::string &_name, const nodeType &_type);


		/*! \brief get Instance of the factory
		 *
		 */
		static NodeFactory &getInstance();
		
		/*! \brief initialise DataBase
		 *
		 *  Load up all the nodes in the ./nodes folder and create corresponding objects
		 */
		void InitDB();

	private:
		/*! \brief A private constructor
		 *
		 * The constructor calls InitDB which initialises the database according to the nodes in the folder
		 */
		NodeFactory();
		/*! \brief A private destructor
		 *
		 * The destructor deletes the DataBase
		 */
		~NodeFactory();
		//! \brief A private copy constructor
		NodeFactory(const NodeFactory&);
		//! \brief A privat assignment operator
		const NodeFactory &operator=(const NodeFactory&);
		//! \brief Instance of the factory
		static NodeFactory *m_instance;
		//! \brief The DataBase
		DataBase *m_db;
		/*! \brief Add Node to DataBase
		 *
		 * \param _doc The document to read
		 * \param _cur current Node in document
		 */
		void addNodeToDB(xmlDocPtr _doc, xmlNodePtr _cur) const;
};

#endif
