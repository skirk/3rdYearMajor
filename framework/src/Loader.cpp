#include "Loader.h"
#include "Node.h"
#include <iostream>
#include <cstring>
#include <dirent.h>
#include <libxml/xmlreader.h>

Loader::Loader()
{
	loadFiles();
    m_current = 0;
    m_size = 5;
}


Loader::~Loader()
{
}

void Loader::printElementNames(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			std::cout<<"nodename "<< cur_node->name <<'\n';
		}

		printElementNames(cur_node->children);
	}
}

void Loader::loadFiles()
{
	DIR *dp;
    struct dirent *ep;
    std::string path = "./nodes";
    std::string fullpath;
    dp = opendir(path.c_str());
    if(dp != NULL)
    {
        while (ep = readdir(dp))
            if(strstr(ep->d_name, ".xml"))
            {
                std::cout<< ep->d_name <<"\n";
                fullpath = path;
                fullpath = fullpath +"/"+ ep->d_name;
                std::cout<<fullpath<<'\n';
				xmlDocPtr result;
                result = parseFile(fullpath.c_str());
				if (result == NULL)
				{
					std::cout<<"File failed to parse"<<'\n';
				}
				else{
					createNode(result);
				}
            }
        (void) closedir(dp);
    }
    else
        std::cout<<"couldn't open the directory\n";
}

void Loader::createNode(const xmlDocPtr &_doc)
{
	xmlNode * rootElement = NULL;
	rootElement = xmlDocGetRootElement(_doc);

	printElementNames(rootElement);

}



/*
   void Loader::parseFile(const char *_filename) {
   xmlTextReaderPtr reader;
   int ret;

   reader = xmlReaderForFile(_filename, NULL,
   XML_PARSE_DTDATTR |
   XML_PARSE_NOENT |
   XML_PARSE_DTDVALID);
   if (reader != NULL) {
   ret = xmlTextReaderRead(reader);
   }

   while (ret ==1) {
   ret = xmlTextReaderRead(reader);
   }

   if(xmlTextReaderIsValid(reader) != 1) {
   std::cout<<"Document" <<_filename<<" does not validate\n";
   }
   xmlFreeTextReader(reader);
   if(ret != 0) {

   std::cout<<_filename<<" failed to parse\n";
   }
   else {

   std::cout<<_filename<<" unable to open\n";

   }
   }
   */
xmlDocPtr Loader::parseFile(const char *_filename) { 
	xmlDocPtr doc; 
	doc = xmlReadFile(_filename, NULL, 0); 
	return doc;
}

void Loader::operator++()
{
	m_current++;
}

bool Loader::isEnd()
{
	if(m_current < m_size)
	{
		return false;
	}
	else
		return true;
}

