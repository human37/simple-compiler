#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"

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

int main()
{
   testScanner(); 
}
