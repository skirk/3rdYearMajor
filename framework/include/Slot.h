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

enum class Stype { input = 1<<0, output= 1<<1
};

inline const bool
operator&(Stype __x, Stype __y)
{
	return (static_cast<int>(__x) & static_cast<int>(__y));
}

class Node;

class Slot {

	protected:
		//! \brief Name of the slot
		std::string m_name;
		//! \brief Variable of the slot
		SVariable m_var;
		//! \brief Type of the slot (input or output)
		Stype m_type;

		Node *m_parent;
		Slot *m_link;
		bool m_override;
		Slot(const Slot&);

	public:
		/*! \brief Constructor
		 *
		 * \param _name Name of the slot
		 * \param _var Type of the variable
		 */
		Slot(Node *_parent, const char *_name, const SVariable &_var);
		//! \brief default constructor
		Slot();
		virtual ~Slot();
		/*! \brief assignment operator
		 * 
		 * \param _other Slot to assign from
		 */
		Slot &operator=(const Slot &_other);
		//! \brief get Name of the Slot
		std::string getName() const;
		//! \brief get Type of the Slot
		Stype getType() const;
		//! \brief Check whether the slot is input
		virtual bool isInput() const;
		//! \brief Prototype pattern
		virtual Slot *clone();
		Node *getParent();
		void linkToSlot(Slot &_s);
		/*! \brief Remove the connection
		 *
		 *	set the m_link to null and m_override to false	
		 */
		void removeLink();
		/*! \brief check whether node is overwritten
		 *
		 *  return true if Input is connected
		 */
		bool isOverwritten();
		/*! \brief get possible connection to Output slot
		 *
		 *  Return a pointer to a Output slot the Input is connected to
		 */
		Slot *getLink();
		/*! \brief Prototype pattern
		 *
		 *  return copy of self
		 */

};

#endif
