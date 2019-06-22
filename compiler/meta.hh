#include <global.hh>
#include <memory>
#include <statement.hh>

namespace Flaner
{
	namespace Compiler
	{
		namespace Meta
		{
			class Operation
			{
				enum Operator
				{
					// 后缀运算符
					op_postfix_at = 12,  // []
					op_postfix_pow,      // **

					// 前缀运算符
					op_prefix_neg = 21,   // -
					op_prefix_notb = 22,  // ~
					op_prefix_notl = 23,  // !
					op_prefix_typeof,

					// 关系运算符
					op_infix_cmp_eq = 70,    // ==
					op_infix_cmp_ne = 71,    // !=
					op_infix_cmp_lt = 72,    // <
					op_infix_cmp_gt = 73,    // >
					op_infix_cmp_lte = 74,   // <=
					op_infix_cmp_gte = 75,   // >=
					op_infix_cmp_3way = 76,  // <=>

					// 通用运算符
					op_infix_add = 80,     // +
					op_infix_sub = 81,     // -
					op_infix_mul = 82,     // *
					op_infix_div = 83,     // /
					op_infix_mod = 84,     // %
					op_infix_sll = 85,     // <<<
					op_infix_srl = 86,     // >>>
					op_infix_sla = 87,     // <<
					op_infix_sra = 88,     // >>
					op_infix_andb = 89,    // &
					op_infix_orb = 90,     // |
					op_infix_xorb = 91,    // ^
					op_infix_assign = 92,  // =

				};




				struct Literal
				{
					std::shared_ptr<AST::Value> value;
				};

				struct FunctionCall
				{
					size_t length;
				};

				struct MemberAccess
				{
					std::string name;
				};

				struct ListLiteral
				{
					size_t length;
				};

				struct ObjectLiteral
				{
					std::vector<std::shared_ptr<std::string>> keys;
				};
			};
		}
	}
}
