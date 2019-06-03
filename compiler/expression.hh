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

			class UnaryOperator
			{
			public:
				UnaryOperator operator=(Lex::Token token);
			};

			class BinaryOperator
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
				BinaryOperator(std::string op);
				BinaryOperator(Lex::TokenType token);
			};

			class UnaryExpression : public Expression
			{
			public:
				std::unique_ptr<Value> right;
				std::unique_ptr<UnaryOperator> op;
			};

			class BinaryExpreesion : public Expression
			{
			public:
				std::unique_ptr<Expression> left;
				std::unique_ptr<Expression> right;
				std::unique_ptr<BinaryOperator> op;
			};

			class TernaryExpression : public Expression
			{
			public:
				std::unique_ptr<Expression> condition;
				std::unique_ptr<Expression> yes;
				std::unique_ptr<Expression> no;
			};

			class Value : public Expression
			{
			public:
				std::unique_ptr<Expression> form;
			};

			class Param
			{
			public:
				bool hasDefaultValue();
				bool isRest();
				std::unique_ptr<Value> defaultValue;
				std::unique_ptr<Identifier> id;

				Param(std::unique_ptr<Identifier> _id, std::unique_ptr<Value> _defaultValue = false)
				{
					id = _id;
					defaultValue = _defaultValue;
				}

			};

			class ParamsList
			{
				using list = std::vector<std::unique_ptr<Param>>;
				list params;
			public:
				inline list::iterator begin()
				{
					return params.begin();
				}

				inline list::iterator end()
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
				std::unique_ptr<Identifier> name;
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
		};
	};
};


#endif // !_FLANER_COMPILER_EXPRESSION_HH_
