#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>
#include <scanner.hh>
#include <declaration.hh>

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
			std::unique_ptr<AST::Identifier> parseIdentifier(std::unique_ptr<Lex::TokenList> tokenList)
			{
				std::unique_ptr<AST::Identifier> identifier = tokenList->now();
				return identifier;
			}

			// 调用此函数时，当前 token 是 '(' 或 identifier
			std::unique_ptr<AST::Value> parseValue(std::unique_ptr<Lex::TokenList> tokenList)
			{
				AST::Value value;
				Lex::Token now = tokenList->next();
				if (now.is(TOKEN_IDENTIFIER))
				{
					value.form = now;
					return value;
				}
				else if (now.is(TOKEN_PAREN_BEGIN))
				{
					AST::Expression expression;
					tokenList->next();
					expression = parseExpression(tokenList);
					return AST::Value(AST::Expression);
				}
				else if (now.is(TOKEN_NUMBER))
				{
					// 数字字面值

				}
				else if (now.is(TOKEN_STRING))
				{
					// 字符串字面值

				}
				else
				{
					// 这种情况不应当出现
					return nullptr;
				}
			}

			std::unique_ptr<AST::UnaryExpression> parseUnaryExpression(std::unique_ptr<Lex::TokenList> tokenList)
			{
				std::unique_ptr<AST::UnaryExpression> unaryExpression;

				// 当前 token 一定是一个 unary operator
				std::unique_ptr<AST::UnaryOperator> unaryOperator = tokenList->now();

				// 那么下一个 token 就应该是一个 value
				AST::Value value = parseValue(tokenList);

				if (value == nullptr)
				{
					syntax_error("Unexpected token")
				}

				unaryExpression->right = value;
				unaryExpression->op = unaryOperator;
				
				return value;
			}

			std::unique_ptr<AST::Expression> parseExpression(std::unique_ptr<Lex::TokenList> tokenList)
			{
				
			}

			// 当调用 parseExpression 时，当前 token 是 '('
			Expression parseExpression()
			{
				Expression expression;
				int parenCursor = 0;
				do
				{

					Token t = tokenList.next();
					if (t.is(TOKEN_PAREN_BEGIN))
					{
						parenCursor += 1;
					}

				} while (parenCursor > 0)

			}


			IfStatement parseIfStatement()
			{
				IfStatement ifStatement;
				int parenCursor = 0;
				if (!tokenList.next().is(TOKEN_PAREN_BEGIN))
				{
					syntax_error("mission a '(' after keyword if");
				}

				Expression expr;


		}
	};
};

#endif // !_FLANER_COMPILER_PARSER_HH_
