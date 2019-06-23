/*#include <expression.hh>
#include <parser.hh>
#include <algorithm>

namespace Flaner
{
	namespace Compiler
	{
		namespace Expression
		{

			Unit makeUnit(std::shared_ptr<Lex::TokenList> tokenList)
			{
				std::shared_ptr<Lex::Token> currentToken = tokenList->now();
				Unit unit;

				switch (currentToken->type)
				{
				case Lex::TOKEN_NUMBER:
					Numeric numeric = (currentToken->value.c_str());
					NumericValue value(numeric);
					unit = value;
					return unit;
				case Lex::TOKEN_STRING:
					StringValue value(currentToken->value);
				default:
					break;
				}
			}


			bool ExpressionQueue::push(Unit token)
			{
				switch (switch_on)
				{
					case 
				default:
					break;
				}
			}
		}
	}
}
/*