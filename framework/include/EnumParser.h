/*! \author Eclipse 
 *  \version 0.1
 *  \date 11/04/2013 
 *  \class EnumParser
 *  \brief return corresponding enumerators when given strings
 *
 *  The implementation is taken from Stack OverFlow answer 
 *  http://stackoverflow.com/questions/726664/string-to-enum-in-c
 */

#ifndef _ENUMPARSER_H_
#define _ENUMPARSER_H_

#include <string>
#include <iostream>
#include <map>

template <typename T>
class EnumParser
{
	private:
		//! \brief Map containing strings that correspond to enumerated values
		std::map<std::string, T>enumMap;
	public:
		//! \brief Default Constructor
		EnumParser(){};

		/* \brief return enumerator based on a give array of characters
		 *
		 * \param value is the array of characters to be checked against the maps values
		 */
		T parseEnum(const char *value)
		{
			typename std::map<std::string, T>::const_iterator iValue = enumMap.find(value);
			if (iValue  == enumMap.end())
				std::cout<<"Couldn't parse enumerator\n";
			return iValue->second;
		}
};

#endif
