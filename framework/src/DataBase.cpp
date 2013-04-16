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
			{
				addNode(docvec[i], cur);
			}
			cur = cur->next;
		}
		xmlFreeDoc(docvec[i]);
	}
	delete p;
	delete file;
}


void DataBase::addNode(xmlDocPtr _doc, xmlNodePtr _cur)
{
	Parser *p = new Parser();
	xmlChar *key;
	key = p->parseAttribute(_cur, "style");
	if (key==NULL)
	{
		xmlChar *name = p->parseAttribute(_cur, "name");
		if(name==NULL)
		{
			std::cout<<"Unknown node\n";
			xmlFree(name);
			return;
		}
		std::cout<<"Node "<<name<<" doesn't have a stylesheet"<<'\n';
		xmlFree(name);
		return;
	}
	std::cout<<"keyword: "<<key<<'\n';
	m_nodes.push_back(*p->parseNode(_doc, _cur));
	xmlFree(key);
	delete p;
}
