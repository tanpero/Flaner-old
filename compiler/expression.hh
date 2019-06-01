#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <statement.hh>
#include <token.hh>
#include <memory>
#include <vector>
#include <variant>

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

			class Operator
			{
			public:
				enum Kind
				{
					PLUS,
					MINUS,
					MULTI,
					DEVIDE,
					POWER,
					MOD,
					LOGIC_AND,
					LOGIC_OR,
					BIT_AND,
					BIT_OR,
					BIT_XOR
				};

				Kind kind;
				Operator(std::string op);
				Operator(Lex::Token token);
			};

			class UnaryExpression : public Expression
			{
			public:
				UnaryExpression()
			};

			class BinaryExpreesion : public Expression
			{
			public:
				std::unique_ptr<Expression> left;
				std::unique_ptr<Expression> right;
				std::string op
			};

			class Value : public Expression
			{
			public:
				Expression form;
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
				enum FunctionKind
				{
					COMMON,
					GENERATOR
				};
				std:unique_ptr<Identifier> name;
				std::unique_ptr<ParamsList> paramsList;
				std::unique_ptr<StatementSequence> body;
			};

			class ObjectMember
			{
			public:
				struct CommonMemberValue
				{
					std::unique_ptr<Value> value;
				};
				struct DescribedMemberValue
				{
					std::unique_ptr<FunctionValue> getter;
					std::unique_ptr<FunctionValue> setter;
				};
				std::variant<CommonMemberValue, DescribedMemberValue> value;
			};
		}
	};
};


#endif // !_FLANER_COMPILER_EXPRESSION_HH_
