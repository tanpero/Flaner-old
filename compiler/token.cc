#include <token.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Lex
		{
			void TokenList::push(std::shared_ptr<Token> token)
			{
				tokens.push_back(token);
			}

			std::shared_ptr<Token> TokenList::pop()
			{
				std::shared_ptr<Token> end = *(tokens.end());
				tokens.pop_back();
				return end;
			}

			// 设置游标位置
			void TokenList::reset(unsigned int n)
			{
				cursor = n;
			}

			// 获取当前游标位置
			int TokenList::pos()
			{
				return cursor;
			}

			// 获取上一个 token，游标不变
			std::shared_ptr<Token> TokenList::last()
			{
				if (cursor == 0)
				{
					return nullptr;
				}
				return tokens.at(cursor - 1);
			}

			// 获取当前 token
			std::shared_ptr<Token> TokenList::now()
			{
				return tokens.at(cursor);
			}

			// 获取下一个 token，游标不变
			std::shared_ptr<Token> TokenList::next()
			{
				if (cursor == tokens.size() - 1)
				{
					return nullptr;
				}
				return tokens.at(cursor + 1);
			}

			// 将游标向前移动 n 个位置，并得到当前 token
			std::shared_ptr<Token> TokenList::forward(unsigned int n)
			{
				if (n >= tokens.size() - cursor)
				{
					// 超出 tokens 范围
					return nullptr;
				}
				else
				{
					cursor += n;
				}

				return tokens.at(cursor);
			}

			std::shared_ptr<Token> TokenList::forward()
			{
				return forward(1);
			}

			// 将游标后前移动 n 个位置，并得到当前 token
			std::shared_ptr<Token> TokenList::backward(unsigned int n)
			{
				if (n > cursor)
				{
					// 超出 tokens 范围
					return nullptr;
				}
				else
				{
					cursor -= n;
				}

				return tokens.at(cursor);
			}

			std::shared_ptr<Token> TokenList::backward()
			{
				return backward(1);
			}

			// 获取第一个 token
			std::shared_ptr<Token> TokenList::first()
			{
				return tokens.front();
			}

			// 获取最后一个 token
			std::shared_ptr<Token> TokenList::end()
			{
				return tokens.back();
			}
		}
	}
}
