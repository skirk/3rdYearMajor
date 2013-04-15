/*
#include "Loader.h"
#include "FileInterface.h"
#include "Node.h"
#include <iostream>

Loader::Loader()
{
    parseFolder("nodes");
    m_current = 0;
    m_size = 5;
	xmlCleanupParser();
}


Loader::~Loader()
{
}



void Loader::loadFolder(const std::string &_location)
{
    FileInterface<xmlDocPtr> file;
	std::vector<xmlDocPtr> nodeDocuments = file.parseFolder(xmlParseFile, _location);
	for (unsigned int i = 0; i<nodeDocuments.size(); i++)
	{
		if(nodeDocuments[i] == NULL)
		{
			std::cout<<"oh no\n";
			continue;
		}
		createNode(nodeDocuments[i]);
	}
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
*/
