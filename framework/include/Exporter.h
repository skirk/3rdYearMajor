#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
class Node;
class XMLExporter
{
	private:
		xmlDocPtr m_doc;
		xmlNodePtr m_node;
		xmlTextWriterPtr m_writer;
		std::string m_file;
		void writeSlotAttributes(const std::string&, const std::string&, const std::string&);
		void writeSourceElement(const std::string&, const std::string&, const std::string&);
	public:
		void open(const std::string &_name);
		void close();
		XMLExporter();
		void writeNode(Node *_n);
};

#endif
