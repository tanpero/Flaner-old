#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <statement.hh>
#include <meta.hh>
#include <expression.hh>

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
            

            std::shared_ptr<AST::EmptyStatement> parseEmptyStatement(TokenList tokenList);

            void checkWithSemicolon(TokenList tokenList);

            //std::shared_ptr<Expression::NumericValue> parseNumeric(TokenList tokenList);
            std::shared_ptr<Expr::Value> parseLiteralValue(TokenList tokenList);

            // 仅为声明
            std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList);
            std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList);

            // 对象类型实例化说明
            std::shared_ptr<AST::Instantiation> parseInstantiation(TokenList tokenList);

            // 初始化
            std::shared_ptr<AST::Expression> parseEqualInitializer(TokenList tokenList);

            // 声明 + 赋值语句
            std::shared_ptr<AST::DefintionStatement> parseVariableDefintion(TokenList tokenList);
            std::shared_ptr<AST::DefintionStatement> parseConstantDefintion(TokenList tokenList);

            // 函数参数列表
            std::shared_ptr<Expr::ParamsList> parseParameterList(TokenList tokenList);
            std::shared_ptr<Expr::ParamsList> parseParameterListDeclaration(TokenList tokenList);

            // 函数
            std::shared_ptr<Expr::Function> parseFunctionDefintion(TokenList tokenList);

            // 带分号的表达式语句
            std::shared_ptr<AST::Statement> parseExpressionStatement(TokenList tokenList);

            //  调用时此函数时，当前 token 已经是 identifier
            std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList);

            // 调用此函数时，当前 token 是 '(' 或 identifier
            std::shared_ptr<Expr::Value> parseValue(TokenList tokenList);

            // 解析否定表达式
            std::shared_ptr<bool> parseNegationExpression(TokenList tokenList);

			// TODO...
            std::shared_ptr<Expr::UnaryExpressionNode> parseUnaryExpression(TokenList tokenList);

            std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList);


            // 解析一个块（包含在块语句内）
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


            bool acceptPrefioperator(OperatorUnits& units, TokenList tokenList);

            bool acceptThis(OperatorUnits& units, TokenList tokenList);
            bool acceptListLiteral(OperatorUnits& units, TokenList tokenList);

        }
    };
};

#endif // !_FLANER_COMPILER_PARSER_HH_
