#include "Loader.h"
#include <iostream>
#include <cstring>
#include <dirent.h>

Loader::Loader()
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir("./nodes");
	if(dp != NULL)
	{
		while (ep = readdir(dp))
			if(strstr(ep->d_name, ".xml"))
				std::cout<< ep->d_name <<"\n";
		(void) closedir(dp);
	}
	else
		std::cout<<"couldn't open the directory\n";

	m_iteration = 0;
	m_size = 5;
}

Loader::~Loader()
{
}

void Loader::operator++()
{
	m_iteration++;
}

bool Loader::isEnd()
{
	if(m_iteration < m_size)
	{
		return false;
	}
	else
		return true;
}

