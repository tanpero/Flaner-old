#include <parser.hh>
#include <scanner.hh>
#include <exception.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Parser
		{
			std::shared_ptr<AST::NullStatement> parseNullStatement(TokenList tokenList)
			{
				if (tokenList->now() == Lex::TOKEN_SEMICOLON)
				{
					return std::make_shared<AST::NullStatement>();
				}
				else
				{
					return nullptr;
				}
			}


			std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList)
			{
				Lex::Token now = tokenList->now();
				Lex::Token forward = tokenList->forward();

				if (now == Lex::TOKEN_LET)
				{
					if (forward != Lex::TOKEN_ID)
					{
						unexpected_token_syntax_error(forward);
					}
					std::shared_ptr<AST::Declaration> declaration;
					declaration->kind = AST::Declaration::Variable;

					std::shared_ptr<AST::Identifier> id;
					id->name = forward.value;
					declaration->identifier = id;

					tokenList->forward();
					return declaration;
				}
				else
				{
					return nullptr;
				}
			}


			std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList)
			{
				Lex::Token now = tokenList->now();
				Lex::Token forward = tokenList->forward();

				if (now == Lex::TOKEN_CONST)
				{
					if (forward != Lex::TOKEN_ID)
					{
						unexpected_token_syntax_error(forward);
					}

					std::shared_ptr<AST::Declaration> declaration;
					declaration->kind = AST::Declaration::Variable;

					std::shared_ptr<AST::Identifier> id;
					id->name = forward.value;
					declaration->identifier = id;

					tokenList->forward();
					return declaration;
				}
				else
				{
					return nullptr;
				}
			}


			std::shared_ptr<AST::Declaration> parseVariableDefintion(TokenList tokenList)
			{
				
			}


			std::shared_ptr<AST::Declaration> parseConstantDefintion(TokenList tokenList)
			{
				return std::shared_ptr<AST::Declaration>();
			}


			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList)
			{
				std::shared_ptr<AST::Identifier> identifier = std::make_shared<AST::Identifier>(tokenList->now());

				return identifier;
			}


			std::shared_ptr<AST::Value> parseValue(TokenList tokenList)
			{
				// TODO...
				return std::shared_ptr<AST::Value>();
			}


			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList)
			{
				std::shared_ptr<AST::UnaryExpression> unaryExpression;

				// ��ǰ token һ����һ�� unary operator
				std::shared_ptr<AST::UnaryOperator> unaryOperator = std::make_shared<AST::UnaryOperator>(tokenList->now());

				// ��ô��һ�� token ��Ӧ����һ�� value
				std::shared_ptr<AST::Value> value = std::make_shared<AST::Value>(parseValue(tokenList));

				if (value == nullptr)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				unaryExpression->right = std::make_shared<AST::Value>(value);
				unaryExpression->op = std::make_shared<AST::UnaryOperator>(unaryOperator);

				return unaryExpression;
			}


			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList)
			{
				return std::shared_ptr<AST::Expression>();
			}


			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList)
			{
				// ʹ�ô����Ű����Ŀ���䣬��������Ӧ�����һ�� '}'
				if (tokenList->now() == Lex::TOKEN_BRACE_BEGIN)
				{

				}

				// ��������һ���ֺ�
				else
				{

				}
			}


			std::shared_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList)
			{
				if (tokenList->now() != Lex::TOKEN_IF)
				{
					return nullptr;
				}

				if (tokenList->forward() != Lex::TOKEN_PAREN_BEGIN)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::Expression> expression = std::move(parseExpression(tokenList));
				
				// ����Ϊ��
				if (!expression)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				// ����������ϣ�����������ź�ĵ�һ�� token ����ʼ��������ı����ţ�
				// ˵������������ֵֹĶ���

				Lex::Token next = tokenList->next();
				if (Scanner::isPunctuation(next.raw_value()) && !Scanner::isBeginPunctuation(next.raw_value()))
				{
					unexpected_token_syntax_error(next)
				}

				// ���ܻ��׳����󣬷���һ����ȡ����ȷ��ֵ
				std::shared_ptr<AST::BlockStatement> body = parseBlockStatement(tokenList);

				std::shared_ptr<AST::IfStatement> ifStatement;

				ifStatement->condition = expression;
				ifStatement->body = body;
				
				return ifStatement;
			}


			std::shared_ptr<AST::SwitchClause> parseCaseClause(TokenList tokenList)
			{
				Lex::Token token = tokenList->now();

				// ����ؼ��ֲ��� case����ô������Ϊ default �Ӿ�
				if (token != Lex::TOKEN_CASE)
				{
					return nullptr;
				}

				tokenList->forward();

				// ���ʽ������Ϻ󣬵�ǰ token Ӧ���� ':'
				std::shared_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				token = tokenList->now();
				if (token != Lex::TOKEN_COLON)
				{
					unexpected_token_syntax_error(token);
				}

				tokenList->forward();
				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				std::shared_ptr<AST::SwitchClause> clause;
				clause->first = expression;
				clause->second = block;

				return clause;
			}

			
			std::shared_ptr<AST::SwitchClause> parseDefaultClause(TokenList tokenList)
			{
				Lex::Token token = tokenList->now();

				// ������� defualt����ô��ȻҲ���� case���� parseSwitchClause �н���������
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

				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				std::shared_ptr<AST::SwitchClause> clause;
				clause->first = nullptr;
				clause->second = block;

				return clause;
			}


			std::shared_ptr<AST::SwitchClause> parseSwitchClause(TokenList tokenList)
			{
				std::shared_ptr<AST::SwitchClause> clause;
				
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

				return nullptr;
			}


			std::shared_ptr<AST::SwitchClauseList> parseSwitchClauseList(TokenList tokenList)
			{
				Lex::Token token = tokenList->now();

				if (token != Lex::TOKEN_BRACE_BEGIN)
				{
					unexpected_token_syntax_error(token)
				}

				std::shared_ptr<AST::SwitchClauseList> clauseList;

				while (true)
				{
					std::shared_ptr<AST::SwitchClause> clause = parseSwitchClause(tokenList);

					if (!clause)
					{
						break;
					}
					clauseList->push_back(clause);
				}


				token = tokenList->forward();

				if (token != Lex::TOKEN_BRACE_END)
				{
					unexpected_token_syntax_error(token)
				}

				return clauseList;
			}


			std::shared_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList)
			{
				if (tokenList->now() != Lex::TOKEN_SWITCH)
				{
					return nullptr;
				}

				std::shared_ptr<AST::SwitchStatement> switchStatement;

				Lex::Token now = tokenList->forward();

				// ����ؼ��ֺ���С����
				if (now != Lex::TOKEN_PAREN_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				std::shared_ptr<AST::Expression> expression = parseExpression(tokenList);

				// ����ؼ��ֺ��Ǵ�����
				if (now != Lex::TOKEN_BRACE_BEGIN)
				{
					syntax_error("Invalid or unexpected token '" + now.value);
				}

				tokenList->forward();

				std::vector<std::shared_ptr<AST::SwitchClause>> cases;
				std::shared_ptr<AST::SwitchClause> oneCase;

				do
				{
					// TODO...
					oneCase = parseCaseClause(tokenList);
				} while (oneCase != nullptr);

			}


			std::shared_ptr<AST::ForInitializer> parseForInitializer(TokenList tokenList)
			{
				std::shared_ptr<AST::ForInitializer> initializer;
				initializer = parseNullStatement(tokenList);
				if (initializer)
				{
					return initializer;
				}

				initializer = parseVariableDefintion(tokenList);
				if (initializer)
				{
					return initializer;
				}

				initializer = parseConstantDefintion(tokenList);
				if (initializer)
				{
					return initializer;
				}

				initializer = parseExpression(tokenList);
				return initializer;
			}


			std::shared_ptr<AST::ForStatement> parseForStatement(TokenList tokenList)
			{
				return std::shared_ptr<AST::ForStatement>();
			}

		};
	};
};

