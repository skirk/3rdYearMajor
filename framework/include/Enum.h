#ifndef _ENUM_H_
#define _ENUM_H_

enum class SlotVar {
	BOOLEAN = 1<<0,
	INT = 1 <<1,
	FLOAT = 1<<2,
	VEC3 = 1 <<3,
	VEC4 = 1 <<4,
	MAT3 = 1 <<5,
	MAT4 = 1 <<6,

	INPUT = 1<<7,
	OUTPUT = 1<<8
};

enum class nodeType {
	GRAPH,
	EXPRESSION,
	STATE
};


inline const SlotVar
operator|(SlotVar __x, SlotVar __y)
{
	return static_cast<SlotVar>
		(static_cast<int>(__x) | static_cast<int>(__y));
}

inline const bool
operator&(SlotVar __x, SlotVar __y)
{
	return (static_cast<int>(__x) & static_cast<int>(__y));
}
#endif
