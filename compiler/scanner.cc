#include <scanner.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Scanner
		{
			bool isWhitespace(char c)
			{
				switch (static_cast<int>(c)))
				{
					case 0x09:
					case 0x0a:
					case 0x0b:
					case 0x0c:
					case 0x0d:
					case 0x20:
					case 0x85:
					case 0xA0:
						return true;
					default:
						return false;
				}
			}
			bool isWS(char c)
			{
				return isWhitespace(c) || c == CR || c == LF;
			}
			bool isLetter(char c)
			{
				return 'a' <= c && 'z' >= c || 'A' <= c && 'Z' >= c;
			}
			bool isAlphanumeric(char c)
			{
				return isLetter(c) || '0' <= c && '9' >= c;
			}
			bool isIDHead(char c)
			{
				return isLetter(c) || c == '_';
			}
			bool isIDTail(char c)
			{
				return isLetter(c) || isAlphanumeric(c);
			}
			bool isNonPrintable(char c)
			{
				return 0x00 <= c && 0x1f >= c;
			}
			bool isPrintable(char c)
			{
				return !isNonPrintable(c);
			}
			bool isBinaryDigit(char c)
			{
				return c == '0' || c == '1';
			}
			bool isOctalDigit(char c)
			{
				return '0' <= c && '7' >= c;
			}
			bool isDecimalDigit(char c)
			{
				return '0' <= c && '9' >= c;
			}
			bool isHexadecimalDigit(char c)
			{
				return isDecimalDigit(c) ||
					('A' <= c && 'F' >= c) ||
					('a' <= c && 'f' >= c);
			}
			bool isBinaryDigits(char * s)
			{
				size_t length = sizeof(s) / sizeof(char);
				for (size_t i = 0; i < length; ++i)
				{
					if (!isBinaryDigit(s[i]))
					{
						return false;
					}
				}
				return true;
			}
			bool isOctalDigits(char * s)
			{
				size_t length = sizeof(s) / sizeof(char);
				for (size_t i = 0; i < length; ++i)
				{
					if (!isOctalDigit(s[i]))
					{
						return false;
					}
				}
				return true;
			}
			bool isDecimalDigits(char * s)
			{
				size_t length = sizeof(s) / sizeof(char);
				for (size_t i = 0; i < length; ++i)
				{
					if (!isDecimalDigit(s[i]))
					{
						return false;
					}
				}
				return true;
			}
			bool isHexadecimalDigits(char * s)
			{
				bool isFraction = isExponent = false;
				size_t length = sizeof(s) / sizeof(char);
				for (size_t i = 0; i < length; ++i)
				{
					if (!isHexadecimalDigit(s[i]))
					{
						return false;
					}
				}
				return true;
			}
		};
	};
};
