/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 15/04/2013 Initialisation 
 *  \class Parser
 *  \brief Parser class creates reads in xml and stylesheet documents
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <libxml/tree.h>
#include <map>
#include <string>

class Graph;
class Node;
class Slot;

class Parser
{
	public: 
		//! Few variables to store document constants
		//@{
		static const char* NODE;
		static const char* NODESLOT;
		static const char* NODESLOTS;
		static const char* NODEOUTPUTS;
		static const char* SLOTSOURCE;
		//@}
	private:
		void makeConnection(Graph *_g, std::string input, std::string output);
		Node *getNodeFromString(Graph *_g, const std::string &_name);
	public:
		/*! \brief ParseNode from given document and xmlNode.
		 *
		 * \param _doc document to parse
		 * \param _node node structure to iterate through
		 */
		Node* parseNode(const xmlDocPtr &_doc, xmlNodePtr _node, std::map<std::string, std::string> *_map=0);
		/*! \brief ParseSLot from given document and xmlNode.
		 *
		 * \param _doc document to parse
		 * \param _node node structure to iterate through
		 */
		Slot* parseSlot(Node *_in, const xmlDocPtr &_doc, xmlNodePtr _node, std::map<std::string, std::string> *_map = 0);
		/*! \brief Parse a attribute out of node if any
		 * 
		 * \param _cur node to parse
		 * \param _key attribute to look for
		 */
		xmlChar* parseAttribute(xmlNodePtr _cur, const char* _key);
		/*! \brief Parse a element value
		 * 
		 * \param _cur node to parse
		 * \param _key element name
		 */
		xmlChar* parseElement(const xmlDocPtr &_doc, xmlNodePtr _cur, const char* _key);
		int validateAgainstSchema(const xmlDocPtr &_doc, const xmlDocPtr &_schema);
		/*! \brief Print all top and child elements of given Node.
		 * 
		 * \param _node node structure to iterate through
		 */
		void printElementNames(xmlNodePtr _node);
		/*! \brief Print all top and child elements of given Node.
		 * 
		 * \param _node node structure to iterate through
		 */

};


#endif
