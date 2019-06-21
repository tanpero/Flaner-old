#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <statement.hh>
#include <operator.hh>

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
			using OperatorUnits = std::shared_ptr<std::vector<std::shared_ptr<Op::Operator>>>;

			std::shared_ptr<AST::EmptyStatement> parseEmptyStatement(TokenList tokenList);

			void checkWithSemicolon(TokenList tokenList);

			std::shared_ptr<AST::Value> parseLiteralValue(TokenList tokenList);

			// ��Ϊ����
			std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList);
			std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList);

			// ��������ʵ����˵��
			std::shared_ptr<AST::Instantiation> parseInstantiation(TokenList tokenList);

			// ��ʼ��
			std::shared_ptr<AST::Expression> parseEqualInitializer(TokenList tokenList);

			// ���� + ��ֵ���
			std::shared_ptr<AST::DefintionStatement> parseVariableDefintion(TokenList tokenList);
			std::shared_ptr<AST::DefintionStatement> parseConstantDefintion(TokenList tokenList);

			// ���������б�
			std::shared_ptr<AST::ParamsList> parseParameterList(TokenList tokenList);
			std::shared_ptr<AST::ParamsList> parseParameterListDeclaration(TokenList tokenList);

			// ����
			std::shared_ptr<AST::FunctionValue> parseFunctionDefintion(TokenList tokenList);

			// ���ֺŵı��ʽ���
			std::shared_ptr<AST::Statement> parseExpressionStatement(TokenList tokenList);

			//  ����ʱ�˺���ʱ����ǰ token �Ѿ��� identifier
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList);

			// ���ô˺���ʱ����ǰ token �� '(' �� identifier
			std::shared_ptr<AST::Value> parseValue(TokenList tokenList);

			// �����񶨱��ʽ
			std::shared_ptr<bool> parseNegationExpression(TokenList tokenList);


			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList);

			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList);


			// ����һ���飨�����ڿ�����ڣ�
			std::shared_ptr<AST::StatementSequence> parseBlock(TokenList tokenList);
			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList);
			std::shared_ptr<AST::Statement> parseNonBlockStatement(TokenList tokenList);
			std::shared_ptr<AST::Statement> parseStatement(TokenList tokenList);


			std::shared_ptr<AST::ElseClause>  parseElseBranch(TokenList tokenList);
			std::shared_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList);


			std::shared_ptr<AST::SwitchClause> parseCaseClause(TokenList tokenList);
			std::shared_ptr<AST::SwitchClause> parseDefaultClause(TokenList tokenList);			
			std::shared_ptr<AST::SwitchClause> parseSwitchClause(TokenList tokenList);			
			std::shared_ptr<AST::SwitchClauseList> parseSwitchClauseList(TokenList);
			std::shared_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList);			


			std::shared_ptr<AST::DoWhileStatement> parseDoWhileStatement(TokenList tokenList);
			std::shared_ptr<AST::WhileStatement> parseWhileStatement(TokenList tokenList);


			std::shared_ptr<AST::ForInitializer> parseForInitializer(TokenList tokenList);
			std::shared_ptr<AST::ForComplementTriplet> parseForComplementTriplet(TokenList tokenList);
			std::shared_ptr<AST::ForInStatement> parseForInStatement(TokenList tokenList);
			std::shared_ptr<AST::ForOfStatement> parseForOfStatement(TokenList tokenList);
			std::shared_ptr<AST::Statement> parseForComplement(TokenList tokenList);
			std::shared_ptr<AST::Statement> parseForStatement(TokenList tokenList);


			std::shared_ptr<AST::LabelStatement> parseLabelStatement(TokenList tokenList);
			std::shared_ptr<AST::BreakStatement> parseBreakStatement(TokenList tokenList);
			std::shared_ptr<AST::ContinueStatement> parseContinueStatement(TokenList tokenList);

			std::shared_ptr<AST::ThrowStatement> parseThrowStatement(TokenList tokenList);
			std::shared_ptr<AST::ReturnStatement> parseReturnStatement(TokenList tokenList);

			std::shared_ptr<AST::TryCatchStatement::CatchClause> parseCatchClause(TokenList tokenList);
			std::shared_ptr<AST::TryCatchStatement> parseTryCatchStatement(TokenList tokenList);

			std::shared_ptr<AST::WithStatement> parseWithStatement(TokenList tokenList);

			std::shared_ptr<AST::ImportStatement> parseImportStatement(TokenList tokenList);
			std::shared_ptr<AST::ExportStatement> parseExportStatement(TokenList tokenList);
			std::shared_ptr<AST::ClassStatement> parseClassStatement(TokenList tokenList);
			std::shared_ptr<AST::DecoratorStatement> parseDecoratorStatement(TokenList tokenList);
			std::shared_ptr<AST::YieldStatement> parseYieldStatement(TokenList tokenList);


			bool acceptPrefixOperator(OperatorUnits& units, TokenList tokenList);

			bool acceptThis(OperatorUnits& units, TokenList tokenList);
			bool acceptListLiteral(OperatorUnits& units, TokenList tokenList);

		}
	};
};

#endif // !_FLANER_COMPILER_PARSER_HH_
