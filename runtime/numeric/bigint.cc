#include <bigint.hh>

namespace Flaner
{
	namespace Runtime
	{
		namespace numeric
		{

			Bigint::Bigint()
			{
				sign = 1;
			}


			Bigint::Bigint(long long v)
			{
				*this = v;
			}


			Bigint::Bigint(std::string & s)
			{
				read(s);
			}


			void Bigint::operator=(const Bigint &v)
			{
				sign = v.sign;
				a = v.a;
			}


			void Bigint::operator=(long long v)
			{
				sign = 1;
				a.clear();
				if (v < 0)
					sign = -1, v = -v;
				for (; v > 0; v = v / base)
					a.push_back(v % base);
			}


			Bigint Bigint::operator+(const Bigint &v) const
			{
				if (sign == v.sign) {
					Bigint res = v;

					for (int i = 0, carry = 0; i < (int)std::max(a.size(), v.a.size()) || carry; ++i) {
						if (i == (int)res.a.size())
							res.a.push_back(0);
						res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
						carry = res.a[i] >= base;
						if (carry)
							res.a[i] -= base;
					}
					return res;
				}
				return *this - (-v);
			}


			Bigint Bigint::operator-(const Bigint &v) const
			{
				if (sign == v.sign) {
					if (abs() >= v.abs()) {
						Bigint res = *this;
						for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
							res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
							carry = res.a[i] < 0;
							if (carry)
								res.a[i] += base;
						}
						res.trim();
						return res;
					}
					return -(v - *this);
				}
				return *this + (-v);
			}


			void Bigint::operator*=(int v)
			{
				if (v < 0)
					sign = -sign, v = -v;
				for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i) {
					if (i == (int)a.size())
						a.push_back(0);
					long long cur = a[i] * (long long)v + carry;
					carry = (int)(cur / base);
					a[i] = (int)(cur % base);

				}
				trim();
			}


			Bigint Bigint::operator*(int v) const
			{
				Bigint res = *this;
				res *= v;
				return res;
			}


			void Bigint::operator*=(long long v)
			{
				if (v < 0)
					sign = -sign, v = -v;
				for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i) {
					if (i == (int)a.size())
						a.push_back(0);
					long long cur = a[i] * (long long)v + carry;
					carry = (int)(cur / base);
					a[i] = (int)(cur % base);

				}
				trim();
			}


			Bigint Bigint::operator*(long long v) const
			{
				Bigint res = *this;
				res *= v;
				return res;
			}


			int Bigint::size()
			{
				if (a.empty())return 0;
				int ans = (a.size() - 1)*base_digits;
				int ca = a.back();
				while (ca)
					ans++, ca /= 10;
				return ans;
			}


			Bigint Bigint::operator ^ (const Bigint &v)
			{
				Bigint ans = 1, a = *this, b = v;
				while (!b.isZero()) {
					if (b % 2)
						ans *= a;
					a *= a, b /= 2;
				}
				return ans;
			}


			std::string Bigint::toString()
			{
				std::stringstream ss;
				ss << *this;
				std::string s;
				ss >> s;
				return s;
			}


			int Bigint::sumOf()
			{
				std::string s = toString();
				int ans = 0;
				for (auto c : s)  ans += c - '0';
				return ans;
			}


			std::pair<Bigint, Bigint> divmod(const Bigint & a1, const Bigint & b1)
			{

				int norm = base / (b1.a.back() + 1);
				Bigint a = a1.abs() * norm;
				Bigint b = b1.abs() * norm;
				Bigint q, r;
				q.a.resize(a.a.size());

				for (int i = a.a.size() - 1; i >= 0; i--) {
					r *= base;
					r += a.a[i];
					int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
					int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
					int d = ((long long)base * s1 + s2) / b.a.back();
					r -= b * d;
					while (r < 0)
						r += b, --d;
					q.a[i] = d;
				}

				q.sign = a1.sign * b1.sign;
				r.sign = a1.sign;
				q.trim();
				r.trim();
				return std::make_pair(q, r / norm);
			}


			Bigint Bigint::operator/(const Bigint &v) const
			{
				return divmod(*this, v).first;
			}


			Bigint Bigint::operator%(const Bigint &v) const
			{
				return divmod(*this, v).second;
			}


			void Bigint::operator/=(int v)
			{
				if (v < 0)
					sign = -sign, v = -v;
				for (int i = (int)a.size() - 1, rem = 0; i >= 0; --i) {
					long long cur = a[i] + rem * (long long)base;
					a[i] = (int)(cur / v);
					rem = (int)(cur % v);
				}
				trim();
			}


			Bigint Bigint::operator/(int v) const
			{
				Bigint res = *this;
				res /= v;
				return res;
			}


			int Bigint::operator%(int v) const
			{
				if (v < 0)
					v = -v;
				int m = 0;
				for (int i = a.size() - 1; i >= 0; --i)
					m = (a[i] + m * (long long)base) % v;
				return m * sign;
			}



			void Bigint::operator+=(const Bigint &v)
			{
				*this = *this + v;
			}


			void Bigint::operator-=(const Bigint &v)
			{
				*this = *this - v;
			}


			void Bigint::operator*=(const Bigint &v)
			{
				*this = *this * v;
			}


			void Bigint::operator/=(const Bigint &v)
			{
				*this = *this / v;
			}



			bool Bigint::operator<(const Bigint &v) const
			{
				if (sign != v.sign)
					return sign < v.sign;
				if (a.size() != v.a.size())
					return a.size() * sign < v.a.size() * v.sign;
				for (int i = a.size() - 1; i >= 0; i--)
					if (a[i] != v.a[i])
						return a[i] * sign < v.a[i] * sign;
				return false;
			}


			bool Bigint::operator>(const Bigint &v) const
			{
				return v < *this;
			}


			bool Bigint::operator<=(const Bigint &v) const
			{
				return !(v < *this);
			}


			bool Bigint::operator>=(const Bigint &v) const
			{
				return !(*this < v);
			}


			bool Bigint::operator==(const Bigint &v) const
			{
				return !(*this < v) && !(v < *this);
			}


			bool Bigint::operator!=(const Bigint &v) const
			{
				return *this < v || v < *this;
			}


			void Bigint::trim()
			{
				while (!a.empty() && !a.back())
					a.pop_back();
				if (a.empty())
					sign = 1;
			}


			bool Bigint::isZero() const
			{
				return a.empty() || (a.size() == 1 && !a[0]);
			}


			Bigint Bigint::operator-() const
			{
				Bigint res = *this;
				res.sign = -sign;
				return res;
			}


			Bigint Bigint::abs() const
			{
				Bigint res = *this;
				res.sign *= res.sign;
				return res;
			}



			long long Bigint::longValue() const
			{
				long long res = 0;
				for (int i = a.size() - 1; i >= 0; i--)
					res = res * base + a[i];
				return res * sign;
			}


			Bigint gcd(const Bigint &a, const Bigint &b)
			{
				return b.isZero() ? a : gcd(b, a % b);
			}


			Bigint lcm(const Bigint & a, const Bigint & b)
			{
				return a / gcd(a, b) * b;
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
