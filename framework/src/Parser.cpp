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
	nodeType t = ep.parseEnum(type.c_str());
	Node *temp;
	_cur = _cur->xmlChildrenNode;

	if(t == nodeType::GRAPH)
	{
		std::cout<<"node type is graph"<<'\n';
		std::map<std::string, std::string> connectionMap;
		Graph *temp2 = new Graph();
		temp2->setName(name);
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) 
			{
				temp2->add(parseSlot(temp2, _doc, _cur, _map));
			}
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODE))
			{
				temp2->addNode(parseNode(_doc, _cur, &connectionMap));
			}
			_cur = _cur->next;
		}

		if(connectionMap.begin() != connectionMap.end())
		{
			std::map <std::string, std::string>::const_iterator it;
			for(it = connectionMap.begin(); it != connectionMap.end(); it++)
			{
				makeConnection(temp2, it->first, it->second);
			}
		}
		connectionMap.clear();

		temp = temp2;
	}
	else
	{
		temp = new Node();
		temp->setName(name);
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) {
				temp->add(parseSlot(temp, _doc, _cur));
			}
			_cur = _cur->next;
		}
	}

	temp->setType(t);
	return temp;
}

Slot* Parser::parseSlot(Node *_in,const xmlDocPtr &_doc, xmlNodePtr _cur, std::map<std::string, std::string> *_map)
{
	Slot *s = 0;
	xmlChar *name,*type, *var; 
	name = parseAttribute(_cur, "name");
	type = parseAttribute(_cur,  "type");
	var = parseAttribute(_cur,  "var");
	EnumParser<SVariable> p;
	if(!strcmp((const char*)type, "input")) 
	{
		s = new Slot(
				_in,
				(const char*)name,
				Stype::input,
				p.parseEnum((const char*)var)
				);

		xmlNodePtr cur2 = _cur->children;
		while(cur2 != NULL) {

			std::cout<<cur2->name<<'\n';
			if(!xmlStrcmp(cur2->name, (const xmlChar *)SLOTSOURCE)) 
			{
				std::string input, output;
				xmlChar *sourcenode, *sourceid, *sourceslot;
				sourcenode = parseAttribute(cur2, "node");
				sourceid = parseAttribute(cur2, "id");
				sourceslot = parseAttribute(cur2,  "slot");

				input = _in->getName()+"."+ _in->getID()+"."+ (char *)name;
				output = (char*)sourcenode;
				output += ".";
				output += (char*)sourceid;
				output += ".";
				output += (char*)sourceslot;
				_map->insert(std::pair<std::string, std::string>(input, output));
			}
			cur2 = cur2->next;
		}
	}
	else 
	{
		s = new Slot(
				_in,
				(const char*)name,
				Stype::output,
				p.parseEnum((const char*)var)
				);
	}

	xmlFree(name);
	xmlFree(type);
	xmlFree(var);
	_cur = _cur->next;
	return s;
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
		if (cur_node->type == XML_ELEMENT_NODE) {
			//std::cout<<"nodename "<< cur_node->name <<'\n';
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
