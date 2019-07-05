#ifndef _FLANER_COMPILER_EXPRESSION_HH_
#define _FLANER_COMPILER_EXPRESSION_HH_

#include <global.hh>
#include <token.hh>
#include <meta.hh>
#include <stack>
#include <vector>
#include <memory>
#include <variant>
#include <queue>
#include <map>
#include <set>

namespace Flaner
{
    namespace Compiler
    {
        namespace Expr
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

            class NullValue
            {
            public:
				ValueKindIndex kindIndex;
                NullValue() : kindIndex(ValueKindIndex::INDEX_NULL) {}
            };


            class BooleanValue
            {
            public:
				ValueKindIndex kindIndex;
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

            class NumericValue
            {
            public:
                NumericValue() : kindIndex(ValueKindIndex::INDEX_NUMERIC) {}
                NumericValue(Numeric _value) : kindIndex(ValueKindIndex::INDEX_NUMERIC), value(_value) {}
                Numeric value;
            };
            
            class BigintValue
            {
            public:
                BigintValue() : kindIndex(ValueKindIndex::INDEX_BIGINT) {}
            };

            class StringValue
            {
            public:
				ValueKindIndex kindIndex;
                StringValue() : kindIndex(ValueKindIndex::INDEX_STRING), value("") {}
                StringValue(std::string value) : kindIndex(ValueKindIndex::INDEX_STRING), value(value) {}
                std::string value;
            };

            class ListValue
            {
            public:
				ValueKindIndex kindIndex;
                ListValue() : kindIndex(ValueKindIndex::INDEX_LIST) {}
            };

            class ObjectValue
            {
            public:
				ValueKindIndex kindIndex;
                ObjectValue() : kindIndex(ValueKindIndex::INDEX_OBJECT) {}
            };

            class FunctionValue
            {
            public:
				ValueKindIndex kindIndex;
                FunctionValue() : kindIndex(ValueKindIndex::INDEX_FUNCTION) {}
            };

            class SymbolValue
            {
            public:
				ValueKindIndex kindIndex;
                SymbolValue() : kindIndex(ValueKindIndex::INDEX_SYMBOL) {}
            };

            class RegExpValue
            {
            public:
				ValueKindIndex kindIndex;
                RegExpValue() : kindIndex(ValueKindIndex::INDEX_REGEXP) {}
            };

            using Value = std::variant<NullValue, BooleanValue, NumericValue,
                BigintValue, StringValue, ListValue, ObjectValue, FunctionValue, SymbolValue, RegExpValue>;


            class UnaryOperator
            {
            public:

                Meta::Operator kind;
				uint8_t priority;
				explicit UnaryOperator(Meta::Operator _kind) : kind(kind) {}
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
                std::shared_ptr<ExpressionNode> defaultValueExpr;
                std::shared_ptr<AST::Identifier> id;

                Param()
                    : hasDefaultValue(false), isRest(false), defaultValueExpr(nullptr), id(nullptr) {}

                Param(std::shared_ptr<AST::Identifier> id)
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

            class Function : public FunctionValue
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

                Function() : kind(COMMON) {}
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
            

			/*
			* 表达式树节点定义
			*/
			class ExpressionNode;

			class ValueNode
			{
			public:
				std::shared_ptr<Value> value;
			};
			
            class UnaryExpressionNode
            {
            public:
                std::shared_ptr<ExpressionNode> right;
                std::shared_ptr<UnaryOperator> op;
            };

            class BinaryExpressionNode
            {
            public:
                std::shared_ptr<ExpressionNode> left;
                std::shared_ptr<ExpressionNode> right;
                std::shared_ptr<BinaryOperator> op;
            };

            class TernaryExpressionNode
            {
            public:
                std::shared_ptr<ExpressionNode> condition;
                std::shared_ptr<ExpressionNode> yes;
                std::shared_ptr<ExpressionNode> no;
            };

			class MemberAccessNode
			{
			public:

				// 对于 app.foo.bar.some
				// 会得到以下树：
				//     [MemberAccessNode]
				//     -> [MemberAccessNode]
				//         -> [MemberAccessNode]
				//            -> app
				//            -> foo
				//         -> bar
				//     -> some
				//
				// 同样，对于 a[123].b.c[456]
				// 会得到以下树：
				//     [BinaryExpressionNode(op_postfix_at)]
				//     -> [MemberAccessNode]
				//         -> [MemberAccessNode]
				//             -> [BinaryExpressionNode(op_postfix_at)]
				//                -> a
				//                -> 123
				//             -> b
				//         -> c
				//     -> 456
				std::shared_ptr<ExpressionNode> object;
				std::shared_ptr<AST::Identifier> attribute;
			};

