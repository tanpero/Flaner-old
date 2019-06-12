#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <statement.hh>

/*
* File: parser.hh
* Note: ���� token �б�����﷨����
*/

namespace Flaner
{
	namespace Compiler
	{
		namespace Parser
		{

			using TokenList = std::shared_ptr<Lex::TokenList>;

			std::shared_ptr<AST::NullStatement> parseNullStatement(TokenList tokenList);

			void checkWithSemicolon(TokenList tokenList);

			// ��Ϊ����
			std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList);
			std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList);

			// ��������ʵ����˵��
			std::shared_ptr<AST::Instantiation> parseInstantiation(TokenList tokenList);

			// ���� + ��ֵ���
			std::shared_ptr<AST::DefintionStatement> parseVariableDefintion(TokenList tokenList);
			std::shared_ptr<AST::DefintionStatement> parseConstantDefintion(TokenList tokenList);

			// ���������б�
			std::shared_ptr<AST::ParamsList> parseParameterList(TokenList tokenList);
			std::shared_ptr<AST::ParamsList> parseParameterListDeclaration(TokenList tokenList);

			//  ����ʱ�˺���ʱ����ǰ token �Ѿ��� identifier
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList);

			// ���ô˺���ʱ����ǰ token �� '(' �� identifier
			std::shared_ptr<AST::Value> parseValue(TokenList tokenList);

			// �����񶨱��ʽ
			std::shared_ptr<bool> parseNegationExpression(TokenList tokenList);

			// ����һ���飨�����ڿ�����ڣ�
			std::shared_ptr<AST::StatementSequence> parseBlock(TokenList tokenList);
			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList);

			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList);

			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList);

			std::shared_ptr<AST::Statement> parseStatement(TokenList tokenList);

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
