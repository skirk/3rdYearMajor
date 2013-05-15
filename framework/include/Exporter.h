#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
class Node;
class HeaderStruct;

class XMLExporter
{
	private:
		xmlDocPtr m_doc;
		xmlNodePtr m_node;
		xmlTextWriterPtr m_writer;
		std::string m_file;
		void writeSlotAttributes(const std::string&, const std::string&, const std::string&);
		void writeSourceElement(const std::string&, const std::string&, const std::string&);
		void writeState(const Node *_n);
		void writeSlots(const Node *_n);
	public:
		void open(const std::string &_name);
		void close();
		void write(const Node *_n);
		void writeHeader(const HeaderStruct&);
		XMLExporter();
};

#endif
