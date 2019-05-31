#include <bigint.hh>

namespace Flaner
{
	namespace Runtime
	{
		namespace numeric
		{

			Bigint::Bigint()
			{
			}


			Bigint::Bigint(long long v)
			{
			}


			Bigint::Bigint(std::string & s)
			{
			}


			void Bigint::operator=(const Bigint &v)
			{
			}


			void Bigint::operator=(long long v)
			{
			}


			Bigint Bigint::operator+(const Bigint &v) const
			{
			}


			Bigint Bigint::operator-(const Bigint &v) const
			{
			}


			void Bigint::operator*=(int v)
			{
			}


			Bigint Bigint::operator*(int v) const
			{
			}


			void Bigint::operator*=(long long v)
			{
			}


			Bigint Bigint::operator*(long long v) const
			{
			}


			int size()
			{
			}


			Bigint Bigint::operator ^ (const Bigint &v)
			{
			}


			std::string toString()
			{
			}


			int sumOf()
			{
			}


			std::pair<Bigint, Bigint> divmod(const Bigint &a1, const Bigint &b1)
			{
			}



			Bigint Bigint::operator/(const Bigint &v) const
			{
			}


			Bigint Bigint::operator%(const Bigint &v) const
			{
			}


			void Bigint::operator/=(int v)
			{
			}


			Bigint Bigint::operator/(int v) const
			{
			}


			int Bigint::operator%(int v) const
			{
			}



			void Bigint::operator+=(const Bigint &v)
			{
			}


			void Bigint::operator-=(const Bigint &v)
			{
			}


			void Bigint::operator*=(const Bigint &v)
			{
			}


			void Bigint::operator/=(const Bigint &v)
			{
			}



			bool Bigint::operator<(const Bigint &v) const
			{
			}


			bool Bigint::operator>(const Bigint &v) const
			{
			}


			bool Bigint::operator<=(const Bigint &v) const
			{
			}


			bool Bigint::operator>=(const Bigint &v) const
			{
			}


			bool Bigint::operator==(const Bigint &v) const
			{
			}


			bool Bigint::operator!=(const Bigint &v) const
			{
			}


			void Bigint::trim()
			{
			}


			bool Bigint::isZero() const
			{
			}


			Bigint Bigint::operator-() const
			{
			}


			Bigint Bigint::abs() const
			{
			}



			long long Bigint::longValue() const
			{
			}


			Bigint Bigint::gcd(const Bigint &a, const Bigint &b)
			{
			}


			Bigint Bigint::lcm(const Bigint &a, const Bigint &b)
			{
			}



			void Bigint::read(const std::string &s)
			{
			}



			std::istream& operator>>(std::istream &stream, Bigint &v)
			{
			}


			std::ostream& operator<<(std::ostream &stream, const Bigint &v)
			{
			}



			static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits)
			{
			}


			typedef std::vector<long long> vll;

			static vll karatsubaMultiply(const vll &a, const vll &b)
			{
			}


			Bigint Bigint::operator*(const Bigint &v) const
			{
			}



		};
	};
};
