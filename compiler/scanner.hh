#ifndef _FLANER_COMPILER_SCANNER_HH_
#define _FLANER_COMPILER_SCANNER_HH_

/*
* File: scanner.hh
* Note：扫描源文件并进行词法分析，得到 token 列表
*/

#include <token.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Scanner
		{
			const char CR = '\r';
			const char LF = '\n';

			inline bool isWhitespace(char c);

			inline bool isWS(char c);

			inline bool isLetter(char c);

			inline bool isAlphanumeric(char c);

			inline bool isIDHead(char c);

			inline bool isIDTail(char c);

			inline bool isNonPrintable(char c);

			inline bool isPrintable(char c);

			inline bool isBinaryDigit(char c);

			inline bool isOctalDigit(char c);

			inline bool isDecimalDigit(char c);

			inline bool isHexadecimalDigit(char c);

			inline bool isBinaryDigits(char* s);

			inline bool isOctalDigits(char* s);

			inline bool isDecimalDigits(char* s);

			inline bool isHexadecimalDigits(char* s);

			bool isStingLiteral(char* s);

			bool isPunctuation(char s);

			bool isBeginPunctuation(char s);

		};
	};
};

#endif // !_FLANER_COMPILER_SCANNER_HH_
