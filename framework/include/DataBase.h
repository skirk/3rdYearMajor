//! A DataBase Class
/*!
	Database holds are the nodes that are accessible to the user
*/

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
#include "Node.h"

class DataBase
{
	public:
		//! A constructor
		/*!
		 * Call for Loader class to generate all the nodes that have been implemented
		*/
		DataBase();
		std::vector<Node> m_nodes;

};
#endif
