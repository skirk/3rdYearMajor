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

enum class Stype {
	input = 1<<0,
	output= 1<<1
};

inline const bool
operator&(Stype __x, Stype __y)
{
	return (static_cast<int>(__x) & static_cast<int>(__y));
}

class BaseSlot {

	protected:
		std::string m_name;
		SVariable m_var;

	public:
		Stype m_type;
		BaseSlot(const char *_name, const SVariable &_var);
		BaseSlot();
		virtual ~BaseSlot();
		/*! \brief assignment operator
		 * 
		 * \param _other Slot to assign from
		 */
		BaseSlot &operator=(const BaseSlot &_other);
		/*! \brief Constructor
		 *
		 * \param _name Name of the slot
		 * \param _var Type of the variable
		 */
		std::string getName() const;
		bool isInput() const;

};

#endif
