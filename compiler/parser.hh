#ifndef _FLANER_COMPILER_PARSER_HH_
#define _FLANER_COMPILER_PARSER_HH_

#include <token.hh>

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
			Identifier parseIdentifier(Lex::TokenList* tokenList)
			{
				if (isIDHead())
			}


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
