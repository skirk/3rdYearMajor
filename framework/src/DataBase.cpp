#include "DataBase.h"
#include "FileInterface.h"
#include <libxslt/xsltutils.h>
#include "Parser.h"
#include <iostream>

const char* DataBase::SHEET="sheet";
const char* DataBase::NAME="name";
const char* DataBase::NODE="node";

DataBase::DataBase()
{
	FileInterface<xmlDocPtr> *file = new FileInterface<xmlDocPtr>();
	std::vector<xmlDocPtr> docvec = file->loadFolder(xmlParseFile, "nodes/nodes");
	xmlDocPtr schema = file->loadFile(xmlParseFile, "nodes/schemas/schema.xml");

	Parser *p = new Parser();
	xmlNodePtr cur;
	for(unsigned int i = 0; i < docvec.size(); i++)
	{
		if (p->validateAgainstSchema(docvec[i], schema) == 1);
		{
			cur = xmlDocGetRootElement(docvec[i]);
			while(cur != NULL) {
				if(!xmlStrcmp(cur->name, (const xmlChar *)NODE))
				{
					addNode(docvec[i], cur);
				}
				cur = cur->next;
			}
		}
		xmlFreeDoc(docvec[i]);
	}
	xmlFreeDoc(schema);
	delete file;
}

void DataBase::addNode(xmlDocPtr _doc, xmlNodePtr _cur)
{
	Parser *p = new Parser();
	xmlChar *key;
	key = p->parseAttribute(_cur, SHEET);
	if (key==NULL)
	{
		xmlChar *name = p->parseAttribute(_cur, NAME);
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
	FileInterface<xmlDocPtr> *file = new FileInterface<xmlDocPtr>();
	file->changeContext("nodes/stylesheets/");
	if (file->loadFile(xmlParseFile, (const char*)key) == NULL)
	{
		xmlChar *name = p->parseAttribute(_cur, NAME);
		std::cout<<"Failed to parse "<<name<<"'s stylesheet"<<'\n';
		xmlFree(name);
		return;

	}
	std::cout<<"keyword: "<<key<<'\n';
	m_nodes.push_back(*p->parseNode(_doc, _cur));
	xmlFree(key);
	delete p;
}
