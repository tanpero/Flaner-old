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

			// ��鵱ǰ token ����һ�� token �Ƿ�Ϊ�ֺ�
			void checkWithSemicolon(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_SEMICOLON) && tokenList->next()->noteq(Lex::TOKEN_SEMICOLON))
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

			std::shared_ptr<AST::Expression> parseEqualInitializer(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_ASSIGN))
				{
					return nullptr;
				}

				tokenList->forward();

				return parseExpression(tokenList);
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

				std::shared_ptr<AST::Expression> initializer = std::make_shared<AST::Expression>();
				
				// ���������û�и�ֵ��������ʼֵΪ nullptr
				initializer = parseEqualInitializer(tokenList);

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

				initializer->form = parseExpression(tokenList);

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
							paramsList->insert(std::make_shared<AST::Param>(name));
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

				if (tokenList->forward()->eq(Lex::TOKEN_DOT_DOT_DOT))
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

				return paramsList;
			}

			std::shared_ptr<AST::ParamsList> parseParameterListDeclaration(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					return nullptr;
				}

				tokenList->forward();

				std::shared_ptr<AST::ParamsList> paramsList = parseParameterList(tokenList);

				if (tokenList->forward()->noteq(Lex::TOKEN_PAREN_END))
				{
					unclosing_parentheses_syntax_error()
				}
				
				tokenList->forward();
				
				return paramsList;
			}

			/*
			*
			* (a, b = false) => doSomething(a, b);
			* 
			* (...args) => {
			*     print(args.max);
			* };
			*
			*/
			std::shared_ptr<AST::FunctionValue> parseFunctionDefintion(TokenList tokenList)
			{
				std::shared_ptr<AST::FunctionValue> function = std::shared_ptr<AST::FunctionValue>();
				
				// �� parameterList Ϊ nullptr��˵���β��б�Ϊ��
				std::shared_ptr<AST::ParamsList> parameterList = parseParameterListDeclaration(tokenList);
								
				if (tokenList->now()->noteq(Lex::TOKEN_FUNCTION_ARROW))
				{
					// ���������Ű����ı��ʽ
					return nullptr;
				}

				if (tokenList->forward()->eq(Lex::TOKEN_BRACE_BEGIN))
				{
					std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);
					std::shared_ptr<AST::StatementSequence> body = std::make_shared<AST::StatementSequence>();
					body->insert(block);
					function->body = body;
				}

				else
				{
					std::shared_ptr<AST::Expression> expr = parseExpression(tokenList);

					if (!expr)
					{
						unexpected_token_syntax_error(tokenList->now())
					}

					std::shared_ptr<AST::ReturnStatement> returnStatement = std::make_shared<AST::ReturnStatement>();
					std::shared_ptr<AST::Value> value = std::make_shared<AST::Value>(expr);
					returnStatement->value = value;

					std::shared_ptr<AST::StatementSequence> body = std::make_shared<AST::StatementSequence>();
					body->insert(returnStatement);
					function->body = body;
				}

				function->paramsList = parameterList;
				return function;
			}

			std::shared_ptr<AST::Statement> parseExpressionStatement(TokenList tokenList)
			{
				std::shared_ptr<AST::Expression> expr = parseExpression(tokenList);

				if (!expr)
				{
					return nullptr;
				}

				checkWithSemicolon(tokenList);

				tokenList->forward();
			}

			
			std::shared_ptr<AST::Identifier> parseIdentifier(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> token = tokenList->now();
				if (token->noteq(Lex::TOKEN_ID))
				{
					return nullptr;
				}

				std::shared_ptr<AST::Identifier> identifier =
					std::make_shared<AST::Identifier>(token->value);

				tokenList->forward();

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

				std::shared_ptr<AST::BlockStatement> blockStatement = std::make_shared<AST::BlockStatement>();

				// ʹ�ô����Ű����Ŀ���䣬��������Ӧ�����һ�� '}'
				if (tokenList->now()->eq(Lex::TOKEN_BRACE_BEGIN))
				{
					blockStatement->body = parseBlock(tokenList);

					if (!blockStatement)
					{
						return nullptr;
					}
				}

				return nullptr;
			}

			std::shared_ptr<AST::UnaryExpression> parseUnaryExpression(TokenList tokenList)
			{
				return std::shared_ptr<AST::UnaryExpression>();
			}


			std::shared_ptr<AST::ElseClause> parseElseBranch(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_ELSE))
				{
					return nullptr;
				}

				tokenList->forward();

				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				if (!block)
				{
					unexpected_end_of_input_syntax_error(tokenList->now())
				}
				
				std::shared_ptr<AST::ElseClause> clause = std::make_shared<AST::ElseClause>();
				clause->body = block;

				return clause;
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

				tokenList->forward();
				ifStatement->branch = parseElseBranch(tokenList);
				
				tokenList->forward();
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

			std::shared_ptr<AST::DoWhileStatement> parseDoWhileStatement(TokenList tokenList)
			{

				if (tokenList->now()->noteq(Lex::TOKEN_DO))
				{
					return nullptr;
				}

				tokenList->forward();

				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				if (!block)
				{
					unexpected_end_of_input_syntax_error(tokenList->last())
				}

				if (tokenList->now()->noteq(Lex::TOKEN_WHILE))
				{
					return nullptr;
				}

				if (tokenList->forward()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					unexpected_token_syntax_error(tokenList->now())
				}
				
				std::shared_ptr<AST::Expression> cond = parseExpression(tokenList);

				if (!cond)
				{
					unexpected_token_syntax_error(tokenList->last())
				}
				
				checkWithSemicolon(tokenList);

				tokenList->forward();

				std::shared_ptr<AST::DoWhileStatement> doWhileStatement = std::make_shared<AST::DoWhileStatement>();
				doWhileStatement->condition = cond;
				doWhileStatement->body = block;

				return doWhileStatement;
			}

			std::shared_ptr<AST::WhileStatement> parseWhileStatement(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_WHILE))
				{
					return nullptr;
				}
				
				tokenList->forward();

				std::shared_ptr<AST::Expression> cond = parseExpression(tokenList);

				if (!cond)
				{
					unexpected_token_syntax_error(tokenList->last())
				}

				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);

				if (!block)
				{
					unexpected_end_of_input_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::WhileStatement> whileStatement = std::make_shared<AST::WhileStatement>();
				whileStatement->condition = cond;
				whileStatement->body = block;

				return whileStatement;
			}


			std::shared_ptr<AST::ForInitializer> parseForInitializer(TokenList tokenList)
			{
				std::shared_ptr<AST::ForInitializer> initializer;
				initializer = std::make_shared<AST::ForInitializer>(parseNullStatement(tokenList));
				if (initializer)
				{
					return initializer;
				}

				initializer = std::make_shared<AST::ForInitializer>(parseVariableDefintion(tokenList));
				if (initializer)
				{
					return initializer;
				}

				initializer = std::make_shared<AST::ForInitializer>(parseConstantDefintion(tokenList));
				if (initializer)
				{
					return initializer;
				}

				initializer = std::make_shared<AST::ForInitializer>(parseExpression(tokenList));
				return initializer;
			}

			std::shared_ptr<AST::ForComplementTriplet> parseForComplementTriplet(TokenList tokenList)
			{
				std::shared_ptr<AST::ForInitializer> initializer = parseForInitializer(tokenList);
				if (tokenList->now()->noteq(Lex::TOKEN_SEMICOLON))
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::Expression> condition = parseExpression(tokenList);
				if (tokenList->now()->noteq(Lex::TOKEN_SEMICOLON))
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::Expression> increment = parseExpression(tokenList);

				if (tokenList->now()->noteq(Lex::TOKEN_PAREN_END))
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::BlockStatement> block = parseBlockStatement(tokenList);
				if (!block)
				{
					unexpected_end_of_input_syntax_error(tokenList->now())
				}

				std::shared_ptr<AST::ForComplementTriplet> triplet = std::make_shared<AST::ForComplementTriplet>();
				triplet->initializer = initializer;
				triplet->condition = condition;
				triplet->increment = increment;
				triplet->body = block;

				return triplet;
			}


			std::shared_ptr<AST::ForStatement> parseForStatement(TokenList tokenList)
			{
				return std::shared_ptr<AST::ForStatement>();
			}

			std::shared_ptr<AST::ForInStatement> parseForInStatement(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_FOR))
				{
					return nullptr;
				}

				if (tokenList->forward()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				tokenList->forward();

				std::shared_ptr<AST::Declaration> binding = parseVariableDeclaration(tokenList);

				// û��ʹ�� let �����������Ѿ����ⲿ��������ʶ��
				if (!binding)
				{
					std::shared_ptr<AST::Identifier> id = parseIdentifier(tokenList);

					if (!id)
					{
						unexpected_token_syntax_error(tokenList->now())
					}

					binding->kind = binding->Variable;
					binding->identifier = id;
				}

				// û��ʹ�� in �ؼ���
				if (tokenList->now()->noteq(Lex::TOKEN_IN))
				{
					return nullptr;
				}

				std::shared_ptr<AST::Expression> expr = parseExpression(tokenList);
				if (!expr)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				if (tokenList->now()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					unclosing_parentheses_syntax_error()
				}

				std::shared_ptr<Lex::Token> braceBegin = tokenList->forward();

				std::shared_ptr<AST::BlockStatement> body = parseBlockStatement(tokenList);
				if (!body)
				{
					unexpected_end_of_input_syntax_error(braceBegin)
				}

				std::shared_ptr<AST::ForInStatement> forInStatement = std::make_shared<AST::ForInStatement>();
				forInStatement->binding = binding;
				forInStatement->target = expr;
				forInStatement->body = body;

				return forInStatement;
			}

			std::shared_ptr<AST::ForOfStatement> parseForOfStatement(TokenList tokenList)
			{
				if (tokenList->now()->noteq(Lex::TOKEN_FOR))
				{
					return nullptr;
				}

				if (tokenList->forward()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				tokenList->forward();

				std::shared_ptr<AST::Declaration> binding = parseVariableDeclaration(tokenList);

				// û��ʹ�� let �����������Ѿ����ⲿ��������ʶ��
				if (!binding)
				{
					std::shared_ptr<AST::Identifier> id = parseIdentifier(tokenList);

					if (!id)
					{
						unexpected_token_syntax_error(tokenList->now())
					}

					binding->kind = binding->Variable;
					binding->identifier = id;
				}

				// û��ʹ�� in �ؼ���
				if (tokenList->now()->noteq(Lex::TOKEN_OF))
				{
					return nullptr;
				}

				std::shared_ptr<AST::Expression> expr = parseExpression(tokenList);
				if (!expr)
				{
					unexpected_token_syntax_error(tokenList->now())
				}

				if (tokenList->now()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					unclosing_parentheses_syntax_error()
				}

				std::shared_ptr<Lex::Token> braceBegin = tokenList->forward();

				std::shared_ptr<AST::BlockStatement> body = parseBlockStatement(tokenList);
				if (!body)
				{
					unexpected_end_of_input_syntax_error(braceBegin)
				}

				std::shared_ptr<AST::ForOfStatement> forOfStatement = std::make_shared<AST::ForOfStatement>();
				forOfStatement->binding = binding;
				forOfStatement->target = expr;
				forOfStatement->body = body;

				return forOfStatement;
				
			}

		};
	};
};

