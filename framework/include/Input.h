/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 01/05/2013 
 *  \class Input
 *  \brief Derived class from Slot expressing a Input slot
 */

#ifndef _INPUT_H_
#define _INPUT_H_
#include <memory>

#include "Slot.h"

class Output;

class Input : public Slot
{
	private:
		//! \brief boolean to determine whether connected or not
		bool m_override;
		//! \brief pointer to the connected output
		Output *m_ref;
	public:
		/*! \brief Constructor
		 *
		 *  \param _name name of the slot
		 *  \param _var variable type
		 */
		Input(Node *_parent, const char *_name, const SVariable &_var); 

		//! \brief Default Constructor
		~Input();
		/*! \brief Link Input slot to a Output slot 
		 *
		 *  Set the m_ref pointer inside Input to point to a Output
		 *  \param _s Output to be linked in
		 */
};

#endif
