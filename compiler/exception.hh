#ifndef _FLANER_COMPILER_EXCEPTION_HH_
#define _FLANER_COMPILER_EXCEPTION_HH_

#include <global.hh>
#include <string>
#include <iostream>

namespace Flaner
{
	namespace Compiler
	{
		namespace Exception
		{
			class Error
			{
				std::string info;
			public:
				FlanerCompilerException(std::string info) : info(info) {}
				inline std::string what()
				{
					return "Error: " + info;
				}
			};

			class SyntaxError : public Error
			{
			public:
				SyntaxError(std::string info) : info(info) {}
				inline std::string what()
				{
					return "SyntaxError: " + info;
				}
			};

#define syntax_error(info) \
		throw new SyntaxError(info);

		}
	}
}

#endif // !_FLANER_COMPILER_EXCEPTION_HH_

