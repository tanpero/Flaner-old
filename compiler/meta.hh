#include <global.hh>
#include <memory>
#include <statement.hh>

namespace Flaner
{
    namespace Compiler
    {
        namespace Meta
        {
			enum Operator
			{				
				// 前缀运算符
				op_prefix_neg,   // -
				op_prefix_notb,  // ~
				op_prefix_notl,  // !
				op_prefix_typeof,
				
				// 后缀运算符
				op_postfix_at,   // []
				op_postfix_pow,  // **
				
				// 逻辑运算符
				op_infix_andl,  // &&
				op_infix_orl,   // ||

				// 管道运算符
				op_infix_pipeline, // |>

				// 关系运算符
				op_infix_cmp_eq,    // ==
				op_infix_cmp_ne,    // !=
				op_infix_cmp_lt,    // <
				op_infix_cmp_gt,    // >
				op_infix_cmp_lte,   // <=
				op_infix_cmp_gte,   // >=
				op_infix_cmp_3way,  // <=>

				// 通用运算符
				op_infix_add,     // +
				op_infix_sub,     // -
				op_infix_mul,     // *
				op_infix_div,     // /
				op_infix_mod,     // %
				op_infix_sll,     // <<<
				op_infix_srl,     // >>>
				op_infix_sla,     // <<
				op_infix_sra,     // >>
				op_infix_andb,    // &
				op_infix_orb,     // |
				op_infix_xorb,    // ^
				op_infix_assign,  // =
			};


        }
    }
}
