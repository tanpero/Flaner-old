#ifndef _FLANER_COMPILER_STATEMENT_HH_
#define  _FLANER_COMPILER_STATEMENT_HH_

#include <global.hh>
#include <token.hh>

#include <memory>
#include <vector>
#include <variant>
#include <tuple>
#include <string>

namespace Flaner
{
	namespace Compiler
	{
		namespace AST
		{

			class Statement
			{
			public:
				virtual std::string type();
				virtual void walk();
			};

			class StatementSequence
			{
				std::vector<std::shared_ptr<Statement>> sequence;
			public:
				std::shared_ptr<Statement> get();
				bool next();
				void insert(std::shared_ptr<Statement> statement);

			};

			class NullStatement : public Statement
			{
			public:

			};

			class BlockStatement : public Statement
			{
			public:
				BlockStatement(std::shared_ptr<StatementSequence> sequence) : body(sequence) {}
				std::shared_ptr<StatementSequence> body;
			};


			class Identifier
			{
			public:
				std::string name;

				Identifier(Lex::Token token)
				{
					name = token.value;
				}

				Identifier() : name("") {}
				Identifier(std::string name) : name(name) {}
			};

			class Declaration : public Statement
			{
			public:
				enum Kind : int
				{
					Variable = 0,
					Constant = 1
				};

			public:
				Kind kind;
				std::shared_ptr<Identifier> identifier;
			};


			class Instantiation : Statement
			{
			public:
				std::shared_ptr<Identifier> className;
			};


			class InstanceBinding : Statement
			{
			public:
				std::shared_ptr<Declaration> declaration;
				std::shared_ptr<Instantiation> type;
			};


			class Expression : public Statement
			{
			public:

			};

			class UnaryOperator
			{
			public:
				std::shared_ptr<Lex::Token> name;
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

			class Value;

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
				Value() : form(std::make_shared<Expression>()) {}
				Value(std::shared_ptr<Expression> expr) : form(expr) {}
				std::shared_ptr<Expression> form;
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

			class FunctionValue : public Value
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

				FunctionValue() : kind(COMMON) {}
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


			class DefintionStatement : public Statement
			{
			public:
				Declaration::Kind kind;
				std::shared_ptr<Identifier> identifier;
				std::shared_ptr<Expression> initializer;
				std::shared_ptr<Instantiation> instantiation;
			};

			class ElseClause;

			class IfStatement : public Statement
			{
			public:
				virtual std::string type();
				virtual void walk();

				std::shared_ptr<Expression> condition;
				std::shared_ptr<BlockStatement> body;
				std::shared_ptr<ElseClause> branch;

			};

			class ElseClause : public Statement
			{
			public:
				std::shared_ptr<BlockStatement> body;
			};

			class WhileStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> condition;
				std::shared_ptr<BlockStatement> body;
			};

			class DoWhileStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> condition;
				std::shared_ptr<BlockStatement> body;
			};


			class ForInitializer : public Statement
			{
				using NullStatement = std::shared_ptr<AST::NullStatement>;
				using Defintion     = std::shared_ptr<AST::DefintionStatement>;
				using Expression    = std::shared_ptr<AST::Expression>;
			public:
				std::variant<NullStatement, Defintion, Expression> body;
				ForInitializer(NullStatement s) : body(s) {}
				ForInitializer(Defintion s) : body(s) {}
				ForInitializer(Expression s) : body(s) {}
			};

			class ForComplementTriplet : public Statement
			{
			public:
				std::shared_ptr<ForInitializer> initializer;
				std::shared_ptr<Expression> condition;
				std::shared_ptr<Expression> increment;
				std::shared_ptr<BlockStatement> body;
			};

			class ForInStatement : public Statement
			{
			public:
				std::shared_ptr<Declaration> binding;
				std::shared_ptr<Expression> target;
				std::shared_ptr<BlockStatement> body;
			};

			class ForOfStatement : public Statement
			{
			public:
				std::shared_ptr<Declaration> binding;
				std::shared_ptr<Expression> target;
				std::shared_ptr<BlockStatement> body;
			};

			class ForStatement : public Statement
			{
			public:
				struct CommonHeader
				{
					std::shared_ptr<Expression> initialization;
					std::shared_ptr<Expression> condition;
					std::shared_ptr<Expression> increment;
				};

				// 保留 for...in 和 for...of 语句的循环头定义
				struct InHeader
				{

				};

				struct OfHeader
				{

				};

				using Header = std::variant<CommonHeader, InHeader, OfHeader>;

			public:
				Header header;
				std::shared_ptr<BlockStatement> body;
			};

			// 若表达式指针为 nullptr，则该子句为 default 子句，否则为 case 子句
			using SwitchClause = std::pair<std::shared_ptr<Expression>, std::shared_ptr<BlockStatement>>;
			using SwitchClauseList = std::vector<std::shared_ptr<SwitchClause>>;

			class SwitchStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> target;
				std::shared_ptr<SwitchClauseList> clauseList;
			};

			class TryCatchStatement : public Statement
			{
			public:
				struct CatchClause
				{
					std::shared_ptr<InstanceBinding> binding;
					std::shared_ptr<BlockStatement> body;
				};

			public:
				std::shared_ptr<BlockStatement> tryBlockStatement;
				std::vector<std::shared_ptr<CatchStatement>> catchBodies;
				std::shared_ptr<BlockStatement> finallyBlockStatement;
			};

			class LabelStatement : public Statement
			{
			public:
				LabelStatement(std::shared_ptr<Identifier> name) : name(name->name) {}
				std::string name;
			};

			class BreakStatement : public Statement
			{
			public:
				std::shared_ptr<LabelStatement> label;
			};

			class ContinueStatement : public Statement
			{
			public:
				std::shared_ptr<LabelStatement> label;
			};

			class VisitorStatement : public Statement
			{
			public:
				enum Kind
				{
					getter, setter
				};

				Kind kind;
				FunctionValue function;
			};
			
			class ClassStatement : public Statement
			{
			public:
				FunctionValue constructor;
				Identifier name;
				std::vector<std::shared_ptr<ObjectMember>> members;
			};

			class ThrowStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> expression;
			};

			class ImportStatement : public Statement
			{
			public:
				std::string name;
				std::string path;
				std::string rename;
			};

			class WithStatement : public Statement
			{
			public:
				std::shared_ptr<Value> object;
				std::shared_ptr<BlockStatement> body;
			};

			class ReturnStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> expression;
			};

			class YieldStatement : public Statement
			{
			public:
				std::shared_ptr<Expression> expression;
			};

		};
	};
};

#endif // !_FLANER_COMPILER_STATEMENT_HH_
