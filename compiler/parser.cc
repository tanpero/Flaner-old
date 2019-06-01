#include <parser.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Parser
		{

			

			std::unique_ptr<AST::Identifier> parseIdentifier(std::unique_ptr<Lex::TokenList> tokenList)
			{
				std::unique_ptr<AST::Identifier> identifier = tokenList->now();
				return identifier;
			}

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

			Lex::TokenList std::unique_ptr<AST::Expression> parseExpression(std::unique_ptr<Lex::TokenList> tokenList)
			{
				return Lex::TokenList std::unique_ptr<AST::Expression>();
			}

		};
	};
};
