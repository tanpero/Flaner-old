#include <expression.hh>
#include <parser.hh>
#include <algorithm>

namespace Flaner
{
	namespace Compiler
	{
		namespace Expr
		{

			ValueNode parseValue(std::shared_ptr<Lex::TokenList> tokenList)
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
					
					default:
						break;
				}
			}


			/* std::shared_ptr<Expression> makeExpressionTree(OperatorQueue operatorQueue, ValueQueue valueQueue)
			{
				auto firstOp = operatorQueue->front();

				//std::shared_ptr<Expression> root;
				std::shared_ptr<ExpressionNode> root = std::make_shared<ExpressionNode>();

				switch (firstOp->target)
				{
				case Meta::target_unary:

					std::shared_ptr<UnaryExpressionNode> unary = std::make_shared<UnaryExpressionNode>();

					switch (firstOp->kind)
					{
					case Meta::op_prefix_notl:
						unary->op = std::make_shared<UnaryOperator>(UnaryOperator::Kind::LOGIC_NOT);

						uint8_t firstOpPriority = firstOp->priority;

						OperatorQueue subOperatorQueue;

						// ���� operatorQueue ���������ȼ����ڴ����������������������ӱ��ʽ��
						for (auto i = operatorQueue->begin(); i != operatorQueue->end(); ++i)
						{
							// ������ȼ��� firstOp �����ȼ��ͻ�ƽ������ô�������ڴ��ӱ��ʽ�ķ�Χ
							if ((*i)->priority <= firstOpPriority)
							{
								subOperatorQueue = std::make_shared<
									std::vector<OperatorQueue::element_type::value_type>>
									(operatorQueue->begin() + 2, // firstOp ��ĵ�һ��������
										*i);                     // ��ǰ
								break;
							}
						}

						break;

					case Meta::op_prefix_notb:
						unary.op = UnaryOperator::Kind

					default:
						break;
					}

					root->node = unary;
				default:
					break;
				}
				//std::shared_ptr<Expression> root = std::make_shared<Expression>();
				Expression root;
			}
		}
	}
}

}*/
		};
	};
};
