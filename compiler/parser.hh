#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <declaration.hh>
#include <optinal>

/*
* File: parser.hh
* Note: 根据 token 列表进行语法分析
*/

namespace Flaner
{
	namespace Compiler
	{
		namespace Parser
		{

			//  调用时此函数时，当前 token 已经是 identifier
			std::unique_ptr<AST::Identifier> parseIdentifier(std::unique_ptr<Lex::TokenList> tokenList);

			// 调用此函数时，当前 token 是 '(' 或 identifier
			std::unique_ptr<AST::Value> parseValue(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::UnaryExpression> parseUnaryExpression(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::Expression> parseExpression(std::unique_ptr<Lex::TokenList> tokenList);


			std::unique_ptr<AST::BlockStatement> parseBlockStatement(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::IfStatement> parseIfStatement(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::CaseClause>   parseCaseClause(std::unique_ptr<Lex::TokenList> tokenList);
			std::unique_ptr<AST::DefaultClause> parseDefaultClause(std::unique_ptr<Lex::TokenList> tokenList);
			std::optional<std::variant<std::unique_ptr<AST::CaseClause, AST::DefaultClause>>>
				parseSwitchClause(std::unique_ptr<Lex::TokenList> tokenList);
			std::vector<std::optional<std::variant<std::unique_ptr<AST::CaseClause, AST::DefaultClause>>>>
				parseSwitchClauseList(std::unique_ptr<Lex::TokenList>);
			std::unique_ptr<AST::SwitchStatement> parseSwitchStatement(std::unique_ptr<Lex::TokenList> tokenList);			

			std::unique_ptr<AST::WhileStatement> parseWhileStatement(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::ForStatement> parseForStatement(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::ContinueStatement> parseContinueStatement(std::unique_ptr<Lex::TokenList> tokenList);

			std::unique_ptr<AST::BreakStatement> parseBreakStatement(std::unique_ptr<Lex::TokenList> tokenList);

		}
	};
};

#endif // !_FLANER_COMPILER_PARSER_HH_
