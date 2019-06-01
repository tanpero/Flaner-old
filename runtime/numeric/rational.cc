#include <rational.hh>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>

namespace Flaner
{
	namespace Runtime
	{
		namespace numeric
		{

			int absInt(int x) {
				if (x >= 0) {
					return x;
				}
				else {
					return -x;
				}
			}

			void getFactors(int num, std::vector<int>& factorSet) {
				if (num != 1) {
					factorSet.push_back(num);
				}
				for (int i = 2; i <= sqrt(static_cast<double>(num)); i++) {
					if (num  %  i == 0) {
						factorSet.push_back(i);
						factorSet.push_back(num / i);
					}
				}
			}

			void simplifyFun(int& a, int& b) {
				int tempN = a;
				int tempD = b;
				int small, temp;
				std::vector<int> factorSet;
				if (tempN == tempD) {
					a = 1;
					b = 1;
					return;
				}
				else if (tempN == -tempD) {
					a = -1;
					b = 1;
					return;
				}
				else if (tempN == 0) {
					b = 1;
					return;
				}


				if (absInt(tempN) < absInt(tempD)) {
					small = absInt(tempN);
				}
				else {
					small = absInt(tempD);
				}

				getFactors(small, factorSet);
				for (unsigned int i = 0; i < factorSet.size(); i++) {
					temp = factorSet[i];
					while (tempN % temp == 0 && tempD % temp == 0) {
						tempN /= temp;
						tempD /= temp;
					}
				}
				a = tempN;
				b = tempD;
			}


			// friend functions definitions
			Rational operator+(const Rational& left, const Rational& right) {
				Rational temp;
				int tempLD = left.getDenominator();
				int tempRD = right.getDenominator();
				simplifyFun(tempLD, tempRD);
				temp.setDenominator(left.getDenominator() * tempRD);
				temp.setNumerator(left.getNumerator() * tempRD + right.getNumerator() * tempLD);
				temp.simplify();
				return temp;
			}

			Rational operator-(const Rational& left, const Rational& right) {
				return left + (-right);
			}

			Rational operator * (const Rational& left, const Rational& right) {
				Rational temp;
				Rational temp_2(right.getNumerator(), left.getDenominator());
				Rational temp_3(left.getNumerator(), right.getDenominator());
				int a = temp_2.getDenominator();
				int b = temp_2.getNumerator();
				int c = temp_3.getDenominator();
				int d = temp_3.getNumerator();
				temp.setNumerator(b * d);
				temp.setDenominator(a * c);
				return temp;
			}

			Rational operator/(const Rational& left, const Rational& right) {
				Rational temp_1(left.getNumerator(), left.getDenominator());
				Rational temp_2(right.getDenominator(), right.getNumerator());
				return temp_1 * temp_2;
			}

			bool operator==(const Rational& left, const Rational& right) {
				return (left.numerator == right.numerator && left.denominator == right.denominator);
			}

			bool operator!=(const Rational& left, const Rational& right) {
				return !(left == right);
			}

			bool operator<(const Rational& left, const Rational& right) {
				int lside = left.getNumerator() * right.getDenominator();
				int rside = left.getDenominator() * right.getNumerator();
				return (lside < rside);
			}

			bool operator>(const Rational& left, const Rational& right) {
				int lside = left.getNumerator() * right.getDenominator();
				int rside = left.getDenominator() * right.getNumerator();
				return (lside > rside);
			}

			bool operator<=(const Rational& left, const Rational& right) {
				return ((left < right) || (left == right));
			}

			bool operator>=(const Rational& left, const Rational& right) {
				return ((left > right) || (left == right));
			}

			std::ostream& operator<<(std::ostream& out, const Rational& obj) {
				out << obj.getNumerator();
				if (obj.getNumerator() != 0 && obj.getDenominator() != 1) {
					out << "/" << obj.getDenominator();
				}
				return out;
			}

