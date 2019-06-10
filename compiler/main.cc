#include <io.hh>
#include <parser.hh>
#include <iostream>
#include <exception>

using namespace Flaner::Compiler;


int main()
{
	std::cout << "\nTanpero Flaner Compiler 1.0.0" << 
		"\n------------\n\n" << std::endl;

	try
	{

		std::shared_ptr<Lex::Token> t1 = std::make_shared<Lex::Token>(Lex::TOKEN_CONST, "const");
		std::shared_ptr<Lex::Token> t2 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "a");
		std::shared_ptr<Lex::Token> t3 = std::make_shared<Lex::Token>(Lex::TOKEN_ASSIGN, "=");
		std::shared_ptr<Lex::Token> t4 = std::make_shared<Lex::Token>(Lex::TOKEN_NUMBER, "0");


		std::shared_ptr<Lex::TokenList> list;
		list->push(t1);
		list->push(t2);
		list->push(t3);
		list->push(t4);
		
		std::shared_ptr<AST::Declaration> declaration = Parser::parseConstantDeclaration(list);
		std::cout << "kind is " << list->first()->value << std::endl;
		std::cout << "identifier is " << declaration->identifier.name << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return 0;
}