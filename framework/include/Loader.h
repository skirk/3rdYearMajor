//! A Loader Class
/*!
	Loader is responsible for loading and creating nodes that lie inside a ./nodes directory in the program startup.
*/

#ifndef _LOADER_H_
#define _LOADER_H_

#include <libxml/tree.h>
#include <string>

class Loader
{
	private:
		//! A variable to track current status
		int m_current;
		//! A variable to track number of node files
		int m_size;
	public:
		//! A constructor
		/*!
		 * The constructor lists all the node files in nodes folder and generates objects.
		*/
		Loader();
		//! A destructor
		~Loader();
		//! Parse file
		/*!
		  Parse the given file
		  \param _filename path to file
		  */
		//xmlDocPtr loadDocument(const char *_filename);
		//! Create a node object
		/*!
		  create a node according to the passed in document
		  \param _doc the tree to parse
		  */

		//! load files from node folder
		/*!
		  create a node according to the passed in document
		  \param _doc the tree to parse
		  */
        //void loadFolder(const std::string &_location);
		//void parseNode(const xmlDocPtr &_doc);
		//! A increment operator overload
		/*!
		  increment the m_current variable
		  */
		void operator++();
		//! A boolean indicating whether all files are read
		bool isEnd();
		//! Print all the element nodes 
		/*!                
		 * \param xmlNode print node and its children
		 */
		void printElementNames(xmlNode *a_node);

};


#endif
