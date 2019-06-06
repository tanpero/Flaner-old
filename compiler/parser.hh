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

			std::shared_ptr<AST::NullStatement> parseNullStatement(TokenList tokenList);
			std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList);
			std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList);

			//  调用时此函数时，当前 token 已经是 identifier
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList);

			// 调用此函数时，当前 token 是 '(' 或 identifier
			std::shared_ptr<AST::Value> parseValue(TokenList tokenList);

			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList);

			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList);


			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList);

			std::shared_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList);

			std::shared_ptr<AST::SwitchClause> parseCaseClause(TokenList tokenList);
			std::shared_ptr<AST::SwitchClause> parseDefaultClause(TokenList tokenList);
			
			std::shared_ptr<AST::SwitchClause> parseSwitchClause(TokenList tokenList);
			
			std::shared_ptr<AST::SwitchClauseList> parseSwitchClauseList(TokenList);

			std::shared_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList);			

			std::shared_ptr<AST::WhileStatement> parseWhileStatement(TokenList tokenList);


			std::shared_ptr<AST::ForInitializer> parseForInitializer(TokenList tokenList);
			std::shared_ptr<AST::ForStatement> parseForStatement(TokenList tokenList);

			std::shared_ptr<AST::ContinueStatement> parseContinueStatement(TokenList tokenList);

			std::shared_ptr<AST::BreakStatement> parseBreakStatement(TokenList tokenList);

		}
	};
};

#endif // !_FLANER_COMPILER_PARSER_HH_
