#include <expression.hh>
#include <parser.hh>
#include <algorithm>

namespace Flaner
{
	namespace Compiler
	{
		namespace Expr
		{

			std::shared_ptr<ValueNode> parseValue(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> currentToken = tokenList->now();

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


			std::shared_ptr<UnaryExpressionNode> parseExpressionNeg(TokenList tokenList)
			{
				std::shared_ptr<UnaryExpressionNode> node = std::make_shared<UnaryExpressionNode>();
				
				if (tokenList->now()->eq(Lex::TOKEN_LOGIC_NOT))
				{
					std::shared_ptr<UnaryOperator> op = std::make_shared<UnaryOperator>(Meta::op_prefix_notl);
					op->priority = 
					node->op = op;
					
				}
			}

			std::shared_ptr<UnaryExpressionNode> parseExpressionNotB(TokenList tokenList)
			{
				return std::shared_ptr<UnaryExpressionNode>();
			}

			std::shared_ptr<UnaryExpressionNode> parseExpressionNotL(TokenList tokenList)
			{
				return std::shared_ptr<UnaryExpressionNode>();
			}

			std::shared_ptr<UnaryExpressionNode> parseExpressionTypeof(TokenList tokenList)
			{
				return std::shared_ptr<UnaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionAt(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionPow(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionAndL(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionOrL(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionPipeline(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionCoale(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<TernaryExpressionNode> parseExpressionBranch(TokenList tokenList)
			{
				return std::shared_ptr<TernaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionCompare(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionAdd(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionSub(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionMul(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionDiv(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionMod(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionSA(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionSL(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionAndB(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionOrB(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionXorB(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<BinaryExpressionNode> parseExpressionAssign(TokenList tokenList)
			{
				return std::shared_ptr<BinaryExpressionNode>();
			}

			std::shared_ptr<MemberAccessNode> parseMemberAccess(TokenList tokenList)
			{
				return std::shared_ptr<MemberAccessNode>();
			}

			std::shared_ptr<FunctionCallingNode> parseFunctionCalling(TokenList tokenList)
			{
				return std::shared_ptr<FunctionCallingNode>();
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

						// 遍历 operatorQueue 中所有优先级高于此运算符的运算符，并建立子表达式树
						for (auto i = operatorQueue->begin(); i != operatorQueue->end(); ++i)
						{
							// 如果优先级比 firstOp 的优先级低或平级，那么它不属于此子表达式的范围
							if ((*i)->priority <= firstOpPriority)
							{
								subOperatorQueue = std::make_shared<
									std::vector<OperatorQueue::element_type::value_type>>
									(operatorQueue->begin() + 2, // firstOp 后的第一个操作符
										*i);                     // 当前
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
