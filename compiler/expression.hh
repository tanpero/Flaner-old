#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <statement.hh>
#include <memory>

namespace Flaner::Compiler
{
	namespace AST
	{
		class Expression : public Statement
		{
		public:

		};

		class BinaryExpreesion : public Expression
		{
		public:
			std::unique_ptr<Expression> left;
			std::unique_ptr<Expression> right;
		};
	}
}



#endif // !_FLANER_COMPILER_EXPRESSION_HH_
