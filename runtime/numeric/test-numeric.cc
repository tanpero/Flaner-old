#include <bigint.hh>
#include <rational.hh>
#include <iostream>

int main(int argc, char* argv[])
{
	using Flaner::Runtime::numeric::Bigint;
	using Flaner::Runtime::numeric::Rational;

	std::cout << "Hello flaner.numeric!" << std::endl;
	std::cout << "---------------------\n" << std::endl;
	Rational rational1(18, 29);
	Rational rational2(-6, 31);
	std::cout << "rational1 " << (rational1 > rational2 ? ">" : "<") << " rational2" << std::endl;
	std::cout << "rational1 + rational2\n = " << rational1 << " + " << rational2 <<
		"\n = " << rational1 + rational2 << std::endl;
	std::cout << "\n\n\n";
	
	std::cout << "------ test cases of numeric::Bigint ------\n";

	Bigint one = std::string("10000000");
	
	std::cout << "the number is " << one << std::endl;
	std::cout << "its size is " << one.digits() << std::endl;
	std::cout << "convert it to 20-base string is " << one.toString(20) << std::endl;
	std::cout << "it division by zero is " << one / 0 << std::endl;
	return 0;
}
