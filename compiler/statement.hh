#ifndef _FLANER_COMPILER_STATEMENT_HH_
#define  _FLANER_COMPILER_STATEMENT_HH_

#include <global.hh>
#include <expression.hh>
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
		}
	};
};

#endif // !_FLANER_COMPILER_STATEMENT_HH_
