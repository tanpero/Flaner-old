#include <expression.hh>
#include <parser.hh>
#include <algorithm>

namespace Flaner
{
	namespace Compiler
	{
		namespace Expr
		{

			uint16_t getPriority(std::shared_ptr<Lex::Token> token)
			{
				uint16_t priority;

				try
				{
					priority = priorityLookupTable.at(token->type);
				}
				catch (const std::exception&)
				{
					debug("Internal Error:"
						  "    At Expression Parser:"
						  "    Unable to identify the operator.\n");
					abort();
				}

				return priority;
			}

			

			uint16_t getOperatorParamsCount(Lex::TokenType op)
			{
				// ���ڲ��������ȼ����в�ѯ�˲�������
				//     ���û���ҵ���˵��������һ���������������ڲ�����
				// ���ߣ�����˲������ڵ�Ŀ�����������У����� 1
				//     ���򣬷��� 2
				// ��ʱ�ݲ�֧����Ŀ�����
				
				// TODO...
				// ��Ҫʹ�ø������ŵķ�ʽ��

				switch (op)
				{
				case Flaner::Compiler::Lex::TOKEN_BIT_NOT: 
				case Flaner::Compiler::Lex::TOKEN_LOGIC_NOT:
				case Flaner::Compiler::Lex::TOKEN_TYPEOF:				case Flaner::Compiler::Lex::TOKEN_DOT_DOT_DOT:
					return 1;
				case Flaner::Compiler::Lex::TOKEN_LOGIC_OR:				case Flaner::Compiler::Lex::TOKEN_BIT_OR:				case Flaner::Compiler::Lex::TOKEN_LOGIC_XOR:				case Flaner::Compiler::Lex::TOKEN_BIT_XOR:				case Flaner::Compiler::Lex::TOKEN_PIPELINE:				case Flaner::Compiler::Lex::TOKEN_EQUAL:				case Flaner::Compiler::Lex::TOKEN_NOT_EQUAL:				case Flaner::Compiler::Lex::TOKEN_LESS_THAN:				case Flaner::Compiler::Lex::TOKEN_GREATER_THAN:				case Flaner::Compiler::Lex::TOKEN_LESS_EQ_THAN:				case Flaner::Compiler::Lex::TOKEN_GREATER_EQ_THAN:				case Flaner::Compiler::Lex::TOKEN_SPACESHIP:				case Flaner::Compiler::Lex::TOKEN_ADD:				case Flaner::Compiler::Lex::TOKEN_SUB:				case Flaner::Compiler::Lex::TOKEN_MUL:				case Flaner::Compiler::Lex::TOKEN_DIV:				case Flaner::Compiler::Lex::TOKEN_MOD:				case Flaner::Compiler::Lex::TOKEN_POW:				case Flaner::Compiler::Lex::TOKEN_SAL:				case Flaner::Compiler::Lex::TOKEN_SRL:				case Flaner::Compiler::Lex::TOKEN_ROL:				case Flaner::Compiler::Lex::TOKEN_ROR:
					return 2;
				default:
					return 0;
				}
			}

			bool isIdentifier(TokenList tokenList)
			{
				return tokenList->now()->eq(Lex::TOKEN_ID);
			}

			bool isLiteral(TokenList tokenList)
			{
				std::shared_ptr<Lex::Token> token = tokenList->now();

				return token->eq(Lex::TOKEN_NUMBER)
					|| token->eq(Lex::TOKEN_BIGINT)
					|| token->eq(Lex::TOKEN_RATIONAL)
					|| token->eq(Lex::TOKEN_STRING)
					|| token->eq(Lex::TOKEN_TRUE)
					|| token->eq(Lex::TOKEN_FALSE)
					|| token->eq(Lex::TOKEN_NULL)
					|| token->eq(Lex::TOKEN_THIS);
			}

			bool isFunctionName(TokenList tokenList)
			{
				if (!isIdentifier(tokenList)
					|| tokenList->next()->noteq(Lex::TOKEN_PAREN_BEGIN))
				{
					return false;
				}

				return true;
			}
			
			bool isOperator(TokenList tokenList)
			{
				return static_cast<bool>(getOperatorParamsCount(tokenList));
			}


#define op_left_assoc(c) (c == '+' || c == '-' || c == '/' || c == '*' || c == '%')
#define is_operator(c)   (c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '%' || c == '=')
#define is_function(c)   (c >= 'A' && c <= 'Z')
#define is_ident(c)      ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))

			UnitStream shuntingYard(TokenList input)
			{
				std::shared_ptr<UnitStream> output = std::make_shared<UnitStream>();

				while (true)
				{
					std::shared_ptr<Lex::Token> token = input->now();

					if (isLiteral(input))
					{
						output->push(input->now());
					}
				}
			}


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
