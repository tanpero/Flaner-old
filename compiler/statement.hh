#ifndef _FLANER_COMPILER_STATEMENT_HH_
#define  _FLANER_COMPILER_STATEMENT_HH_

#include <global.hh>
#include <expression.hh>
#include <declaration.hh>
#include <memory>
#include <vector>
#include <variant>
#include <tuple>

namespace Flaner
{
	namespace Compiler
	{
		namespace AST
		{
			class Statement
			{
			public:

			};

			class StatementSequence
			{
				std::vector<std::unique_ptr<Statement>> sequence;
			public:
				std::auto_ptr<Statement> get();
				bool next();
				void insert(Statement statement);
			};

			class IfStatement : public Statement
			{
			public:
				std::unique_ptr<Expression> condition;
				std::unique_ptr<StatementSequence> body;
			};

			class WhileStatement : public Statement
			{
			public:
				std::unique_ptr<Expression> condition;
				std::unique_ptr<StatementSequence> body;
			};

			class DoWhileStatement : public Statement
			{
			public:
				std::unique_ptr<Expression> condition;
				std::unique_ptr<StatementSequence> body;
			};

			class ForStatement : public Statement
			{
			public:
				struct CommonHeader
				{
					std::unique_ptr<Expression> initialization;
					std::unique_ptr<Expression> condition;
					std::unique_ptr<Expression> increment;
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
				std::unique_ptr<StatementSequence> body;
			};

			class CaseStatement : public Statement
			{
			public:
				std::unique_ptr<Expression> object;
				std::unique_ptr<StatementSequence> body;
			};

			class SwitchStatement : public Statement
			{
			public:
				std::unique_ptr<Expression> target;
				std::vector<std::unique_ptr<CaseStatement>> cases;
				std::unique_ptr<StatementSequence> defaultCase;
			};

			class TryCatchStatement : public Statement
			{
			public:
				struct CatchStatement
				{
					Identifier bindingId;
					std::unique_ptr<StatementSequence> body;
				};

			public:
				std::unique_ptr<StatementSequence> tryBody;
				std::vector<std::unique_ptr<CatchStatement>> catchBodies;
				std::unique_ptr<StatementSequence> finallyBody;
			};

			class LabelStatement : public: Statement
			{
			public:
				std::string name;
			}

			class BreakStatement : public Statement
			{
			public:
				std::unique_ptr<LabelStatement> label;
			};

			class ContinueStatement : public Statement
			{
			public:
				std::unique_ptr<LabelStatement> label;
			};

			

		};
	};
};

#endif // !_FLANER_COMPILER_STATEMENT_HH_