			class FunctionCallingNode
			{
			public:
				std::shared_ptr<AST::Identifier> functionName;
				std::vector<std::shared_ptr<ExpressionNode>> arguments;
			};

			class ExpressionNodez
			{
			public:
				std::variant<ValueNode, UnaryExpressionNode, BinaryExpressionNode, TernaryExpressionNode> node;
			};

			using UnitStream = std::queue<std::variant<Meta::Operator, Value>>;

			using TokenList = std::shared_ptr<Lex::TokenList>;


			std::map<Lex::TokenType, uint16_t> priorityLookupTable = {
				{ Lex::TOKEN_ADD,             0 },
				{ Lex::TOKEN_BIT_NOT,         0 },
				{ Lex::TOKEN_LOGIC_NOT,       0 },
				{ Lex::TOKEN_TYPEOF,          0 },

				{ Lex::TOKEN_LOGIC_AND,       0 },
				{ Lex::TOKEN_BIT_AND,         0 },
				{ Lex::TOKEN_LOGIC_OR,        0 },
				{ Lex::TOKEN_BIT_OR,          0 },
				{ Lex::TOKEN_LOGIC_XOR,       0 },
				{ Lex::TOKEN_BIT_XOR,         0 },

				{ Lex::TOKEN_PIPELINE,        0 },
				{ Lex::TOKEN_EQUAL,           0 },
				{ Lex::TOKEN_NOT_EQUAL,       0 },
				{ Lex::TOKEN_LESS_THAN,       0 },
				{ Lex::TOKEN_GREATER_THAN,    0 },
				{ Lex::TOKEN_LESS_EQ_THAN,    0 },
				{ Lex::TOKEN_GREATER_EQ_THAN, 0 },
				{ Lex::TOKEN_SPACESHIP,       0 },

				{ Lex::TOKEN_ADD,             0 },
				{ Lex::TOKEN_SUB,             0 },
				{ Lex::TOKEN_MUL,             0 },
				{ Lex::TOKEN_DIV,             0 },
				{ Lex::TOKEN_MOD,             0 },
				{ Lex::TOKEN_POW,             0 },
				{ Lex::TOKEN_SAL,             0 },
				{ Lex::TOKEN_SRL,             0 },
				{ Lex::TOKEN_ROL,             0 },
				{ Lex::TOKEN_ROR,             0 },
			
			};

			std::set<Lex::TokenType> unaryOperatorsSet = {
				Lex::TOKEN_ADD,
				Lex::TOKEN_BIT_NOT,
				Lex::TOKEN_LOGIC_NOT,
				Lex::TOKEN_TYPEOF,
			};
			
#include <queue>

			std::queue<>;

			std::shared_ptr<Value> parseValue(TokenList tokenList);
			std::shared_ptr<UnaryExpressionNode> parseExpressionNeg(TokenList tokenList);
			std::shared_ptr<UnaryExpressionNode> parseExpressionNotB(TokenList tokenList);
			std::shared_ptr<UnaryExpressionNode> parseExpressionNotL(TokenList tokenList);
			std::shared_ptr<UnaryExpressionNode> parseExpressionTypeof(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionAt(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionPow(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionAndL(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionOrL(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionPipeline(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionCoale(TokenList tokenList);
			std::shared_ptr<TernaryExpressionNode> parseExpressionBranch(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionCompare(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionAdd(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionSub(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionMul(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionDiv(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionMod(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionSA(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionSL(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionAndB(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionOrB(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionXorB(TokenList tokenList);
			std::shared_ptr<BinaryExpressionNode> parseExpressionAssign(TokenList tokenList);
			std::shared_ptr<MemberAccessNode> parseMemberAccess(TokenList tokenList);
			std::shared_ptr<FunctionCallingNode> parseFunctionCalling(TokenList tokenList);

			std::shared_ptr<ExpressionNode> makeExpressionTree(OperatorQueue, ValueQueue);
    
        }
    }
}

#endif // !_FLANER_COMPILER_EXPRESSION_HH_
