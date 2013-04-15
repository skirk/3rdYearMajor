#include "DataBase.h"
#include "FileInterface.h"
#include "Parser.h"
#include <iostream>

DataBase::DataBase()
{

	FileInterface<xmlDocPtr> *file = new FileInterface<xmlDocPtr>();
	Parser *p = new Parser();

	std::vector<xmlDocPtr> docvec = file->loadFolder(xmlParseFile, "nodes");

	xmlNodePtr cur;
	for(unsigned int i = 0; i < docvec.size(); i++)
	{
		cur = xmlDocGetRootElement(docvec[i]);
		while(cur != NULL) {
			if(!xmlStrcmp(cur->name, (const xmlChar *)"node"))
				m_nodes.push_back(*p->parseNode(docvec[i], cur));
			cur = cur->next;
		}
	}
	delete p;
	delete file;
}
