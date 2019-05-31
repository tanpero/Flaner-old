#ifndef _FLANER_RUNTIME_NUMERIC_BIGINT_HH_
#define _FLANER_RUNTIME_NUMERIC_BIGINT_HH_

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace Flaner
{
	namespace Runtime
	{
		namespace numeric
		{

			const int base = 1000000000;
			const int base_digits = 9;

			class Bigint
			{
				std::vector<int> a;
				int sign;

			public:
				Bigint();
				Bigint(long long v);
				Bigint(std::string &s);
				void operator=(const Bigint &v);
				void operator=(long long v);
				Bigint operator+(const Bigint &v) const;
				Bigint operator-(const Bigint &v) const;
				void operator*=(int v);
				Bigint operator*(int v) const;
				void operator*=(long long v);
				Bigint operator*(long long v) const;

			public:
				int size();
				Bigint operator ^ (const Bigint &v);
				std::string toString();
				int sumOf();

			public:
				friend std::pair<Bigint, Bigint> divmod(const Bigint &a1, const Bigint &b1);

				Bigint operator/(const Bigint &v) const;
				Bigint operator%(const Bigint &v) const;
				void operator/=(int v);
				Bigint operator/(int v) const;
				int operator%(int v) const;

				void operator+=(const Bigint &v);
				void operator-=(const Bigint &v);
				void operator*=(const Bigint &v);
				void operator/=(const Bigint &v);

				bool operator<(const Bigint &v) const;
				bool operator>(const Bigint &v) const;
				bool operator<=(const Bigint &v) const;
				bool operator>=(const Bigint &v) const;
				bool operator==(const Bigint &v) const;
				bool operator!=(const Bigint &v) const;

				void trim();
				bool isZero() const;
				Bigint operator-() const;
				Bigint abs() const;

				long long longValue() const;
				friend Bigint gcd(const Bigint &a, const Bigint &b);
				friend Bigint lcm(const Bigint &a, const Bigint &b);

				void read(const std::string &s);

				friend std::istream& operator>>(std::istream &stream, Bigint &v);
				friend std::ostream& operator<<(std::ostream &stream, const Bigint &v);

				static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits);
				typedef std::vector<long long> vll;

				static vll karatsubaMultiply(const vll &a, const vll &b);
				Bigint operator*(const Bigint &v) const

			
		};
	};
};

#endif // !_FLANER_RUNTIME_NUMERIC_BIGINT_HH_
