#include <bigint.hh>
#include <rational.hh>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello flaner.numeric!" << std::endl;
	std::cout << "---------------------\n" << std::endl;
	Rational rational1(18, 29);
	Rational rational2(-6, 31);
	std::cout << "rational1 " << (rational1 > rational2 ? ">" : "<") << " rational2" << std::endl;
	std::cout << "rational1 + rational2\n = " << rational1 << " + " << rational2 <<
		"\n = " << rational1 + rational2 << std::endl;

	return 0;
}
