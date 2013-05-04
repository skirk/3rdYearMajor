#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <string>
class Node;
class XMLExporter
{
	public:
		void writeNode(Node *_n, const std::string &_file);
};

#endif
