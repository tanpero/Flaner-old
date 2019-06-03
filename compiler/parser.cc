#include <parser.hh>
#include <scanner.hh>
#include <exception.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Parser
		{

			std::unique_ptr<AST::Identifier> parseIdentifier(TokenList tokenList)
			{
				std::unique_ptr<AST::Identifier> identifier = std::make_unique<AST::Identifier>(tokenList->now);

				return identifier;
			}

			
			std::unique_ptr<AST::Value> parseValue(TokenList tokenList)
			{
				// TODO...
				return std::unique_ptr<AST::Value>();
			}

			std::unique_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList)
			{
				std::unique_ptr<AST::UnaryExpression> unaryExpression;

				// 当前 token 一定是一个 unary operator
				std::unique_ptr<AST::UnaryOperator> unaryOperator = std::make_unique<AST::UnaryOperator>(tokenList->now());

				// 那么下一个 token 就应该是一个 value
				std::unique_ptr<AST::Value> value = std::make_unique<AST::Value>(parseValue(tokenList));

				if (value == nullptr)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				unaryExpression->right = std::make_unique<AST::Value>(value);
				unaryExpression->op = std::make_unique<AST::UnaryOperator>(unaryOperator);

				return unaryExpression;
			}

			std::unique_ptr<AST::Expression> parseExpression(TokenList tokenList)
			{
				return std::unique_ptr<AST::Expression>();
			}

			std::unique_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList)
			{
				// 使用大括号包裹的块语句，解析到对应的最后一个 '}'
				if (tokenList->now() == Lex::TOKEN_BRACE_BEGIN)
				{

				}

				// 解析到第一个分号
				else
				{

				}
			}

			std::unique_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList)
			{
				if (tokenList->now() != Lex::TOKEN_IF)
				{
					return nullptr;
				}

				if (tokenList->forward() != Lex::TOKEN_PAREN_BEGIN)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				std::unique_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				// 条件为空
				if (!expression)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				// 条件解析完毕，如果条件括号后的第一个 token 是起始括号以外的标点符号，
				// 说明混入了奇奇怪怪的东西

				Lex::Token next = tokenList->next();
				if (Scanner::isPunctuation(next.raw_value()) && !Scanner::isBeginPunctuation(next.raw_value()))
				{
					unexpected_token_syntax_error(next)
				}

				// 可能会抛出错误，否则一定获取了正确的值
				std::unique_ptr<AST::BlockStatement> body = parseBlockStatement(tokenList);

				std::unique_ptr<AST::IfStatement> ifStatement;

				ifStatement->condition = expression;
				ifStatement->body = body;

				return ifStatement;
			}

			std::unique_ptr<AST::CaseClause> parseCaseClause(TokenList tokenList)
			{
				Lex::Token token = tokenList->now();
				if (token != Lex::TOKEN_CASE)
				{
					return nullptr;
				}

				tokenList->forward();

				// 表达式解析完毕后，当前 token 应当是 ':'
				std::unique_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				token = tokenList->now();
				if (token != Lex::TOKEN_COLON)
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

			std::unique_ptr<AST::DefaultClause> parseDefaultClause(TokenList tokenList)
			{
				Lex::Token token = tokenList->now();

				if (token != Lex::TOKEN_DEFAULT)
				{
					return nullptr;
				}

				token = tokenList->forward();

				if (token != Lex::TOKEN_COLON)
				{
					unexpected_token_syntax_error(token)
				}

				tokenList->forward();

				std::unique_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				std::unique_ptr<AST::DefaultClause> clause;
				clause->body = block;

				return clause;
			}

			SwitchClause parseSwitchClause(TokenList tokenList)
			{
				std::variant<std::unique_ptr<AST::CaseClause>, std::unique_ptr<AST::DefaultClause>> clause;

				clause = parseCaseClause(tokenList);
				if (clause)
				{
					return clause;
				}

				clause = parseDefaultClause(tokenList);
				if (clause)
				{
					return clause;
				}

				return std::nullopt;
			}

			SwitchClauseList parseSwitchClauseList(TokenList)
			{
				Lex::Token token = tokenList->now();

				if (token != Lex::TOKEN_BRACE_BEGIN)
				{
					unexpected_token_syntax_error(token)
				}

				SwitchClauseList clauseList;

				while (true)
				{
					SwitchClause clause = parseSwitchClause(tokenList);

					if (!clause)
					{
						break;
					}

					clauseList.push_back(clause);
				}

				token = tokenList->forward();

				if (token != Lex::TOKEN_BRACE_END)
				{
					unexpected_token_syntax_error(token)
				}

				return clauseList;
			}

			std::unique_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList)
			{
				if (tokenList->now() != Lex::TOKEN_SWITCH)
				{
					return nullptr;
				}

				std::unique_ptr<AST::SwitchStatement> switchStatement;

				Lex::Token now = tokenList->forward();

				// 如果关键字后不是小括号
				if (now != Lex::TOKEN_PAREN_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				std::unique_ptr<AST::Expression> expression = parseExpression(tokenList);

				// 如果关键字后不是大括号
				if (now != Lex::TOKEN_BRACE_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				tokenList->forward();

				std::vector<std::unique_ptr<AST::CaseClause>> cases;
				std::unique_ptr<AST::CaseClause> oneCase;

				do
				{
					oneCase = parseCaseClause();
				} while (oneCase != nullptr);

			}

		};
	};
};

