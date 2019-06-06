#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <declaration.hh>
#include <optional>

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

			using TokenList = std::shared_ptr<Lex::TokenList>;

			//  调用时此函数时，当前 token 已经是 identifier
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList);

			// 调用此函数时，当前 token 是 '(' 或 identifier
			std::shared_ptr<AST::Value> parseValue(TokenList tokenList);

			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList);

			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList);


			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList);

			std::shared_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList);

			std::shared_ptr<AST::CaseClause>   parseCaseClause(TokenList tokenList);
			std::shared_ptr<AST::DefaultClause> parseDefaultClause(TokenList tokenList);
			
			using SwitchClause = std::optional<std::variant<std::shared_ptr<AST::CaseClause>, std::shared_ptr<AST::DefaultClause>>>;
			SwitchClause parseSwitchClause(TokenList tokenList);
			
			using SwitchClauseList = std::vector<SwitchClause>;
			SwitchClauseList parseSwitchClauseList(TokenList);

			std::shared_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList);			

			std::shared_ptr<AST::WhileStatement> parseWhileStatement(TokenList tokenList);

			std::shared_ptr<AST::ForStatement> parseForStatement(TokenList tokenList);

			std::shared_ptr<AST::ContinueStatement> parseContinueStatement(TokenList tokenList);

			std::shared_ptr<AST::BreakStatement> parseBreakStatement(TokenList tokenList);

		}
	};
};

#endif // !_FLANER_COMPILER_PARSER_HH_
