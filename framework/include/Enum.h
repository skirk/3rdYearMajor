#ifndef _ENUM_H_
#define _ENUM_H_

enum class SlotVar {
	BOOLEAN = 0x0001,
	INT = 0x0002,
	FLOAT = 0x0003,
	VEC3 = 0x004,
	VEC4 = 0x005,
	MAT3 = 0x006,
	MAT4 = 0x007,

	INPUT = 0x1000,
	OUTPUT = 0X2000
};


inline const SlotVar
operator|(SlotVar __x, SlotVar __y)
{
	return static_cast<SlotVar>
		(static_cast<int>(__x) | static_cast<int>(__y));
}

#endif
