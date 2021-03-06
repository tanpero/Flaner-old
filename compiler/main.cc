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

        std::shared_ptr<Lex::Token> t5 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "m");
        std::shared_ptr<Lex::Token> t6 = std::make_shared<Lex::Token>(Lex::TOKEN_COMMA, ",");
        std::shared_ptr<Lex::Token> t7 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "n");
        std::shared_ptr<Lex::Token> t8 = std::make_shared<Lex::Token>(Lex::TOKEN_COMMA, ",");
        std::shared_ptr<Lex::Token> t9 = std::make_shared<Lex::Token>(Lex::TOKEN_DOT_DOT_DOT, "...");
        std::shared_ptr<Lex::Token> t10 = std::make_shared<Lex::Token>(Lex::TOKEN_ID, "args");


        std::shared_ptr<Lex::TokenList> list = std::make_shared<Lex::TokenList>();
        list->push(t1);
        list->push(t2);
        list->push(t3);
        list->push(t4);
        
        std::shared_ptr<AST::Declaration> declaration = Parser::parseConstantDeclaration(list);
        std::cout << "kind is " << list->first()->value << std::endl;
        std::cout << "identifier is " << declaration->identifier->name << std::endl;
        std::cout << "------------------\n" << std::endl;

        std::shared_ptr<Lex::TokenList> list2 = std::make_shared<Lex::TokenList>();
        list2->push(t5);
        list2->push(t6);
        list2->push(t7);
        list2->push(t8);
        list2->push(t9);
        list2->push(t10);

        std::shared_ptr<AST::ParamsList> paramsList = Parser::parseParameterList(list2);
        int count = 1;
        for (std::vector<std::shared_ptr<AST::Param>>::iterator i = paramsList->begin();
            i != paramsList->end(); ++i, ++count)
        {
            std::cout << "parameter " << count << ": " << (*i)->id->name << std::endl;
        }

        std::cout << "------------" << std::endl;
        std::cout << paramsList->getLength() << std::endl;


    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    

    return 0;
}