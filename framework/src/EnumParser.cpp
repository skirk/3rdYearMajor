#include "EnumParser.h"
#include "Enum.h"

template <>
EnumParser<SlotVar>::EnumParser()
{
	enumMap["boolean"] = SlotVar::BOOLEAN;
	enumMap["int"] = SlotVar::INT;
	enumMap["float"] = SlotVar::FLOAT;
	enumMap["vec3"] =SlotVar::VEC3;
	enumMap["vec4"] = SlotVar::VEC4;
	enumMap["mat3"] = SlotVar::MAT3;
	enumMap["mat4"] = SlotVar::MAT4;
	enumMap["input"] = SlotVar::INPUT;
	enumMap["output"] = SlotVar::OUTPUT;
}
