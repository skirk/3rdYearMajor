//! A Loader Class
/*!
	Loader is responsible for loading and creating nodes that lie inside a ./nodes directory in the program startup.
*/

#ifndef _LOADER_H_
#define _LOADER_H_

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
		//! A increment operator overload
		/*!
		 	increment the m_current variable
		*/
		void operator++();
		//! A boolean indicating whether all files are read
		bool isEnd();

};

#endif 