			std::istream& operator>>(std::istream& in, Rational& obj) {
				std::string inputstr;
				int num = 0;
				int sign = 1;
				bool slashExist = false;
				bool dotExist = false;
				bool validInput = true;
				int virtualDenominator = 1;
				std::cin >> inputstr;
				for (unsigned int i = 0; i < inputstr.size(); i++) {
					char temp = inputstr[i];
					if (temp == '.') {
						if (dotExist == false && slashExist == false && i != 0) {
							dotExist = true;
						}
						else {
							validInput = false;
							break;
						}
					}
					else if (temp == '/') {
						if (dotExist == false && slashExist == false && i != 0) {
							slashExist = true;
							obj.setNumerator(sign * num);
							num = 0;
							sign = 1;
						}
						else {
							validInput = false;
							break;
						}
					}
					else if (temp == '-') {
						if (i == 0) {
							sign = -sign;
						}
						else if (inputstr[i - 1] == '/') {
							sign = -sign;
						}
						else {
							validInput = false;
							break;
						}
					}
					else if (temp <= '9' && temp >= '0') {
						if (dotExist) {
							if (virtualDenominator > INT_MAX / 10) {
								std::cout << "this frational is too long to handle.";
								validInput = false;
								break;
							}
							else {
								virtualDenominator *= 10;
							}
						}
						if (num > INT_MAX / 10) {
							std::cout << "this number is too long to handle.";
							validInput = false;
							break;
						}
						num *= 10;
						num += inputstr[i] - '0';
					}
					else {
						validInput = false;
						break;
					}
				}

				if (validInput == false) {
					obj.setNumerator(0);
					obj.setDenominator(1);
					std::cout << "Input is not valid! The whole set to 0" << std::endl;
				}
				else {
					if (slashExist == true) {
						obj.setDenominator(sign * num);
					}
					else if (dotExist) {
						obj.setNumerator(sign * num);
						obj.setDenominator(virtualDenominator);
					}
					else {
						obj.setNumerator(sign * num);
						obj.setDenominator(1);
					}
				}
				obj.simplify();
				return in;
			}




			// member function definition
			Rational::Rational() noexcept
			{
				setNumerator(0);
				setDenominator(1);
			}

			Rational::Rational(double x) {
				int i = 1;
				while (x * i - static_cast<int>(x * i) != 0) {
					if (i > INT_MAX / 10) {
						std::cout << "this frational number : " << x << " can not be transfer to rational number, it's too long, now set it 0." << std::endl;
						setNumerator(0);
						setDenominator(1);
						return;
					}
					else {
						i *= 10;
					}
				}
				setNumerator(x * i);
				setDenominator(i);
				simplify();
			}

			Rational::Rational(int numerator_, int denominator_) {
				int n = numerator_;
				int d = denominator_;
				if (d == 0) {
					setNumerator(0);
					setDenominator(1);
				}
				else {
					if (d < 0) { // right, we don't want this negative, so
						n = -n;
						d = -d;	// if they were both negative, we want them both positive
								// otherwise, n is now negative
					}
				}
				setNumerator(n);
				setDenominator(d);
				simplify();
			}

			Rational& Rational::operator=(const Rational& obj) {
				setNumerator(obj.getNumerator());
				setDenominator(obj.getDenominator());
				return  *this;
			}

			Rational& Rational::operator+=(const Rational& obj) {
				*this = *this + obj;
				return  *this;
			}

			Rational& Rational::operator-=(const Rational& obj) {
				*this = *this - obj;
				return  *this;
			}

			Rational& Rational::operator *=(const Rational& obj) {
				*this = *this * obj;
				return  *this;
			}

			Rational& Rational::operator/=(const Rational& obj) {
				*this = *this / obj;
				return  *this;
			}
			Rational& Rational::operator++() {
				*this = *this + 1;
				return  *this;
			}

			Rational Rational::operator++(int) {
				Rational before = *this;
				*this = *this + 1;
				return before;
			}

			Rational& Rational::operator--() {
				*this = *this - 1;
				return  *this;
			}

			Rational Rational::operator--(int) {
				Rational before = *this;
				*this = *this - 1;
				return before;
			}

			Rational Rational::operator+() const {
				return  *this;
			}

			Rational Rational::operator-() const {
				Rational temp;
				temp.setNumerator(-getNumerator());
				temp.setDenominator(getDenominator());
				return temp;
			}

			void Rational::setNumerator(int numerator_) {
				numerator = numerator_;
			}

			int Rational::getNumerator() const {
				return numerator;
			}

			void Rational::setDenominator(int denominator_) {
				if (denominator_ == 0) {
					denominator = 1;
					numerator = 0;
					std::cout << "Denominator is 0! Not good! THe whole is set to 0." << std::endl;
				}
				else {
					denominator = denominator_;
				}
			}

			int Rational::getDenominator() const {
				return denominator;
			}


			void Rational::simplify() {
				int tempN = numerator;
				int tempD = denominator;
				simplifyFun(tempN, tempD);
				setNumerator(tempN);
				setDenominator(tempD);
			}

		};
	};
};
