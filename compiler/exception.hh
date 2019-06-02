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
			public:
				FlanerCompilerException(std::string info) : info(info) {}
				inline std::string what()
				{
					return "Error: " + info;
				}
			};

			class SyntaxError : public Error
			{
			public:
				SyntaxError(std::string info) : info(info) {}
				inline std::string what()
				{
					return "SyntaxError: " + info;
				}
			};

#define syntax_error(info) \
		throw new SyntaxError(info);

#define unexpected_token_syntax_error(token) \
	do \
	{ \
		switch (token.type) \
		{ \
		case TOKEN_UNKNOWN: \
			syntax_error("Invalid or unexpected token '" + token.value + "'") \
				break; \
		case TOKEN_ID: \
			syntax_error("Unexpected identifier") \
				break; \
		case TOKEN_NUMBER: \
			syntax_error("Unexpected number") \
				break; \
		case TOKEN_STRING: \
			syntax_error("Unexpected string") \
				break; \
		default: \
			syntax_error("Unexpected token" + token.value) \
				break; \
		} \
	} while (false); 

#endif // !_FLANER_COMPILER_EXCEPTION_HH_

