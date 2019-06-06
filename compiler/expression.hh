#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <statement.hh>
#include <token.hh>
#include <declaration.hh>
#include <memory>
#include <vector>
#include <variant>

namespace Flaner
{
	namespace Compiler
	{
		namespace AST
		{
			class Value;
			class Identifier;
			//class Statement;
			class StatementSequence;

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
				std::shared_ptr<Value> right;
				std::shared_ptr<UnaryOperator> op;
			};

			class BinaryExpreesion : public Expression
			{
			public:
				std::shared_ptr<Expression> left;
				std::shared_ptr<Expression> right;
				std::shared_ptr<BinaryOperator> op;
			};

			class TernaryExpression : public Expression
			{
			public:
				std::shared_ptr<Expression> condition;
				std::shared_ptr<Expression> yes;
				std::shared_ptr<Expression> no;
			};

			class Value : public Expression
			{
			public:
				std::shared_ptr<Expression> form;
			};

			class Param
			{
			public:
				bool hasDefaultValue();
				bool isRest();
				std::shared_ptr<Value> defaultValue;
				std::shared_ptr<Identifier> id;

				Param(std::shared_ptr<Identifier> _id, std::shared_ptr<Value> _defaultValue = false)
					: id(_id), defaultValue(_defaultValue) {}

			};

			class ParamsList
			{
				using list = std::vector<std::shared_ptr<Param>>;
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
				std::shared_ptr<Identifier> name;
				std::shared_ptr<ParamsList> paramsList;
				std::shared_ptr<StatementSequence> body;
			};

			class ObjectMember
			{
			public:
				struct CommonMemberValue
				{
					std::shared_ptr<Value> value;
				};
				struct DescribedMemberValue
				{
					std::shared_ptr<FunctionValue> getter;
					std::shared_ptr<FunctionValue> setter;
				};
				std::variant<CommonMemberValue, DescribedMemberValue> value;
			};
		};
	};
};


#endif // !_FLANER_COMPILER_EXPRESSION_HH_
