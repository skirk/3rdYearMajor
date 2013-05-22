#include "Parser.h"
#include "Node.h"
#include "Graph.h"
#include "Slot.h"
#include "EnumParser.h"
#include "Enum.h"
#include "Util.h"
#include <cstring>
#include <libxml/xmlschemas.h>
#include <iostream>

const char* Parser::NODESLOTS = "slots";
const char* Parser::NODE = "node";
const char* Parser::NODEOUTPUTS = "outputs";
const char* Parser::NODESLOT = "slot";
const char* Parser::SLOTSOURCE = "source";


Node* Parser::parseNode(const xmlDocPtr &_doc, xmlNodePtr _cur, std::map<std::string, std::string> *_map)
{ 
	EnumParser<nodeType> ep;
	std::string name = (const char*)parseAttribute(_cur, "name");
	std::string type = (const char*)parseAttribute(_cur, "type");
	std::string id = (const char*)parseAttribute(_cur, "id");
	nodeType t = ep.parseEnum(type.c_str());
	Node *temp;
	std::map<std::string, std::string> connectionMap;
	_cur = _cur->children;
	if(t == nodeType::GRAPH)
	{
		std::cout<<"node type is graph"<<'\n';
		Graph *temp2 = new Graph();
		temp2->setName(name);
	//	temp2->setID(std::stoi(id));
		printElementNames(_cur);
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) 
			{
				if ( _map == NULL)
				{	
					temp2->add(parseSlot(temp2, _doc, _cur, &connectionMap));
				}
				else
				{
					temp2->add(parseSlot(temp2, _doc, _cur, _map));
				}

			}
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODE))
			{
				Node *n = parseNode(_doc, _cur, &connectionMap);
				temp2->addNode(n);
				std::cout<<"added node "<<n->getName()<<"address "<<n<<" ID "<<n->getID()<<'\n';
			}
			_cur = _cur->next;
		}
		if(connectionMap.begin() != connectionMap.end())
		{
			std::map <std::string, std::string>::const_iterator it;
			for(it = connectionMap.begin(); it != connectionMap.end(); it++)
			{
				std::cout<<"connection map "<<it->first<<"  "<<it->second<<'\n';
				makeConnection(temp2, it->first, it->second);
			}
		}
		temp = temp2;
	}
	else
	{
		temp = new Node();
		temp->setName(name);
		//temp->setID(std::stoi(id));
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) {
				temp->add(parseSlot(temp, _doc, _cur, _map));
			}
			_cur = _cur->next;
		}
	}

	temp->setType(t);
	std::cout<<"parsing node "<<name<<"address "<<temp<<" ID "<<temp->getID()<<'\n';
	return temp;
}

Slot* Parser::parseSlot(Node *_parent,const xmlDocPtr &_doc, xmlNodePtr _cur, std::map<std::string, std::string> *_map)
{
	Slot *s = 0;
	xmlChar *name,*type, *var; 
	name = parseAttribute(_cur, "name");
	type = parseAttribute(_cur,  "type");
	var = parseAttribute(_cur,  "var");
	EnumParser<SVariable> p;
	EnumParser<Stype> p2;
	s = new Slot(
			_parent,
			(const char*)name,
			p2.parseEnum((const char*)type),
			p.parseEnum((const char*)var)
			);
	_cur=_cur->children;
	while(_cur !=NULL)
	{
		if(!xmlStrcmp(_cur->name, (const xmlChar *)SLOTSOURCE))
		{
			std::cout<<"in source slot"<<'\n';
			std::string output, input;
			input = _parent->getName()+"."+ _parent->getID()+"."+ (char *)name;
			output = parseSource(_cur, _map);
			_map->insert(std::pair<std::string, std::string>(input, output));
		}
		_cur=_cur->next;
	}
	xmlFree(name);
	xmlFree(type);
	xmlFree(var);
	return s;
}


std::string Parser::parseSource(xmlNodePtr _cur, std::map<std::string, std::string> *_connections)
{
	std::string output;
	xmlChar *sourcenode, *sourceid, *sourceslot;
	sourcenode = parseAttribute(_cur, "node");
	sourceid = parseAttribute(_cur, "id");
	sourceslot = parseAttribute(_cur,  "slot");
	output = (char*)sourcenode;
	std::cout<<output<<'\n';
	output += ".";
	output += (char*)sourceid;
	output += ".";
	output += (char*)sourceslot;
	std::cout<<output<<'\n';
	return output;
}

xmlChar* Parser::parseAttribute(xmlNodePtr _cur, const char* _key)
{
	xmlChar *key;
	key = xmlGetProp(_cur, (const xmlChar*)_key);
	if(key == NULL)
		return NULL;
	return key;
}

xmlChar* Parser::parseElement(const xmlDocPtr &_doc, xmlNodePtr _cur, const char* _key)
{
	_cur = _cur->xmlChildrenNode;
	xmlChar *key;
	while (_cur != NULL) {
		if ((!xmlStrcmp(_cur->name, (const xmlChar *)_key))) {
			key = xmlNodeListGetString(_doc, _cur->xmlChildrenNode, 1);
		}
		_cur = _cur->next;
	}
	return key;
}

void Parser::printElementNames(xmlNodePtr _cur)
{
	xmlNode *cur_node = NULL;
	for (cur_node = _cur; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE)
		{
			std::cout<<"nodename "<< cur_node->name <<'\n';
		}
		printElementNames(cur_node->children);
	}
}

//this schema validation code is taken from http://wiki.njh.eu/XML-Schema_validation_with_libxml2 this code
int Parser::validateAgainstSchema(const xmlDocPtr &_doc,const xmlDocPtr &_schema )
{
	xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewDocParserCtxt(_schema);
	if (parser_ctxt == NULL) {
		/* unable to create a parser context for the schema */
		xmlFreeDoc(_schema);
		return -1;
	}
	xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
	if (schema == NULL) {
		/* the schema itself is not valid */
		xmlSchemaFreeParserCtxt(parser_ctxt);
		xmlFreeDoc(_schema);
		return -2;
	}
	xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
	if (valid_ctxt == NULL) {
		/* unable to create a validation context for the schema */
		xmlSchemaFree(schema);
		xmlSchemaFreeParserCtxt(parser_ctxt);
		xmlFreeDoc(_schema);
		return -3; 
	}
	int is_valid = (xmlSchemaValidateDoc(valid_ctxt, _doc) == 0);
	xmlSchemaFreeValidCtxt(valid_ctxt);
	xmlSchemaFree(schema);
	xmlSchemaFreeParserCtxt(parser_ctxt);
	/* force the return value to be non-negative on success */
	return is_valid ? 1 : 0;
}


void Parser::makeConnection(Graph *_g,std::string _input, std::string _output)
{
	Slot *in = Utilities::findSlot(_g, _input);
	Slot *out = Utilities::findSlot(_g, _output);
	if(in->getName() != "empty" && out->getName() != "empty")
	{
		in->linkToSlot(out);
		return;
	}
	std::cout<<"something went wrong\n";

}
