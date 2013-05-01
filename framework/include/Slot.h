/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 16/04/2013 Initialisation 
 *  \class Slot
 *  \brief Slot is a object that has variable associated with it and it's either a Input our Output
 */

#ifndef _SLOT_H_
#define _SLOT_H_
#include <string>
#include "Enum.h"

class Slot {

	private:
		bool m_override;
		std::string m_name;
		SlotVar m_var;
	public:
		Slot(const char *_name, const SlotVar &_var);
		Slot();
		~Slot();
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
		std::string getName() const;
		SlotVar getVar() const;


};

#endif
