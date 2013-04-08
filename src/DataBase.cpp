#include "DataBase.h"
#include "Loader.h"
#include <iostream>

DataBase::DataBase()
{
	Loader *load = new Loader();
	
	while(!load->isEnd())
	{
		++(*load);
	}
	delete load;
}
