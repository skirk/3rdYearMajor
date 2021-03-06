#include "Exporter.h"
#include "EnumParser.h"
#include "Node.h"
#include "Graph.h"
#include "Slot.h"
#include "Context.h"

#include <cstring>
#define MY_ENCODING "ISO-8859-1"

/*
 * From API m_documentation:
 * Macro: BAD_CAST
 * #define BAD_CAST
 * Macro to cast a string to an xmlChar * when one know its safe.
 */
XMLExporter::XMLExporter(ConstantMap *_map)
{
	m_map = _map;
}

void XMLExporter::open(const std::string &_filename, const std::string &_element)
{
	m_doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	m_node = xmlNewDocNode(m_doc, NULL, BAD_CAST "root", NULL);
	xmlDocSetRootElement(m_doc, m_node);
	m_writer = xmlNewTextWriterTree(m_doc,m_node, 0); 
	xmlTextWriterStartDocument(m_writer, NULL, MY_ENCODING, NULL);
//	xmlTextWriterStartElement(m_writer, BAD_CAST _element.c_str());
	m_file = _filename;
}

void XMLExporter::close()
{
	//xmlTextWriterEndElement(m_writer);
	xmlFreeTextWriter(m_writer);
	xmlSaveFormatFileEnc(m_file.c_str(), m_doc, MY_ENCODING, 1); 
	xmlCleanupParser();
	xmlMemoryDump();
}
void XMLExporter::writeSlotAttributes(const std::string &_name, const std::string &_var)
{
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "name", BAD_CAST _name.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "var", BAD_CAST _var.c_str());
}

void XMLExporter::writeSourceElement(const std::string &_sourcenode, const std::string &_id, const std::string &_sourceslot, const std::string &_value)
{
	xmlTextWriterStartElement(m_writer, BAD_CAST "source");
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "node", BAD_CAST _sourcenode.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "id", BAD_CAST _id.c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "slot", BAD_CAST _sourceslot.c_str());
	/*
	if (_value != "")
	{
		xmlTextWriterWriteAttribute(m_writer, BAD_CAST "value", BAD_CAST _value.c_str());
	}
	*/
	xmlTextWriterEndElement(m_writer);
}

void XMLExporter::openAndWriteNode(const Node *_n, const char *_key)
{
	xmlTextWriterStartElement(m_writer, BAD_CAST _key);
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "name", BAD_CAST _n->getName().c_str());
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "id", BAD_CAST _n->getID().c_str());
	EnumParser<nodeType> p;
	xmlTextWriterWriteAttribute(m_writer, BAD_CAST "type", BAD_CAST p.lookupEnum(_n->getType()).c_str());

}

void XMLExporter::write(const Node *_n, const char *_key) 
{
	openAndWriteNode(_n, _key);
	switch (_n->getType())
	{
		case nodeType::STATE:
			{
				writeSlots(_n,"input","output");
				break;
			}

		case nodeType::OPERATOR:
			{
				writeSlots(_n,"input","output");
				break;
			}
		case nodeType::FUNCTION:
			{
				writeSlots(_n,"input","output");
				break;
			}

		case nodeType::GRAPH:
			{
				if(!strcmp(_key, "shader"))
				{
					writeSlots(_n,"import","export");
					writeHeader(m_uniforms, "uniforms");
				}
				else
				{
					writeSlots(_n,"input","output");
				}
				const Graph *g = dynamic_cast<const Graph*>(_n);
				if (g != NULL){

					Graph::nodeiterator it = g->nodeBegin() ; 
					for(; it != g->nodeEnd(); ++it) {
						write(*it, "node");
					}
				}
				break;
			}
		case nodeType::CONSTRUCTOR:
			{
				writeSlots(_n,"input","output");
				break;
			}
		case nodeType::CONSTANT:
			{
				writeSlots(_n,"input","output");
				break;
			}
		case nodeType::BRANCH:
			{
				writeSlots(_n,"input","output");
				break;
			}
	}
	xmlTextWriterEndElement(m_writer);
}

void XMLExporter::writeSlots(const Node *_n, const char *_inputkey, const char *_outputkey)
{
	int rc;
	for(Node::iterator i = _n->begin(); i<_n->end(); i++)
	{
		std::cout<<"in writing node"<<'\n';
		std::cout<<(*i)->getName()<<'\n';
		if((*i)->isInput())
		{
			rc = xmlTextWriterStartElement(m_writer, BAD_CAST _inputkey);
			writeSlotAttributes((*i)->getName(), (*i)->getVar());
			std::cout<<(*i)->isOverwritten()<<'\n';

			if ((*i)->isOverwritten())
			{
				Slot *out = (*i)->getLink();
				/*
				if(out->getParent()->getType() == nodeType::CONSTANT)
				{
					std::cout<<"writing constant node"<<'\n';
					Slot *out = (*i)->getLink();

					ConstantMap::const_iterator it;
					for(it = m_map->begin(); it != m_map->end(); it++)
					{
						std::cout<<it->first->getName()<<'\n';
						std::cout<<it->first<<'\n';
						std::cout<<out->getParent()->getName()<<'\n';
						std::cout<<out->getParent()<<'\n';
					}
					it = m_map->find(out->getParent());
					if(it != m_map->end())
					{
						std::cout<<"inside source element\n";
						writeSourceElement(
								out->getParent()->getName(),
								out->getParent()->getID(),
								out->getName(),
								it->second.c_str());
					}
				}
				*/
				writeSourceElement(
						out->getParent()->getName(),
						out->getParent()->getID(),
						out->getName());
			}
			rc = xmlTextWriterEndElement(m_writer);
		}
		else
		{
			rc = xmlTextWriterStartElement(m_writer, BAD_CAST _outputkey);
			writeSlotAttributes((*i)->getName(),(*i)->getVar());

			if ((*i)->isOverwritten())
			{
				Slot *out = (*i)->getLink();
				writeSourceElement(
						out->getParent()->getName(),
						out->getParent()->getID(), 
						out->getName());
			}
			rc = xmlTextWriterEndElement(m_writer);
		}
	}
}

void XMLExporter::writeState(const Node *_n)
{
}

void XMLExporter::writeHeader(const HeaderStruct &_header, const std::string &_type)
{

	for(unsigned int i = 0; i <_header.size(); i++)
	{
		xmlTextWriterStartElement(m_writer, BAD_CAST _type.c_str());
		xmlTextWriterWriteAttribute(m_writer, BAD_CAST "name", BAD_CAST _header[i]->getName().c_str());
		xmlTextWriterWriteAttribute(m_writer, BAD_CAST "type", BAD_CAST _header[i]->getVar().c_str());
		xmlTextWriterWriteAttribute(
				m_writer,
				BAD_CAST "parent", 
				BAD_CAST _header[i]->getParent()->getName().c_str()
				);
		xmlTextWriterWriteAttribute(
				m_writer, 
				BAD_CAST "id",
				BAD_CAST _header[i]->getParent()->getID().c_str());
		xmlTextWriterEndElement(m_writer);
	}

}

void XMLExporter::setUniforms(const HeaderStruct &_header)
{
	m_uniforms = _header;
}
