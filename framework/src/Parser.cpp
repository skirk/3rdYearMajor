#include "Parser.h"
#include "Node.h"
#include "Slot.h"
#include "EnumParser.h"
#include "Enum.h"
#include <libxml/xmlschemas.h>
#include <iostream>

const char* Parser::NODEINPUTS = "inputs";
const char* Parser::NODEOUTPUTS = "outputs";
const char* Parser::NODESLOT = "slot";

Node* Parser::parseNode(const xmlDocPtr &_doc, xmlNodePtr _cur)
{ 
	_cur = _cur->xmlChildrenNode;
	Node *temp = new Node();
	while(_cur != NULL) {
		//compare first argument to the latter 
		if(!xmlStrcmp(_cur->name, (const xmlChar *)NODEINPUTS)) {
			std::cout<<"nodename "<< _cur->name <<'\n';
			temp->addInputSlot(*parseSlot(_doc, _cur));
		}
		if(!xmlStrcmp(_cur->name, (const xmlChar *)NODEOUTPUTS)) {
			std::cout<<"nodename "<< _cur->name <<'\n';
			temp->addOutputSlot(*parseSlot(_doc, _cur));
		}
		_cur = _cur->next;

	}
	return temp;

}

Slot* Parser::parseSlot(const xmlDocPtr &_doc, xmlNodePtr _cur)
{
	xmlChar *name,*type, *var; 
	Slot *temp = 0;
	_cur = _cur->xmlChildrenNode;
	while(_cur != NULL) {
		if(!xmlStrcmp(_cur->name, (const xmlChar *)NODESLOT)) {
			name = parseElement(_doc, _cur, "name");
			type = parseElement(_doc, _cur,  "type");
			var = parseElement(_doc, _cur,  "var");
			EnumParser<SlotVar> p;
			//bitwise or to determine whether a input or output variable
			temp = new Slot(
					(const char*)name,
					p.parseEnum((const char*)type) |
					p.parseEnum((const char*)var)
					);

		}
		_cur = _cur->next;
	}
	xmlFree(name);
	xmlFree(type);
	xmlFree(var);
	return temp;
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
			printf("keyword: %s\n", key);
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




