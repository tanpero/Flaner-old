#ifndef _FLANER_COMPILER_DECLARATION_HH_
#define _FLANER_COMPILER_DECLARATION_HH_

#include <global.hh>
#include <statement.hh>
#include <string>

namespace Flaner
{
	namespace Compiler
	{
		namespace AST
		{
			class Identifier
			{
			public:
				std::string name;
			};

			class Declaration : public Statement
			{
			public:
				enum Kind
				{
					Variable,
					Constant
				};

			public:
				Kind kind;
				Identifier identifier;
			};
		}
	}
}

#endif // !_FLANER_COMPILER_DECLARATION_HH_
