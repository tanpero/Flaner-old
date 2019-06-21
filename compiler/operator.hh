#include <global.hh>
#include <memory>

namespace Flaner
{
	namespace Compiler
	{
		namespace Op
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
		}
	}
}
