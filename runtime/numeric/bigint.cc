#include <bigint.hh>

namespace Flaner
{
	namespace Runtime
	{
		namespace numeric
		{

			Bigint::Bigint() noexcept
			{
				sign = 1;
			}


			Bigint::Bigint(long long v)
			{
				sign = 1;
				*this = v;
			}


			Bigint::Bigint(std::string & s)
			{
				sign = 1;
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

			void Bigint::operator=(std::string s)
			{
				read(s);
			}


			Bigint Bigint::operator+(const Bigint &v) const
			{
				if (sign == v.sign) {
					Bigint res = v;

					for (int i = 0, carry = 0; i < static_cast<int>(std::max(a.size(), v.a.size()) || carry); ++i) {
						if (i == static_cast<int>(res.a.size()))
							res.a.push_back(0);
						res.a[i] += carry + (i < static_cast<int>(a.size() ? a[i] : 0));
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
						for (int i = 0, carry = 0; i < static_cast<int>(v.a.size() || carry); ++i) {
							res.a[i] -= carry + (i < static_cast<int>(v.a.size() ? v.a[i] : 0));
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
				for (int i = 0, carry = 0; i < static_cast<int>(a.size() || carry); ++i) {
					if (i == static_cast<int>(a.size()))
						a.push_back(0);
					long long cur = a[i] * (long long)v + carry;
					carry = static_cast<int>((cur / base));
					a[i] = static_cast<int>((cur % base));

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
				for (int i = 0, carry = 0; i < static_cast<int>(a.size() || carry); ++i) {
					if (i == static_cast<int>(a.size()))
						a.push_back(0);
					long long cur = a[i] * (long long)v + carry;
					carry = static_cast<int>((cur / base));
					a[i] = static_cast<int>((cur % base));

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

			std::string Bigint::toString(int base)
			{
				if (base < 2 || base > 36)
					return "0";

				bool isNegative = (*this < 0);
				if (isNegative)
					*this *= -1;

				// NOTE: it's probably possible to reserve string based on value
				std::string output;

				do
				{
					char digit = *this % base;

					// Convert to appropriate base character
					// 0-9
					if (digit < 10)
						digit += '0';
					// A-Z
					else
						digit = digit + 'A' - 10;

					// Append digit to string (in reverse order)
					output += digit;

					*this /= base;

				} while (*this > 0);

				if (isNegative)
					output += '-';

				// Reverse the string - NOTE: could be done with std::reverse
				int len = output.size() - 1;
				for (int i = 0; i < len; ++i)
				{
					// Swap characters - NOTE: Could be done with std::swap
					char temp = output[i];
					output[i] = output[len - i];
					output[len - i] = temp;
				}

				return output;
			
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
				int rem = 0;
				if (v < 0)
					sign = -sign, v = -v;
				for (int i = static_cast<int>(a.size() - 1); i >= 0; --i) {
					long long cur = a[i] + rem * (long long)base;
					a[i] = static_cast<int>((cur / v));
					rem = static_cast<int>((cur % v));
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
				sign = 1;
				a.clear();
				int pos = 0;
				while (pos < static_cast<int>(s.size() && (s[pos] == '-' || s[pos] == '+'))) {
					if (s[pos] == '-')
						sign = -sign;
					++pos;
				}
				for (int i = s.size() - 1; i >= pos; i -= base_digits) {
					int x = 0;
					for (int j = std::max(pos, i - base_digits + 1); j <= i; j++)
						x = x * 10 + s[j] - '0';
					a.push_back(x);
				}
				trim();
			}

			void Bigint::read(const std::string & s, int base)
			{
				if (base < 2 || base > 36)
				{
					*this = 0;
					return;
				}
				
				Bigint value = 0;
				
				bool isNegative = (s[0] == '-');

				int startIndex = s.length() - 1;
				int endIndex = isNegative ? 1 : 0;

				long value = 0;
				int digitValue = 1;

				for (int i = startIndex; i >= endIndex; --i)
				{
					char c = s[i];

					// Uppercase it - NOTE: could be done with std::toupper
					if (c >= 'a' && c <= 'z')
						c -= ('a' - 'A');

					// Convert char to int value - NOTE: could be done with std::atoi
					// 0-9
					if (c >= '0' && c <= '9')
						c -= '0';
					// A-Z
					else
						c = c - 'A' + 10;

					if (c >= base)
						*this = 0;

					// Get the base 10 value of this digit    
					value += c * digitValue;

					// Each digit has value base^digit position - NOTE: this avoids pow
					digitValue *= base;
				}

				if (isNegative)
					value *= -1;

				*this = value;
			}


			std::istream& operator>>(std::istream &stream, Bigint &v)
			{
				std::string s;
				stream >> s;
				v.read(s);
				return stream;
			}


			std::ostream& operator<<(std::ostream &stream, const Bigint &v)
			{
				if (v.sign == -1)
					stream << '-';
				stream << (v.a.empty() ? 0 : v.a.back());
				for (int i = static_cast<int>(v.a.size() - 2); i >= 0; --i)
					stream << std::setw(base_digits) << std::setfill('0') << v.a[i];
				return stream;
			}


			static std::vector<long long> karatsubaMultiply(const std::vector<long long> &a, const std::vector<long long> &b)
			{
				int n = a.size();
				std::vector<long long> res(n + n);
				if (n <= 32) {
					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++)
							res[i + j] += a[i] * b[j];
					return res;
				}

				int k = n >> 1;
				std::vector<long long> a1(a.begin(), a.begin() + k);
				std::vector<long long> a2(a.begin() + k, a.end());
				std::vector<long long> b1(b.begin(), b.begin() + k);
				std::vector<long long> b2(b.begin() + k, b.end());

				std::vector<long long> a1b1 = karatsubaMultiply(a1, b1);
				std::vector<long long> a2b2 = karatsubaMultiply(a2, b2);

				for (int i = 0; i < k; i++)
					a2[i] += a1[i];
				for (int i = 0; i < k; i++)
					b2[i] += b1[i];

				std::vector<long long> r = karatsubaMultiply(a2, b2);
				for (int i = 0; i < static_cast<int>(a1b1.size()); i++)
					r[i] -= a1b1[i];
				for (int i = 0; i < static_cast<int>(a2b2.size()); i++)
					r[i] -= a2b2[i];

				for (int i = 0; i < static_cast<int>(r.size()); i++)
					res[i + k] += r[i];
				for (int i = 0; i < static_cast<int>(a1b1.size()); i++)
					res[i] += a1b1[i];
				for (int i = 0; i < static_cast<int>(a2b2.size()); i++)
					res[i + n] += a2b2[i];
				return res;
			}


			std::vector<int> Bigint::convert_base(const std::vector<int>& a, int old_digits, int new_digits)
			{

				std::vector<long long> p(std::max(old_digits, new_digits) + 1);
				p[0] = 1;
				for (int i = 1; i < static_cast<int>(p.size()); i++)
					p[i] = p[i - 1] * 10;
				std::vector<int> res;
				long long cur = 0;
				int cur_digits = 0;
				for (int i = 0; i < static_cast<int>(a.size()); i++) {
					cur += a[i] * p[cur_digits];
					cur_digits += old_digits;
					while (cur_digits >= new_digits) {
						res.push_back(int(cur % p[new_digits]));
						cur /= p[new_digits];
						cur_digits -= new_digits;
					}
				}
				res.push_back(static_cast<int>(cur));
				while (!res.empty() && !res.back())
					res.pop_back();
				return res;
			}


			Bigint Bigint::operator*(const Bigint &v) const
			{
				std::vector<int> a6 = convert_base(this->a, base_digits, 6);
				std::vector<int> b6 = convert_base(v.a, base_digits, 6);
				std::vector<long long> a(a6.begin(), a6.end());
				std::vector<long long> b(b6.begin(), b6.end());
				while (a.size() < b.size())
					a.push_back(0);
				while (b.size() < a.size())
					b.push_back(0);
				while (a.size() & (a.size() - 1))
					a.push_back(0), b.push_back(0);
				std::vector<long long> c = karatsubaMultiply(a, b);
				Bigint res;
				res.sign = sign * v.sign;
				for (int i = 0, carry = 0; i < static_cast<int>(c.size()); i++) {
					long long cur = c[i] + carry;
					res.a.push_back(static_cast<int>((cur % 1000000)));
					carry = static_cast<int>((cur / 1000000));
				}
				res.a = convert_base(res.a, 6, base_digits);
				res.trim();
				return res;
			}

			Bigint Bigint::pow(Bigint n) const
			{
				if (n < 0)
				{
					// 应当抛出异常
					return 0;
				}
				else if (n == 0)
				{
					return 1;
				}
				else if (n == 1)
				{
					return *this;
				}
				else
				{
					Bigint value = *this;
					for (Bigint i = 1; i <= n; i += 1)
					{
						value *= i;
					}
					return value;
				}
			}

		};
	};
};
