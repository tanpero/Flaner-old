#ifndef _FLANER_COMPILER_EXCEPTION_HH_
#define _FLANER_COMPILER_EXCEPTION_HH_

#include <global.hh>
#include <string>
#include <iostream>

namespace Flaner
{
	namespace Compiler
	{
		namespace Exception
		{
			class Error
			{
				std::string info;
				std::string type;
			public:
				Error() {}
				Error(std::string info) : info(info), type("Error") {}
				inline std::string what()
				{
					return type + ": " + info;
				}
			};

			class SyntaxError : public Error
			{
				std::string info;
				std::string type;
			public:
				SyntaxError() {}
				SyntaxError(std::string info) : info(info), type("Error") {}
			};

#define syntax_error(info) \
		throw new Exception::SyntaxError(info);

#define unexpected_token_syntax_error(token) \
	do \
	{ \
		switch (token.type) \
		{ \
		case Lex::TOKEN_UNKNOWN: \
			syntax_error("Invalid or unexpected token '" + token.value + "'") \
				break; \
		case Lex::TOKEN_ID: \
			syntax_error("Unexpected identifier") \
				break; \
		case Lex::TOKEN_NUMBER: \
			syntax_error("Unexpected number") \
				break; \
		case Lex::TOKEN_STRING: \
			syntax_error("Unexpected string") \
				break; \
		default: \
			syntax_error("Unexpected token" + token.value) \
				break; \
		} \
	} \
	while (false); 

#define compiler_warn(info) \
	do \
	{ \
\
	} \
	while (false);

		};

	};
};
#endif // !_FLANER_COMPILER_EXCEPTION_HH_

