#ifndef _FLANER_COMPILER_SOURCE_HH_
#define _FLANER_COMPILER_SOURCE_HH_

#include <global.hh>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <filesystem>


namespace Flaner::Compiler
{
	class Source
	{
		std::string file;
		size_t length;
	public:
		Source(std::string s);
		~Source();
		bool open(std::string s);
		bool close();
	};
};

#endif // !_FLANER_COMPILER_SOURCE_HH_
