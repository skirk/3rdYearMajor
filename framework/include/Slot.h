#ifndef _SLOT_H_
#define _SLOT_H_
#include <string>
#include "Enum.h"

/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 16/04/2013 Initialisation 
 *  \class Slot
 *  \brief Slot is a object that has variable associated with it and it's either a Input our Output
 */

class Slot {

	private:
		bool m_override;
		std::string m_name;
		SlotVar m_var;
	public:
		/*! \brief assignment operator
		 * 
		 * \param _other Slot to assign from
		 */
		Slot &operator=(const Slot &_other);
		/*! \brief Constructor
		 *
		 * \param _name Name of the slot
		 * \param _var Type of the variable
		 */
		Slot(const char *_name, const SlotVar &_var);
};

#endif
