#include <io.hh>
#include <parser.hh>
#include <iostream>
#include <exception>

using namespace Flaner::Compiler;


int main()
{
	//using namespace Flaner::Global;
	
	//IO::File file();	

	std::cout << "Tanpero Flaner Compiler 1.0.0" << std::endl;

	try
	{

		std::shared_ptr<Lex::Token> t1 = std::make_shared<Lex::Token>(Lex::TOKEN_CONST, "const");
		std::shared_ptr<Lex::Token> t2 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "a");
		std::shared_ptr<Lex::Token> t3 = std::make_shared<Lex::Token>(Lex::TOKEN_ASSIGN, "=");
		std::shared_ptr<Lex::Token> t4 = std::make_shared<Lex::Token>(Lex::TOKEN_NUMBER, "0");


		Lex::TokenList list;
		list.push(t1);
		list.push(t2);
		list.push(t3);
		list.push(t4);

		std::cout << list.first()->value << std::endl;


		std::shared_ptr<AST::Declaration> declaration = Parser::parseConstantDeclaration(list);
		std::cout << "1234" << std::endl;
		declaration->identifier.name.data();
		//std::cout << declaration->identifier.name << std::endl;
		std::cout << "5678" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return 0;
}