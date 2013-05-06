/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 29/03/2013 Initialisation 
 *  \class DataBase
 *  \brief DataBase collects all the defined nodes in the program and contains them
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>
#include <string>
#include "Container.h"

class Node;

class DataBase : public Container<Node>
{
	public:
		/*! \brief A constructor
		 *
		 * Call for Loader class to generate all the nodes that have been implemented
		 */
		DataBase();
		/* \brief Get node from the DataBase
		 *
		 *
		 * \param _name  name of the node to get
		 */
};
#endif
