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
		//! \brief Name of the slot
		std::string m_name;
		//! \brief Variable of the slot
		SVariable m_var;
		//! \brief Type of the slot (input or output)
		Stype m_type;

	public:
		/*! \brief Constructor
		 *
		 * \param _name Name of the slot
		 * \param _var Type of the variable
		 */
		BaseSlot(const char *_name, const SVariable &_var);
		//! \brief default constructor
		BaseSlot();
		BaseSlot(const BaseSlot&);
		virtual ~BaseSlot();
		/*! \brief assignment operator
		 * 
		 * \param _other Slot to assign from
		 */
		BaseSlot &operator=(const BaseSlot &_other);
		//! \brief get Name of the Slot
		std::string getName() const;
		//! \brief get Type of the Slot
		Stype getType() const;
		//! \brief Check whether the slot is input
		bool isInput() const;
		//! \brief Prototype pattern
		virtual BaseSlot *clone();

};

#endif
