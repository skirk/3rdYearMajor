#ifndef _FILEINTERFACE_H_
#define _FILEINTERFACE_H_

#include <string>
#include <vector>

template <class T>
class FileInterface
{
public:

    FileInterface();
    ~FileInterface();

	void changeContext(const std::string &_context);
    std::vector<T> loadFolder(T (*parserFunction)(const char*), std::string _filename);
    T loadFile(T (*parserFunction)(const char*), std::string _filename);

private:
    std::string m_context;
};

#endif

