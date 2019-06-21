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
				prefix_plus,
				prefix_minus,
				prefix_negate,
				prefix_reserve,
				prefix_typeof,

				value_this,

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
		}
	}
}
