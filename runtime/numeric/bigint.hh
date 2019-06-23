#ifndef _FLANER_RUNTIME_NUMERIC_BIGINT_HH_
#define _FLANER_RUNTIME_NUMERIC_BIGINT_HH_

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iostream>
#include <iomanip>
#include <rational.hh>

namespace Flaner
{
    namespace Runtime
    {
        namespace numeric
        {

            const int base = 10e9;
            const int base_digits = 9;

            class Bigint
            {
                std::vector<int> a;
                int sign;

            public:            
                Bigint() noexcept;
                Bigint(long long v);
                Bigint(std::string &s);
                Bigint(std::string &s, int base);
                void operator=(const Bigint &v);
                void operator=(long long v);
                void operator=(std::string s);

                Bigint operator+(const Bigint &v) const;
                Bigint operator-(const Bigint &v) const;
                void operator*=(int v);
                Bigint operator*(int v) const;
                void operator*=(long long v);
                Bigint operator*(long long v) const;

            public:
                size_t digits();
                Bigint operator ^ (const Bigint &v);
                std::string toString();
                std::string toString(int base);
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

                void fromString(const std::string &s);
                void fromString(const std::string &s, int base);

                friend std::istream& operator>>(std::istream &stream, Bigint &v);
                friend std::ostream& operator<<(std::ostream &stream, const Bigint &v);

                static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits);
                Bigint operator*(const Bigint &v) const;

                Bigint pow(Bigint& n) const;
                Bigint pow(int n) const;

                Bigint operator&(Bigint n) const;
                Bigint operator|(Bigint n) const;
                Bigint operator<<(Bigint n) const;
                Bigint operator>>(Bigint n) const;

                Bigint operator++();
                Bigint operator++(int);
                Bigint operator--();
                Bigint operator--(int);

            public:
                Bigint maxValue();
                Bigint MinValue();
            };
        };
    };
};

#endif // !_FLANER_RUNTIME_NUMERIC_BIGINT_HH_
