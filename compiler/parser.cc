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
				if (tokenList->now()->noteq(Lex::TOKEN_SEMICOLON))
				{
					return std::make_shared<AST::NullStatement>();
				}
				else
				{
					return nullptr;
				}
			}

			void checkWithSemicolon(TokenList tokenList)
			{
				if (tokenList->next()->noteq(Lex::TOKEN_SEMICOLON))
				{
					missing_semicolon_after_statement_syntax_error()
				}
			}


			std::shared_ptr<AST::Declaration> parseVariableDeclaration(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> now = tokenList->now();
				std::shared_ptr<Lex::Token> forward = tokenList->forward();

				if (now->noteq(Lex::TOKEN_LET))
				{
					return nullptr;
				}

				if (forward->noteq(Lex::TOKEN_ID))
				{
					unexpected_token_syntax_error(forward);
				}
				std::shared_ptr<AST::Declaration> declaration;
				declaration->kind = AST::Declaration::Variable;

				AST::Identifier id;
				id.name = forward->value;
				declaration->identifier = id;

				tokenList->forward();
				return declaration;
			}


			std::shared_ptr<AST::Declaration> parseConstantDeclaration(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> now = tokenList->now();
				std::shared_ptr<Lex::Token> forward = tokenList->forward();

				if (now->noteq(Lex::TOKEN_CONST))
				{
					return nullptr;
				}

				if (forward->noteq(Lex::TOKEN_ID))
				{
					unexpected_token_syntax_error(forward);
				}

				std::shared_ptr<AST::Declaration> declaration = std::make_shared<AST::Declaration>();

				declaration->kind = AST::Declaration::Constant;

				AST::Identifier id;
				id.name = forward->value;
				declaration->identifier = id;

				tokenList->forward();

				return declaration;

			}


			std::shared_ptr<AST::Instantiation> parseInstantiation(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_AS))
				{
					return nullptr;
				}

				std::shared_ptr<Lex::Token> id = tokenList->forward();
				if (id->noteq(Lex::TOKEN_ID))
				{
					unexpected_token_syntax_error(id)
				}
				
				AST::Identifier className;
				className.name = id->value;

				std::shared_ptr<AST::Instantiation> instantiation = std::make_shared<AST::Instantiation>();
				instantiation->className = className;

				tokenList->forward();

				return instantiation;
			}


			std::shared_ptr<AST::DefintionStatement> parseVariableDefintion(TokenList tokenList)
			{
				std::shared_ptr<AST::Declaration> declaration = parseVariableDeclaration(tokenList);

				// ����һ����������
				if (!declaration)
				{
					return nullptr;
				}

				// ��� instantiation Ϊ nullptr����ʡ��
				std::shared_ptr<AST::Instantiation> instantiation = parseInstantiation(tokenList);

				std::shared_ptr<AST::Value> initializer = std::make_shared<AST::Value>();
				
				// ���������û�и�ֵ��������ʼֵΪ nullptr
				if (tokenList->now()->noteq(Lex::TOKEN_ASSIGN))
				{
					initializer = nullptr;
					goto end;
				}
				
				tokenList->forward();

				initializer = parseValue(tokenList);

			end:
				std::shared_ptr<AST::DefintionStatement> defintionStatement = std::make_shared<AST::DefintionStatement>();
				defintionStatement->kind = declaration->kind;
				defintionStatement->identifier = declaration->identifier;
				defintionStatement->instantiation = instantiation;
				defintionStatement->initializer = initializer;

				checkWithSemicolon(tokenList);

				return defintionStatement;				
			}


			std::shared_ptr<AST::DefintionStatement> parseConstantDefintion(TokenList tokenList)
			{
				std::shared_ptr<AST::Declaration> declaration = parseConstantDeclaration(tokenList);

				// ����һ����������
				if (!declaration)
				{
					return nullptr;
				}

				// ��� instantiation Ϊ nullptr����ʡ��
				std::shared_ptr<AST::Instantiation> instantiation = parseInstantiation(tokenList);

				std::shared_ptr<AST::Value> initializer = std::make_shared<AST::Value>();

				// ��������ʱ���븳���ʼֵ
				if (tokenList->now()->noteq(Lex::TOKEN_ASSIGN))
				{
					missing_initializer_in_const_declaration_syntax_error(declaration->identifier)
				}

				tokenList->forward();

				initializer = parseValue(tokenList);

				std::shared_ptr<AST::DefintionStatement> defintionStatement = std::make_shared<AST::DefintionStatement>();
				defintionStatement->kind = declaration->kind;
				defintionStatement->identifier = declaration->identifier;
				defintionStatement->instantiation = instantiation;
				defintionStatement->initializer = initializer;

				checkWithSemicolon(tokenList);

				return defintionStatement;
			}

			std::shared_ptr<AST::ParamsList> parseParameterList(TokenList tokenList)
			{

				// һ����ʼ����Ĭ�ϲ�������ô���Ĳ������붼��Ĭ�ϲ���
				bool hasDefaultParam = false;
				std::shared_ptr<AST::ParamsList> paramsList = std::make_shared<AST::ParamsList>();
				std::shared_ptr<AST::Identifier> name = parseIdentifier(tokenList);

				// �����һ����ʶ��
				if (name)
				{
					while (true)
					{

						std::shared_ptr<Lex::Token> forward = tokenList->forward();
						if (forward->eq(Lex::TOKEN_COMMA))
						{
							// Ĭ��ʵ�κ�ֻ�ܸ���Ĭ��ʵ��
							if (hasDefaultParam)
							{
								syntax_error("After the default parameter can only follow the default parameter")
							}

							std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>(name);
							paramsList->insert(param);

							tokenList->forward();
							name = parseIdentifier(tokenList);
						}

						// ��һ��Ĭ��ʵ��
						else if (forward->eq(Lex::TOKEN_ASSIGN))
						{

							// ������ӦΪ���ʽ
							std::shared_ptr<Lex::Token> testToken = tokenList->forward();
							std::shared_ptr<AST::Expression> expr = parseExpression(tokenList);

							hasDefaultParam = true;

							// ��������
							if (!expr)
							{
								unexpected_token_syntax_error(testToken)
							}

							std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>(name);
							param->hasDefaultValue = true;
							param->defaultValueExpr = expr;
							param->isRest = false;

							paramsList->insert(param);

							tokenList->forward();
							name = parseIdentifier(tokenList);
						}

						break;

					}
				}

				if (tokenList->backward()->eq(Lex::TOKEN_DOT_DOT_DOT))
				{
					std::shared_ptr<AST::Param> param = std::make_shared<AST::Param>();

					param->isRest = true;

					tokenList->forward();

					std::shared_ptr<AST::Identifier> id = parseIdentifier(tokenList);

					if (tokenList->next()->noteq(Lex::TOKEN_PAREN_END))
					{
						if (tokenList->next()->eq(Lex::TOKEN_ASSIGN))
						{
							syntax_error("Rest parameter may not have a default initializer")
						}
						else
						{
							syntax_error("Rest parameter must be last formal parameter")
						}
					}

					if (!id)
					{
						unexpected_token_syntax_error(tokenList->next())
					}

					param->id = id;

					paramsList->insert(param);

					// rest �����������������������Ҳ������ΪĬ�ϲ���
					return paramsList;
				}
					
				else
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				return paramsList;
			}

			
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> token = tokenList->now();
				if (token->noteq(Lex::TOKEN_ID))
				{
					return nullptr;
				}

				std::shared_ptr<AST::Identifier> identifier;
				identifier->name = token->value;

				return identifier;
			}


			std::shared_ptr<AST::Value> parseValue(TokenList tokenList)
			{
				// TODO...
				return std::shared_ptr<AST::Value>();
			}

			std::shared_ptr<bool> parseNegationExpression(TokenList tokenList)
			{
				return std::shared_ptr<bool>();
			}

			// TODO...
			/*
			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList)
			{
				std::shared_ptr<AST::UnaryExpression> unaryExpression;

				std::shared_ptr<Lex::Token> token = tokenList->now();

				// ��⵱ǰ token �Ƿ�Ϊ unary operator
				// TODO...
				std::shared_ptr<AST::UnaryOperator> unaryOperator;
				unaryOperator->name = std::make_shared<std::shared_ptr<Lex::Token>(token);

				tokenList->forward();

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
			*/

			std::shared_ptr<AST::Expression> parseExpression(TokenList tokenList)
			{
				return std::shared_ptr<AST::Expression>();
			}

			std::shared_ptr<AST::Statement> parseStatement(TokenList tokenList)
			{
				return std::shared_ptr<AST::Statement>();
			}


			std::shared_ptr<AST::StatementSequence> parseBlock(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> first = tokenList->now();
				if (first->noteq(Lex::TOKEN_BRACE_BEGIN))
				{
					return nullptr;
				}

				tokenList->forward();

				std::shared_ptr<AST::StatementSequence> sequence = std::make_shared<AST::StatementSequence>();
				while (true)
				{
					std::shared_ptr<AST::Statement> statement = parseStatement(tokenList);
					if (!statement)
					{
						break;
					}
					sequence->insert(statement);
				}

				if (tokenList->forward()->noteq(Lex::TOKEN_BRACE_END))
				{
					unexpected_end_of_input_syntax_error(first);
				}


			}

			std::shared_ptr<AST::BlockStatement> parseBlockStatement(TokenList tokenList)
			{
				// TODO...

				// ʹ�ô����Ű����Ŀ���䣬��������Ӧ�����һ�� '}'
				if (tokenList->now()->eq(Lex::TOKEN_BRACE_BEGIN))
				{
					std::shared_ptr<AST::BlockStatement> blockStatement = std::make_shared<AST::BlockStatement>();
					blockStatement->body = parseBlock(tokenList);
					return blockStatement;
				}

				// ��������һ���ֺ�
				else
				{

				}

				return std::shared_ptr<AST::BlockStatement>();
			}

			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList)
			{
				return std::shared_ptr<AST::UnaryExpression>();
			}


			std::shared_ptr<AST::IfStatement> parseIfStatement(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_IF))
				{
					return nullptr;
				}

				if (tokenList->forward()->noteq(Lex::TOKEN_PAREN_BEGIN))
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

				std::shared_ptr<Lex::Token> next = tokenList->next();
				if (Scanner::isPunctuation(next->raw_value()) && !Scanner::isBeginPunctuation(next->raw_value()))
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
				std::shared_ptr<Lex::Token> token = tokenList->now();

				// ����ؼ��ֲ��� case����ô������Ϊ default �Ӿ�
				if (token->noteq(Lex::TOKEN_CASE))
				{
					return nullptr;
				}

				tokenList->forward();

				// ���ʽ������Ϻ󣬵�ǰ token Ӧ���� ':'
				std::shared_ptr<AST::Expression> expression = parseExpression(tokenList);
				
				token = tokenList->now();
				if (token->noteq(Lex::TOKEN_COLON))
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
				std::shared_ptr<Lex::Token> token = tokenList->now();

				// ������� defualt����ô��ȻҲ���� case���� parseSwitchClause �н���������
				if (token->noteq(Lex::TOKEN_DEFAULT))
				{
					return nullptr;
				}

				token = tokenList->forward();

				if (token->noteq(Lex::TOKEN_COLON))
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
				std::shared_ptr<Lex::Token> token = tokenList->now();

				if (token->noteq(Lex::TOKEN_BRACE_BEGIN))
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

				if (token->noteq(Lex::TOKEN_BRACE_END))
				{
					unexpected_token_syntax_error(token)
				}

				return clauseList;
			}


			std::shared_ptr<AST::SwitchStatement> parseSwitchStatement(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_SWITCH))
				{
					return nullptr;
				}

				std::shared_ptr<AST::SwitchStatement> switchStatement;

				std::shared_ptr<Lex::Token> now = tokenList->forward();

				// ����ؼ��ֺ���С����
				if (now->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					syntax_error("Invalid or unexpected token '" + now->value);
				}

				std::shared_ptr<AST::Expression> expression = parseExpression(tokenList);

				// ����ؼ��ֺ��Ǵ�����
				if (now->noteq(Lex::TOKEN_BRACE_BEGIN))
				{
					syntax_error("Invalid or unexpected token '" + now->value);
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
			{/*
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
				return initializer;*/
				return std::shared_ptr<AST::ForInitializer>();

			}


			std::shared_ptr<AST::ForStatement> parseForStatement(TokenList tokenList)
			{
				return std::shared_ptr<AST::ForStatement>();
			}

		};
	};
};

