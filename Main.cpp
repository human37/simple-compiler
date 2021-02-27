#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Node.h"

void testToken()
{
    TokenType tt = VOID_TOKEN;
    std::string lexeme = "void";
    Token tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
}

void testScanner()
{
    ScannerClass scanner("input.c"); 
    while(scanner.getNextToken().GetTokenType() != ENDFILE_TOKEN)
    {
        std::cout << " - - - - - - start - - - - - - " << std::endl;
        std::cout << scanner.getNextToken() << " line: " << scanner.getLineNumber() << std::endl;
        std::cout << " - - - - - -  end  - - - - - - " << std::endl << std::endl;
    }
}

void testNodes()
{
    StartNode * variable = new StartNode(new ProgramNode(new BlockNode(new StatementGroupNode())));
    delete variable;

    PlusNode * plusvariable = new PlusNode(new IntegerNode(5), new IntegerNode(4));
    std::cout << "5 + 4 = " << plusvariable->Evaluate() << std::endl;
    delete plusvariable;

    MinusNode * minusvariable = new MinusNode(new IntegerNode(5), new IntegerNode(4));
    std::cout << "5 - 4 = " << minusvariable->Evaluate() << std::endl;
    delete minusvariable;
}

int main()
{
    testNodes();
}
