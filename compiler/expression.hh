#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <token.hh>
#include <stack>
#include <vector>
#include <memory>
#include <variant>
#include <queue>

namespace Flaner
{
	namespace Compiler
	{
		namespace Expression
		{

			using Numeric = double;
			using Boolean = bool;

			enum class ValueKindIndex : uint8_t
			{
				INDEX_NULL,
				INDEX_BOOLEAN,
				INDEX_NUMERIC,
				INDEX_BIGINT,
				INDEX_STRING,
				INDEX_OBJECT,
				INDEX_LIST,
				INDEX_FUNCTION,
				INDEX_SYMBOL,
				INDEX_REGEXP,
			};

			class AbstractValue
			{
			public:
				ValueKindIndex kindIndex;
			};

			class NullValue : AbstractValue
			{
			public:
				NullValue() : kindIndex(ValueKindIndex::INDEX_NULL) {}
			};

			class BooleanValue : public AbstractValue
			{
			public:
				BooleanValue() : kindIndex(ValueKindIndex::INDEX_BOOLEAN), value(true) {}
				BooleanValue(Boolean _value) : kindIndex(ValueKindIndex::INDEX_BOOLEAN), value(_value) {}
				Boolean value;
			};

			inline Boolean doOperatorLogicNot(Boolean value)
			{
				return !value;
			}

			inline Boolean doOperatorLogicAnd(Boolean lhs, Boolean rhs)
			{
				return lhs && rhs;
			}

			inline Boolean doOperatorLogicOr(Boolean lhs, Boolean rhs)
			{
				return lhs || rhs;
			}

			class NumericValue : AbstractValue
			{
			public:
				NumericValue() : kindIndex(ValueKindIndex::INDEX_NUMERIC) {}
				NumericValue(Numeric _value) : kindIndex(ValueKindIndex::INDEX_NUMERIC), value(_value) {}
				Numeric value;
			};
			
			class BigintValue : AbstractValue
			{
			public:
				BigintValue() : kindIndex(ValueKindIndex::INDEX_BIGINT) {}
			};

			class StringValue : AbstractValue
			{
			public:
				StringValue() : kindIndex(ValueKindIndex::INDEX_STRING), value("") {}
				StringValue(std::string value) : kindIndex(ValueKindIndex::INDEX_STRING), value(value) {}
				std::string value;
			};

			class ListValue : AbstractValue
			{
			public:
				ListValue() : kindIndex(ValueKindIndex::INDEX_LIST) {}
			};

			class ObjectValue : AbstractValue
			{
			public:
				ListValue() : kindIndex(ValueKindIndex::INDEX_OBJECT) {}
			};

			class FunctionValue : AbstractValue
			{
			public:
				FunctionValue : kindIndex(ValueKindIndex::INDEX_FUNCTION) {}
			};

			class SymbolValue : AbstractValue
			{
			public:
				SymbolValue : kindIndex(ValueKindIndex::INDEX_SYMBOL) {}
			};

			class RegExpValue : AbstractValue
			{
			public:
				RegExpValue : kindIndex(ValueKindIndex::INDEX_REGEXP) {}
			};

			using NativeValue = std::variant<NullValue, BooleanValue, NumericValue,
				BigintValue, StringValue, ListValue, ObjectValue, FunctionValue, SymbolValue, RegExpValue>;


			class UnaryOperator
			{
			public:
				enum class Kind : uint8_t
				{
					LOGIC_NOT,
					BIT_NOT,
					NEGATIVE,
					TYPEOF,
				};

				Kind kind;
			};

			class BinaryOperator
			{
			public:
				enum class Kind : uint8_t
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
					BIT_XOR,
				};

				Kind kind;
			};
			
			class Param
			{
			public:
				bool hasDefaultValue;
				bool isRest;
				std::shared_ptr<Expression> defaultValueExpr;
				std::shared_ptr<Identifier> id;

				Param()
					: hasDefaultValue(false), isRest(false), defaultValueExpr(nullptr), id(nullptr) {}

				Param(std::shared_ptr<Identifier> id)
					: hasDefaultValue(false), isRest(false), defaultValueExpr(nullptr), id(id) {}

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

				inline void insert(std::shared_ptr<Param> param)
				{
					params.push_back(param);
				}

				inline unsigned int getLength()
				{
					return params.size();
				}
			};
			
			class StatementSequence;

			class Function : AbstractValue
			{
			public:
				enum FunctionKind
				{
					COMMON,
					GENERATOR
				};
				FunctionKind kind;
				std::shared_ptr<ParamsList> paramsList;
				std::shared_ptr<StatementSequence> body;

				FunctionValue() : kind(COMMON), kindIndex(ValueKindIndex::INDEX_FUNCTION) {}
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
			


			class UnaryExpressionNode : public Expression
			{
			public:
				std::shared_ptr<Value> right;
				std::shared_ptr<UnaryOperator> op;
			};

			class BinaryExpreesionNode : public Expression
			{
			public:
				std::shared_ptr<Expression> left;
				std::shared_ptr<Expression> right;
				std::shared_ptr<BinaryOperator> op;
			};
			class TernaryExpressionNode : public Expression
			{
			public:
				std::shared_ptr<Expression> condition;
				std::shared_ptr<Expression> yes;
				std::shared_ptr<Expression> no;
			};


			using Unit = std::shared_ptr<std::variant<NativeValue, UnaryOperator, BinaryOperator>>;

			// 从 tokenList 产生可以被接受的 unit
			Unit makeUnit(std::shared_ptr<Lex::TokenList> tokenList);

			// 从 tokenList 预处理构成表达式的 tokens，保证稍后构建表达式树时不会产生错误
			class ExpressionQueue
			{
				std::queue<Unit> queue;
			public:

				// 向表达式队列插入 unit
				bool push(Unit unigt);
			};

	
		}
	}
}

#endif // !_FLANER_COMPILER_EXPRESSION_HH_
