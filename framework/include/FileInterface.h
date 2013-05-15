/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 18/04/2013 
 *  \class FileInterface
 *  \brief FileInterface is responsible for opening and reading files into memory.
 *  The class is templated as some files are read differently into memory than others.
 *  The differentiation is made my passing a Parser function as a function Object.
 */


#ifndef _FILEINTERFACE_H_
#define _FILEINTERFACE_H_

#include <string>
#include <vector>

template <class T>
class FileInterface
{
public:

	//! \brief Default Constructor
    FileInterface();
	//! \brief Default Destructor
    ~FileInterface();

	/* \brief change the context from where to read files
	 * 
	 * \param _context the new location to read from
	 */
	void changeContext(const std::string &_context);
	/* \brief Load a folder of files and return a vector of the objects
	 * 
	 * \param parserFunction is the function how the files are parsed
	 * \param _filename is the name of the file to be parsed
	 */
    std::vector<T> loadFolder(T (*parserFunction)(const char*), std::string _filename);
	/* \brief load a single file to memory as an object
	 * 
	 * \param parserFunction is the function how the files are parsed
	 * \param _filename is the name of the file to be parsed
	 */
    T loadFile(T (*parserFunction)(const char*), std::string _filename);

private:
	//! \brief the current context
    std::string m_context;
};

#endif

