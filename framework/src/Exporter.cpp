#include "Exporter.h"
#include "Node.h"
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#define MY_ENCODING "ISO-8859-1"


void XMLExporter::writeNode(Node _n, const std::string &_file)
{
	int rc;
	xmlTextWriterPtr writer;
	xmlDocPtr doc;
	xmlNodePtr node;
	doc = xmlNewDoc(BAD_CAST XML_DEFAULT_VERSION);
	node = xmlNewDocNode(doc, NULL, BAD_CAST "NODE", NULL);
	xmlDocSetRootElement(doc, node);
	writer = xmlNewTextWriterTree(doc,node, 0); 
	rc = xmlTextWriterStartDocument(writer, NULL, MY_ENCODING, NULL);
	rc = xmlTextWriterStartElement(writer, BAD_CAST "EXAMPLE");
	for(Node::iterator i = _n.begin(); i<_n.end(); i++)
	{
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "SLOT",
				"asdasd", "asd");
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
