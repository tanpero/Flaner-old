#ifndef _FLANER_COMPILER_STATEMENT_HH_
#define  _FLANER_COMPILER_STATEMENT_HH_

#include <global.hh>
#include <declaration.hh>
#include <expression.hh>

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
				void insert(Statement statement);

			};

			class NullStatement : public Statement
			{
			public:

			};

			class BlockStatement : public Statement
			{
			public:
				std::shared_ptr<StatementSequence> body;
			};


			class IfStatement : public Statement
			{
			public:
				virtual std::string type();
				virtual void walk();

				std::shared_ptr<Expression> condition;
				std::shared_ptr<BlockStatement> body;

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
				using Declaration   = std::shared_ptr<AST::Declaration>;
				using Expression    = std::shared_ptr<AST::Expression>;
			public:
				std::variant<NullStatement, Declaration, Expression> body;
				std::shared_ptr<ForInitializer> operator=
					(std::variant<NullStatement, Declaration, Expression> initializer)
				{
					body = initializer;
				}
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
				struct CatchStatement
				{
					std::shared_ptr<Identifier> bindingId;
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
				Value value;
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
				std::shared_ptr<Value> value;
			};

			class YieldStatement : public Statement
			{
			public:
				std::shared_ptr<Value> value;
			};

		};
	};
};

#endif // !_FLANER_COMPILER_STATEMENT_HH_
