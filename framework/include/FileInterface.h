#ifndef _FILEINTERFACE_H_
#define _FILEINTERFACE_H_

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>
#include <vector>

template <class T>
class FileInterface
{
	public:

		std::vector<T> parseFolder(std::string _foldername);
		T parseFile(T (*parserFunction)(const char*), std::string _filename);

	private:
		std::string m_context;
};

template <class T>
T FileInterface::parseXML(T (*parserFunction)(const char*), std::string _filename)
{
	return parserFunction(_filename.c_str());;
}	

#endif
