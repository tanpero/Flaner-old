#include <statement.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace AST
		{

			std::string IfStatement::type()
			{
				return "if";
			}


			void IfStatement::walk()
			{

			}


			std::shared_ptr<Statement> StatementSequence::get()
			{
				return std::shared_ptr<Statement>();
			}


			bool StatementSequence::next()
			{
				return false;
			}


			void StatementSequence::insert(std::shared_ptr<Statement> statement)
			{
			}

			std::string Statement::type()
			{
				return std::string();
			}

			void Statement::walk()
			{
			}

		};
	};
};
