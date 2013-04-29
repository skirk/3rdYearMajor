#ifndef _ENUMPARSER_H_
#define _ENUMPARSER_H_

#include <string>
#include <iostream>
#include <map>

template <typename T>
class EnumParser
{
	private:
		std::map<std::string, T>enumMap;
	public:
		EnumParser(){};

		T parseEnum(const char *value)
		{
			typename std::map<std::string, T>::const_iterator iValue = enumMap.find(value);
			if (iValue  == enumMap.end())
				std::cout<<"Couldn't parse enumerator\n";
			return iValue->second;
		}
};

#endif
