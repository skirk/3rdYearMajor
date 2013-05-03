#include "EnumParser.h"
#include "Enum.h"

template <>
EnumParser<SVariable>::EnumParser()
{
	enumMap["boolean"] = SVariable::BOOLEAN;
	enumMap["int"] = SVariable::INT;
	enumMap["float"] = SVariable::FLOAT;
	enumMap["vec3"] =SVariable::VEC3;
	enumMap["vec4"] = SVariable::VEC4;
	enumMap["mat3"] = SVariable::MAT3;
	enumMap["mat4"] = SVariable::MAT4;
}
