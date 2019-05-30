#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <statement.hh>
#include <memory>
#include <vector>

namespace Flaner
{
	namespace Compiler
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

			class Value : public Expression
			{
			public:

			};

			class Param
			{
			public:
				bool hasDefaultValue();
				bool isRest();
				std::unique_ptr<Value> defaultValue;
				Identifier id;

			};

			class ParamsList
			{
				std::vector<std::unique_ptr<Param>> params;
			public:
				inline std::iterator begin()
				{
					return params.begin();
				}

				inline std::iterator end()
				{
					return params.end();
				}

				unsigned int getLength();
			};

			class FunctionValue : public Value
			{
			public:
				std:unique_ptr<Identifier> name;
				std::unique_ptr<ParamsList> paramsList;
				std::unique_ptr<StatementSequence> body;
			};
		}
	};
};


#endif // !_FLANER_COMPILER_EXPRESSION_HH_
