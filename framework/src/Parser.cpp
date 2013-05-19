#include "Parser.h"
#include "Node.h"
#include "Graph.h"
#include "Slot.h"
#include "EnumParser.h"
#include "Enum.h"
#include <cstring>
#include <libxml/xmlschemas.h>
#include <iostream>
const char* Parser::NODESLOTS = "slots";
const char* Parser::NODE = "node";
const char* Parser::NODEOUTPUTS = "outputs";
const char* Parser::NODESLOT = "slot";
const char* Parser::SLOTSOURCE = "source";

Node* Parser::parseNode(const xmlDocPtr &_doc, xmlNodePtr _cur)
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
		Graph *temp2 = new Graph();
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) 
			{
				temp2->add(parseSlot(temp2, _doc, _cur));
			}
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODE))
			{
				temp2->addNode(parseNode(_doc, _cur));
			}
			_cur = _cur->next;
		}
		temp = temp2;
	}
	else
	{
		temp = new Node();
		while(_cur != NULL) {
			if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) {
				temp->add(parseSlot(temp, _doc, _cur));
			}
			_cur = _cur->next;
		}
	}

	temp->setType(t);
	temp->setName(name);
	return temp;
}
/*
   while(_cur != NULL) {
//compare first argument to the latter 
if(!xmlStrcmp(_cur->name, (const xmlChar *)NODEINPUTS)) {
std::cout<<"adding to the node "<< _cur->name <<'\n';
temp->add(parseSlot(_doc, _cur));
}
if(!xmlStrcmp(_cur->name, (const xmlChar *)NODEOUTPUTS)) {
std::cout<<"adding to the node "<< _cur->name <<'\n';
temp->add(parseSlot(_doc, _cur));
}
_cur = _cur->next;

}
*/

Slot* Parser::parseSlot(Node *_in,const xmlDocPtr &_doc, xmlNodePtr _cur)
{
	//	std::cout<<"adding to the node "<< _cur->name <<'\n';
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
			if(!xmlStrcmp(cur2->name, (const xmlChar *)SLOTSOURCE)) {

				std::map<std::string, std::string> connections;

				std::string input, output;
				xmlChar *sourcenode, *sourceid, *sourceslot;
				sourcenode = parseAttribute(cur2, "node");
				sourceid = parseAttribute(cur2, "id");
				sourceslot = parseAttribute(cur2,  "slot");

				input = _in->getName() + (char *)name;
				output = (char*)sourcenode;
				//output += (char*)sourceid;
				output += (char*)sourceslot;
				std::cout<<input<<" "<<output<<'\n';

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
	/*
	//bitwise or to determine whether a input or output variable
	s = new Slot(
	(const char*)name,
	p.parseEnum((const char*)type) |
	p.parseEnum((const char*)var)
	);
	*/

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




