#ifndef _FLANER_COMPILER_TOKEN_HH_
#define _FLANER_COMPILER_TOKEN_HH_

/*
* File: token.hh
* ���� token ģ�ͺ��б�
*/

#include <string>
#include <vector>

namespace Flaner
{
	namespace Compiler
	{
		namespace Lex
		{
			enum TokenType
			{
				TOKEN_UNKNOWN,

				TOKEN_ID,

				TOKEN_NUMBER,
				TOKEN_STRING,

				TOKEN_LET,
				TOKEN_CONST,

				TOKEN_IF,
				TOKEN_ELSE,
				TOKEN_SWITCH,
				TOKEN_CASE,
				TOKEN_DEFAULT,
				TOKEN_WHILE,
				TOKEN_DO,
				TOKEN_FOR,
				TOKEN_CONTINUE,
				TOKEN_BREAK,
				TOKEN_RETURN,
				
				TOKEN_PAREN_BEGIN,
				TOKEN_PAREN_END,
				TOKEN_BRACKET_BEGIN,
				TOKEN_BRACKET_END,
				TOKEN_BRACE_BEGIN,
				TOKEN_BRACE_END,

				TOKEN_ASSIGN,

				TOKEN_COLON,
				TOKEN_COMMA,
				TOKEN_DOT,
				TOKEN_DOT_DOT_DOT,
				TOKEN_QUESTION,
				TOKEN_SEMICOLON
			};

			struct Token
			{
				TokenType type;
				std::string value;

				inline char raw_value()
				{
					return value.data()[0];
				}

				// ���·�������ȷ�� token �ķ�Χ

				inline bool isStringLiteral()
				{
					return this->type == TOKEN_STRING;
				}

				inline bool isNumberLiteral()
				{
					return this->type == TOKEN_NUMBER;
				}


				// ����ȷ�� token �Ƿ���ָ���������
				inline bool operator==(TokenType t)
				{
					return type == t;
				}

				inline bool operator!=(TokenType t)
				{
					return type != t;
				}

				inline bool eq(TokenType t)
				{
					return *this == t;
				}

				inline bool noteq(TokenType t)
				{
					return *this != t;
				}
			};


			class TokenList
			{
				std::vector<std::shared_ptr<Token>> tokens;
				unsigned int cursor;
			public:

				/*
				* ���ﶨ��
				*         ���       ��ǰ      ��ǰ
				* ��һ�� <------------#------------> ���һ��
				*/

				// ��ĩβ����һ�� token
				void push(std::shared_ptr<Token> token);

				// �Ƴ����õ����һ�� token
				std::shared_ptr<Token> pop();

				// �����α�λ��
				void reset(unsigned int n = 0);

				// ��ȡ��ǰ�α�λ��
				int pos();

				// ��ȡ��һ�� token���α겻��
				std::shared_ptr<Token> last();

				// ��ȡ��ǰ token
				std::shared_ptr<Token> now();

				// ��ȡ��һ�� token���α겻��
				std::shared_ptr<Token> next();

				// ���α���ǰ�ƶ� n ��λ�ã����õ���ǰ token
				std::shared_ptr<Token> forward(unsigned int n);
				std::shared_ptr<Token> forward();

				// ���α��ǰ�ƶ� n ��λ�ã����õ���ǰ token
				std::shared_ptr<Token> backward(unsigned int n);
				std::shared_ptr<Token> backward();

				// ��ȡ��һ�� token
				std::shared_ptr<Token> first();

				// ��ȡ���һ�� token
				std::shared_ptr<Token> end();
				
			};
		};
	};
};

#endif // !_FLANER_COMPILER_TOKEN_HH_
