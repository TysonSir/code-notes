#pragma once
#include <vector>
#include <set>

namespace BASETOOLS
{


	template<typename ContainerType>
	void	ClearStlContainer(ContainerType& container)
	{
		ContainerType::iterator begin = container.begin();
		ContainerType::iterator end = container.end();
		for (; begin!=end; ++begin)
		{
			delete *begin;
		}
		container.clear();
	}

}
