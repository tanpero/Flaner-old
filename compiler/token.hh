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

				// ����ȷ�� token �ķ�Χ
				inline bool is(TokenType t)
				{
					return type == t;
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
			};


			class TokenList
			{
				std::vector<Token> tokens;
			public:

				/*
				* ���ﶨ��
				*         ���       ��ǰ      ��ǰ
				* ��һ�� <------------#------------> ���һ��
				*/

				// ��ĩβ����һ�� token
				void push(Token token);

				// �Ƴ����õ����һ�� token
				Token pop();

				// �����α�λ��
				void reset(int n = 0);

				// ��ȡ��ǰ�α�λ��
				int pos();

				// ��ȡ��һ�� token���α겻��
				Token last();

				// ��ȡ��ǰ token
				Token now();

				// ��ȡһ�� token���α겻��
				Token next();

				// ���α���ǰ�ƶ� n ��λ�ã����õ���ǰ token
				Token forward(int n);
				Token forward();

				// ���α��ǰ�ƶ� n ��λ�ã����õ���ǰ token
				Token backward(int n);
				Token backward();

				// ��ȡ��һ�� token
				Token first();

				// ��ȡ���һ�� token
				Token end();
				
			};
		};
	};
};

#endif // !_FLANER_COMPILER_TOKEN_HH_
