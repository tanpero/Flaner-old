#include <io.hh>
#include <parser.hh>
#include <iostream>
#include <exception>

int main()
{
	using namespace Flaner::Global;
	using namespace Flaner::Compiler;
	IO::File file();	

	try
	{
		std::shared_ptr<Lex::TokenList> tokenList;
		std::shared_ptr<Lex::Token> t1 = std::make_shared<Lex::Token>(Lex::TOKEN_CONST, "const");
		std::shared_ptr<Lex::Token> t2 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "a");
		std::shared_ptr<Lex::Token> t3 = std::make_shared<Lex::Token>(Lex::TOKEN_ASSIGN, "=");
		std::shared_ptr<Lex::Token> t4 = std::make_shared<Lex::Token>(Lex::TOKEN_NUMBER, "0"); tokenList->push(t1);
		//tokenList->push(t2);
		//tokenList->push(t3);
		//tokenList->push(t4);

		//std::shared_ptr<AST::Declaration> declaration = Parser::parseConstantDeclaration(tokenList);
		//std::cout << declaration->identifier->name << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return 0;
}