#include "Node.h"
#include "Output.h"
#include "Input.h"
#include "Slot.h"

#include <sstream>

Node::Node() :
	m_name("empty")
{
	m_id = 0;
}
Node::~Node()
{}

Node::Node(const Node &_n)
{
	m_name = _n.getName(); 
	m_id = std::stoi(_n.getID());
	for(iterator it =_n.begin(); it != _n.end(); it++)
	{
		std::cout<<"copying node slots" <<(*it)->getName()<<'\n';
		m_elems.push_back((*it)->clone()); 
		std::cout<<m_elems.back()->getName()<<'\n';
	}
}

void Node::write(const std::string &_file)
{
	/*
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

			Input* in = dynamic_cast<Input*>(*i);
			bool test = in->isOverwritten();
			std::cout<<test<<'\n';
			if (in->isOverwritten())
			{
				rc = xmlTextWriterStartElement(writer, BAD_CAST "source");
				Output *out = in->getLink();
				xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST out->getName().c_str());
				std::string c = out->getName();
				std::cout<<c<<'\n';
				rc = xmlTextWriterEndElement(writer);
			}
			//	xmlTextWriterWriteAttribute(writer, BAD_CAST "name", BAD_CAST (const xmlChar*));
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

*/
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
void Node::setID(int _id)
{
	std::cout<<"changing from "<<m_id<<" to "<<_id<<'\n';
	m_id = _id;
}

std::string Node::getID() const
{
	std::ostringstream convert;
	convert << m_id;
	return convert.str();
}
nodeType Node::getType()
{
	return m_type;
}
