#include "NodeFactory.h"
#include "DataBase.h"
#include "FileInterface.h"
#include "Parser.h"

#include <memory>
#include <iostream>

const char* NodeFactory::SHEET="sheet";
const char* NodeFactory::NAME="name";
const char* NodeFactory::NODE="node";


NodeFactory::NodeFactory()
{
	m_db = new DataBase();
	InitDB();
}

NodeFactory::~NodeFactory()
{
	delete m_db;
}

DataBase *NodeFactory::getDB()
{ 
	return m_db; 
}

void NodeFactory::InitDB()
{
	std::unique_ptr <Parser> p(new Parser());
	std::unique_ptr <FileInterface<xmlDocPtr>> file(new FileInterface<xmlDocPtr>());
	std::vector<xmlDocPtr> docvec = file->loadFolder(xmlParseFile, "nodes/nodes");
	xmlDocPtr schema = file->loadFile(xmlParseFile, "nodes/schemas/schema.xml");

	xmlNodePtr cur;
	for(unsigned int i = 0; i < docvec.size(); i++)
	{
		if (p->validateAgainstSchema(docvec[i], schema) == 1);
		{
			cur = xmlDocGetRootElement(docvec[i]);
			while(cur != NULL) {
				if(!xmlStrcmp(cur->name, (const xmlChar *)NODE))
				{
					addNodeToDB(docvec[i], cur);
				}
				cur = cur->next;
			}
		}
		xmlFreeDoc(docvec[i]);
	}
	
	xmlFreeDoc(schema);
}

void NodeFactory::addNodeToDB(xmlDocPtr _doc, xmlNodePtr _cur) const
{
	std::unique_ptr <Parser> p (new Parser());
	xmlChar *name = p->parseAttribute(_cur, NAME);
	xmlChar *key = p->parseAttribute(_cur, SHEET);
	if (key==NULL)
	{
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
		std::cout<<"Failed to parse "<<name<<"'s stylesheet"<<'\n';
		xmlFree(name);
		xmlFree(key);
		return;

	}
	std::cout<<"keyword: "<<key<<'\n';

	xmlFree(name);
	xmlFree(key);
	m_db->addNode(p->parseNode(_doc, _cur));
}
