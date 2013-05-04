#include "Exporter.h"
#include "Node.h"
#include "Graph.h"
#include "Input.h"
#include "Output.h"
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#define MY_ENCODING "ISO-8859-1"


void XMLExporter::writeNode(Node *_n, const std::string &_file)
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
	for(Node::iterator i = _n->begin(); i<_n->end(); i++)
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
				std::cout<<"whee\n";
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
	if(_n->getType() == nodeType::GRAPH)
	{
		Graph *g = dynamic_cast<Graph*>(_n);
		if (g != NULL)
		{
			Graph::nodeiterator it = g->NodeBegin() ; 
			std::cout<<"inside graph writing\n";
			for(; it != g->NodeEnd(); ++it)
				writeNode(*it, _file);
		}
	}

	rc = xmlTextWriterEndElement(writer);
	xmlFreeTextWriter(writer);

	xmlSaveFormatFileEnc(_file.c_str(), doc, MY_ENCODING, 1); 
	xmlCleanupParser();
	xmlMemoryDump();
}
