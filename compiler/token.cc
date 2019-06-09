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

			// �����α�λ��
			void TokenList::reset(unsigned int n)
			{
				cursor = n;
			}

			// ��ȡ��ǰ�α�λ��
			int TokenList::pos()
			{
				return cursor;
			}

			// ��ȡ��һ�� token���α겻��
			std::shared_ptr<Token> TokenList::last()
			{
				if (cursor == 0)
				{
					return nullptr;
				}
				return tokens.at(cursor - 1);
			}

			// ��ȡ��ǰ token
			std::shared_ptr<Token> TokenList::now()
			{
				return tokens.at(cursor);
			}

			// ��ȡ��һ�� token���α겻��
			std::shared_ptr<Token> TokenList::next()
			{
				if (cursor == tokens.size() - 1)
				{
					return nullptr;
				}
				return tokens.at(cursor + 1);
			}

			// ���α���ǰ�ƶ� n ��λ�ã����õ���ǰ token
			std::shared_ptr<Token> TokenList::forward(unsigned int n)
			{
				if (n >= tokens.size() - cursor)
				{
					// ���� tokens ��Χ
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

			// ���α��ǰ�ƶ� n ��λ�ã����õ���ǰ token
			std::shared_ptr<Token> TokenList::backward(unsigned int n)
			{
				if (n > cursor)
				{
					// ���� tokens ��Χ
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

			// ��ȡ��һ�� token
			std::shared_ptr<Token> TokenList::first()
			{
				return tokens.front();
			}

			// ��ȡ���һ�� token
			std::shared_ptr<Token> TokenList::end()
			{
				return tokens.back();
			}
		}
	}
}
