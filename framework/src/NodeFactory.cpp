#include "NodeFactory.h"
#include "DataBase.h"
#include "Graph.h"
#include "Node.h"
#include "Enum.h"
#include "FileInterface.h"
#include "Parser.h"

#include <memory>
#include <iostream>

const char* NodeFactory::SHEET="sheet";
const char* NodeFactory::NAME="name";
const char* NodeFactory::NODE="node";

NodeFactory* NodeFactory::m_instance = NULL;


NodeFactory::NodeFactory()
{
	m_db = new DataBase();
}

NodeFactory::~NodeFactory()
{
	delete m_db;
}

DataBase *NodeFactory::getDB()
{ 
	return m_db; 
}

Node *NodeFactory::createNode(const std::string &_name,  const nodeType &_type)
{
	Node *n = m_db->get(_name);
	//if Node exits return it
	if(n->getName() != "empty")
	{
		std::cout<<"adding "<<n->getName()<<'\n';
		
		for(Node::iterator it = n->begin(); it != n->end(); it++)
			std::cout<<(*it)->getName()<<'\n';
		
		return n;
	}
	n->setName(_name);
	switch(_type)
	{
		case nodeType::GRAPH:
		std::cout<<"adding empty"<<'\n';
			std::cout<<"constructing new node"<<'\n';
			n = new Graph();
			break;
		case nodeType::STATE:
			std::cout<<"STATE"<<'\n';
			break;
		case nodeType::EXPRESSION:
			std::cout<<"EXPRESSION\n";
			break; }
	return n;
}

void NodeFactory::InitDB()
{
	std::unique_ptr <Parser> p(new Parser());
	std::unique_ptr <FileInterface <xmlDocPtr> > file(new FileInterface<xmlDocPtr>());
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
		//std::cout<<"Node "<<name<<" doesn't have a stylesheet"<<'\n';
		xmlFree(name);
		return;
	}
	FileInterface<xmlDocPtr> *file = new FileInterface<xmlDocPtr>();
	file->changeContext("nodes/stylesheets/");
	if (file->loadFile(xmlParseFile, (const char*)key) == NULL)
	{
		//std::cout<<"Failed to parse "<<name<<"'s stylesheet"<<'\n';
		xmlFree(name);
		xmlFree(key);
		return;

	}
	//std::cout<<"keyword: "<<key<<'\n';

	m_db->add(p->parseNode(_doc, _cur));

	xmlFree(name);
	xmlFree(key);
}

NodeFactory &NodeFactory::getInstance()
{
	if(m_instance == NULL) {
		m_instance = new NodeFactory();
	}
	return *m_instance;
}
