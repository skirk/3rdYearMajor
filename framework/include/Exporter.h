/*  \author Tuomo Rinne
 *  \version 0.1
 *  \date 20/04/2013 
 *  \class XMLExporter
 *  \brief XMLExporter is responsible for transferring the object structures into a XML document
 */


#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <vector>
#include <map>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

class Node;
class Slot;

typedef std::vector<Slot*> HeaderStruct;
typedef std::map<const Node*, std::string> ConstantMap;

class XMLExporter
{
	private:
		//! /brief the document which is to be written
		xmlDocPtr m_doc;
		//! /brief current node
		xmlNodePtr m_node;
		//! /brief The writer object
		xmlTextWriterPtr m_writer;
		//! /brief location where to write
		std::string m_file;
		/*! /brief map to hold values for constants
		 * 
		 * /note a duct tape solution
		 */
		ConstantMap *m_map;

	private:
		
		/* \brief Write slot attributes into XML
		 *
		 * \param _name name of the slot
		 * \param _type type of the slot
		 * \param _var variable of the slot
		 */
		void writeSlotAttributes(const std::string &_name, const std::string &_type, const std::string &_var);
		/* \brief Write Element into XML
		 *
		 * \param _sourcenode name of the source
		 * \param _id id of the source
		 * \param _sourceslot slot of the source
		 */
		void writeSourceElement(const std::string &_sourcenode, const std::string &_id, const std::string &_sourceslot, const std::string &_value="");
		/* \brief Write State into XML
		 *
		 * \param _node node to write
		 *
		 */
		void writeState(const Node *_n);
		/* \brief Write Slots into XML
		 *
		 * \param _n node to write
		 */
		void writeSlots(const Node *_n);

	public:
		/* \brief Constructor
		 */
		XMLExporter(ConstantMap *_map);
		/* \brief open a file and set up the writer
		 *
		 * \param _name path to the output
		 * \param _element the opening element
		 */
		void open(const std::string &_name, const std::string &_element);
		/* \brief close up the writer
		 */
		void close();
		/* \brief Write Node into XML
		 *
		 * \param _n node to write
		 */
		void write(const Node *_n);
		/* \brief Write Header into XML
		 *
		 * \param _h Header to write
		 * \param _type the tag to write
		 */
		void writeHeader(const HeaderStruct &_header, const std::string &_type);
};


#endif
