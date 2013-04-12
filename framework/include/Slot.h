#ifndef _SLOT_H_
#define _SLOT_H_

#include <string>

enum slotType {
	INPUT,
	OUTPUT
};

enum variable {
	BOOLEAN,
	INT,
	FLOAT,
	VEC3,
	VEC4,
	MAT3,
	MAT4
};

class Slot {
	private:
		bool m_override;
		std::string m_name;
		slotType m_type;	
		variable m_var;
};

#endif
