#ifndef _SLOT_H_
#define _SLOT_H_
#include <string>
/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 16/04/2013 Initialisation 
 *  \class Slot
 *  \brief Slot is a object that has variable associated with it and it's either a Input our Output
 */

//enumerator implementation taken from drdobbs article series:
//http://www.drdobbs.com/flexible-c-11-imperfect-enums-part-1-dec/184403893
namespace SlotVar
{
	enum SlotVarEnum {
		BOOLEAN,
		INT,
		FLOAT,
		VEC3,
		VEC4,
		MAT3,
		MAT4,

		INPUT = 0x1000,
		OUTPUT = 0x2000
	};

	class SlotVarType
	{
		public:
			SlotVarType(SlotVarEnum v)
				:m_var(v)
			{}
			//overload type cast to Enumerator
			operator SlotVarEnum() const
			{
				return m_var;
			}
			SlotVarType &operator=(const SlotVarEnum &_other)
			{
				m_var=_other;
				return *this;
			}
		private:
			SlotVarEnum m_var;
	};
}

class Slot {

	private:
		bool m_override;
		std::string m_name;
		SlotVar::SlotVarType m_var;
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
		Slot(const char *_name, const SlotVar::SlotVarType _var);
};

#endif
