#include <parser.hh>
#include <exception.hh>

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
				Lex::Token now = tokenList->forward();

				if (now == TOKEN_IDENTIFIER)
				{
					value.form = now;
					return value;
				}

				else if (now == TOKEN_PAREN_BEGIN)
				{
					AST::Expression expression;
					tokenList->forward();
					expression = parseExpression(tokenList);
					return AST::Value(AST::Expression);
				}

				else if (now == TOKEN_NUMBER)
				{
					// 数字字面值

				}

				else if (now == TOKEN_STRING)
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

			std::unique_ptr<AST::BlockStatement> parseBlockStatement(std::unique_ptr<Lex::TokenList> tokenList)
			{
				if (tokenList->now())
			}

			std::unique_ptr<AST::IfStatement> parseIfStatement(std::unique_ptr<Lex::TokenList> tokenList)
			{
				if (tokenList->now() != TOKEN_IF)
				{
					return nullptr;
				}

				if (tokenList->forword() != TOKEN_PAREN_BEGIN)
				{
					syntax_error("mission '(' after keyword if");
				}

				std::unique_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				// 条件为空
				if (!expression)
				{
					syntax_error("Unexpected token ')'");
				}

				// 条件解析完毕，如果条件括号后的第一个 token 是起始括号以外的标点符号，
				// 说明混入了奇奇怪怪的东西
				if (tokenList->next().is(PUNCTUATION) && !tokenList->next().is(BEGIN_PUNCTUATION))
				{
					syntax_error(std::string("Invalid or unexpected token" + tokenList->next());
				}

				// 可能会抛出错误，否则一定获取了正确的值
				std::unique_ptr<AST::BlockStatement> body = parseBlockStatement(tokenList);

				std::unique_ptr<AST::IfStatement> ifStatement;

				ifStatement->condition = expression;
				ifStatement->body = body;

				return ifStatement;
			}

			std::unique_ptr<AST::CaseClause> parseCaseClause(std::unique_ptr<Lex::TokenList> tokenList)
			{
				Lex::Token token = tokenList->now();
				if (token != TOKEN_CASE)
				{
					unexpected_token_syntax_error(token);
				}

				tokenList->forward();

				// 表达式解析完毕后，当前 token 应当是 ':'
				std::unique_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				token = tokenList->now();
				if (token != TOKEN_COLON)
				{
					unexpected_token_syntax_error(token);
				}

				tokenList->forward();
				std::unique_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				std::unique_ptr<AST::CaseClause> caseClause;
				caseClause->object = expression;
				caseClause->body = block;
				return caseClause;
			}

			std::unique_ptr<AST::SwitchStatement> parseSwitchStatement(std::unique_ptr<Lex::TokenList> tokenList)
			{
				if (tokenList->now() != TOKEN_SWITCH)
				{
					return nullptr;
				}

				std::unique_ptr<AST::SwitchStatement> switchStatement;

				Lex::Token now = tokenList->forward();

				// 如果关键字后不是小括号
				if (now != TOKEN_PAREN_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				AST::Expression expression = parseExpression(tokenList);

				// 如果关键字后不是大括号
				if (now != TOKEN_BRACE_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				tokenList->forward();

				std::vector<std::unique_ptr<CaseClause>> cases;
				std::unique_ptr<CaseClause> oneCase;

				do
				{
					oneCase = parseCaseClause();
				} while (oneCase != nullptr);

				while (one)
			}

		};
	};
};
