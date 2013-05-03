#include "Node.h"
#include "Output.h"
#include "Input.h"
#include "Slot.h"

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#define MY_ENCODING "ISO-8859-1"


Node::Node()
	:m_name("empty")
{
}
Node::~Node()
{}

void Node::write(const std::string &_file)
{
	int rc;
	xmlTextWriterPtr writer;
	xmlDocPtr doc;
	xmlNodePtr node;
	doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	node = xmlNewDocNode(doc, NULL, BAD_CAST "root", NULL);
	xmlDocSetRootElement(doc, node);
	writer = xmlNewTextWriterTree(doc,node, 0); 
	rc = xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL);
	rc = xmlTextWriterStartElement(writer, BAD_CAST "node");
	for(Node::iterator i = begin(); i<end(); i++)
	{
		rc = xmlTextWriterStartElement(writer, BAD_CAST "slot");
		if((*i)->isInput())
		{
			xmlTextWriterWriteAttribute(writer, BAD_CAST "name", BAD_CAST "INPUT");
			xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST "asd");
			xmlTextWriterWriteAttribute(writer, BAD_CAST "var", BAD_CAST "asd");

			rc = xmlTextWriterStartElement(writer, BAD_CAST "source");
			Output *out = ((Input*)(*i))->getLink();
			//const char* c = out->getName().c_str();
			//std::cout<<c<<'\n';
		//	xmlTextWriterWriteAttribute(writer, BAD_CAST "name", BAD_CAST (const xmlChar*));
			rc = xmlTextWriterEndElement(writer);
		}
		rc = xmlTextWriterEndElement(writer);
		//rc = xmlTextWriterEndElement(writer);
	}
	//	rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "version",
	//			BAD_CAST "1.0");

	rc = xmlTextWriterEndElement(writer);
	xmlFreeTextWriter(writer);

	//const char *file = "asd.xml";

	xmlSaveFormatFileEnc(_file.c_str(), doc, MY_ENCODING, 1); 
	xmlCleanupParser();
	xmlMemoryDump();

}

/*
   Slot *Node::getSlot(const std::string &_name)
   {
   std::vector<Slot*>::iterator it;
   for (it = m_slots.begin(); it != m_slots.end(); ++it)
   {
   Slot *s = *it;
   if(s->getName() == _name)
   {
   return s;
   }
   }
   static Slot empty;
   return &empty;
   }
   */
/*
   void Node::addOutputSlot(Slot *_in)
   {
   m_outputSlots.push_back(_in);
   }

   Node *Node::clone() const 
   {
   return new Node(*this);
   }

*/
std::string Node::getName() const
{
	return m_name;
}

void Node::setName(const std::string &_name)
{
	m_name = _name;
}

