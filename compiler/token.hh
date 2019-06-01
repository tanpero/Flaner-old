#ifndef _FLANER_COMPILER_TOKEN_HH_
#define _FLANER_COMPILER_TOKEN_HH_

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

			};

			struct Token
			{
				TokenType type;
				std::string value;
				inline bool is(TokenType t)
				{
					return type == t;
				}
			};

			class TokenList
			{
				std::vector<Token> tokens;
			public:

				/*
				* 术语定义
				*         向后       当前      向前
				* 第一个 <------------#------------> 最后一个
				*/

				// 在末尾移入一个 token
				void push(Token token);

				// 移出并得到最后一个 token
				Token pop();

				// 设置游标位置
				void resetCursor(int n = 0);

				// 获取上一个 token，游标不变
				Token last();

				// 获取当前 token
				Token now();

				// 获取一个 token，游标不变
				Token next();

				// 将游标向前移动 n 个位置，并得到当前 token
				Token forward(int n);
				Token forward();

				// 将游标后前移动 n 个位置，并得到当前 token
				Token backward(int n);
				Token backward();

				// 获取第一个 token
				Token first();

				// 获取最后一个 token
				Token end();
				
			};
		};
	};
};

#endif // !_FLANER_COMPILER_TOKEN_HH_
