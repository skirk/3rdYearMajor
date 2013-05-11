#include "Exporter.h"
#include "Node.h"
#include "Graph.h"
#include "Slot.h"
#define MY_ENCODING "ISO-8859-1"

/*
 * From API m_documentation:
 * Macro: BAD_CAST
 * #define BAD_CAST
 * Macro to cast a string to an xmlChar * when one know its safe.
 */
XMLExporter::XMLExporter()
{
}

void XMLExporter::open(const std::string &_filename)
{
	m_doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	m_node = xmlNewDocNode(m_doc, NULL, BAD_CAST "root", NULL);
	xmlDocSetRootElement(m_doc, m_node);
	m_writer = xmlNewTextWriterTree(m_doc,m_node, 0); 
	xmlTextWriterStartDocument(m_writer, NULL, MY_ENCODING, NULL);
	m_file = _filename;

}
void XMLExporter::close()
{
	xmlFreeTextWriter(m_writer);
	xmlSaveFormatFileEnc(m_file.c_str(), m_doc, MY_ENCODING, 1); 
	xmlCleanupParser();
	xmlMemoryDump();
}
void XMLExporter::writeSlotAttributes(const std::string &_name, const std::string &_type, const std::string &_var)
{
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "name", BAD_CAST _name.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "type", BAD_CAST _type.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "var", BAD_CAST _var.c_str());
}

void XMLExporter::writeSourceElement(const std::string &_sourcenode, const std::string &_id, const std::string &_sourceslot)
{
	xmlTextWriterStartElement(m_writer, BAD_CAST "source");
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "node", BAD_CAST _sourcenode.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "id", BAD_CAST _id.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "slot", BAD_CAST _sourceslot.c_str());
	xmlTextWriterEndElement(m_writer);
}

void XMLExporter::writeNode(const Node *_n)
{
	int rc;
	rc = xmlTextWriterStartElement(m_writer, BAD_CAST "node");
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "name", BAD_CAST _n->getName().c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "id", BAD_CAST _n->getID().c_str());
	for(Node::iterator i = _n->begin(); i<_n->end(); i++)
	{
		std::cout<<"in writing node"<<'\n';
		std::cout<<(*i)->getName()<<'\n';
		rc = xmlTextWriterStartElement(m_writer, BAD_CAST "slot");
		if((*i)->isInput())
		{
			writeSlotAttributes((*i)->getName(), "input", "var");
			std::cout<<(*i)->isOverwritten()<<'\n';
			if ((*i)->isOverwritten())
			{
				Slot *out = (*i)->getLink();

				writeSourceElement(out->getParent()->getName(), out->getParent()->getID() , out->getName());
			}
		}
		else
		{
			writeSlotAttributes((*i)->getName(), "output", "var");
		}
		rc = xmlTextWriterEndElement(m_writer);

	}
	if(_n->getType() == nodeType::GRAPH)
	{
		const Graph *g = dynamic_cast<const Graph*>(_n);
		if (g != NULL)
		{
			Graph::nodeiterator it = g->NodeBegin() ; 
			for(; it != g->NodeEnd(); ++it)
				writeNode(*it);
		}
	}
	rc = xmlTextWriterEndElement(m_writer);
}
