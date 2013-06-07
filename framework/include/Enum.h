#ifndef _ENUM_H_
#define _ENUM_H_

enum class SVariable {
	BOOLEAN = 1<<0,
	INT     = 1<<1,
	FLOAT   = 1<<2,
	VEC3    = 1<<3,
	VEC4    = 1<<4,
	MAT3    = 1<<5,
	MAT4    = 1<<6,
};

enum class nodeType {
	GRAPH,
	OPERATOR,
	FUNCTION,
	STATE,
	CONSTRUCTOR,
	CONSTANT,
	BRANCH
};


inline const SVariable
operator|(SVariable __x, SVariable __y)
{
	return static_cast<SVariable>
		(static_cast<int>(__x) | static_cast<int>(__y));
}


#endif
