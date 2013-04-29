#include "FileInterface.h"
#include <libxml/parser.h>
#include <libxslt/xsltutils.h>
#include <iostream>
#include <dirent.h>
#include <cstring>

template<class T>
FileInterface<T>::FileInterface()
{
    m_context = "./";
}

template<class T>
FileInterface<T>::~FileInterface()
{
    xmlCleanupParser();
    xmlMemoryDump();
}

template <class T>
void FileInterface<T>::changeContext(const std::string &_context)
{
	m_context = _context;
}

template <class T>
T FileInterface<T>::loadFile(T (*parserFunction)(const char*), std::string _filename)
{
    std::string path = m_context + _filename;
    return parserFunction(path.c_str());;
}

template <class T>
std::vector<T> FileInterface<T>::loadFolder(T (*parserFunction)(const char*), std::string _foldername)
{
    DIR *dp;
    struct dirent *ep;
    std::string path = m_context + _foldername;
    std::string fullpath;
    std::vector<T> res;;
    dp = opendir(path.c_str());
    if(dp != NULL)
    {
        while ((ep = readdir(dp)))
            if(strstr(ep->d_name, ".xml"))
            {
                std::cout<< ep->d_name <<"\n";
                fullpath = path;
                fullpath = fullpath +"/"+ ep->d_name;
                std::cout<<fullpath<<'\n';
                T result;
                result = parserFunction(fullpath.c_str());
                if (result == NULL)
                {
                    std::cout<<"File failed to parse"<<'\n';
                }
                res.push_back(result);
            }
        (void) closedir(dp);
    }
    else
        std::cout<<"couldn't open the directory\n";

    return res;
}

template class FileInterface<xmlDocPtr>;
//template class FileInterface<xsltStylesheetPtr>;
