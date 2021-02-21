#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"

int main()
{
    // TokenType tt = VOID_TOKEN;
    // std::string lexeme = "void";
    // Token tok1(tt, lexeme);
    // std::cout << tok1 << std::endl;
    ScannerClass scanner("input.c"); 
    while(scanner.getNextToken().GetTokenType() != ENDFILE_TOKEN)
    {
        std::cout << " - - - - - - start - - - - - - " << std::endl;
        std::cout << scanner.getNextToken() << std::endl;
        std::cout << " - - - - - -  end  - - - - - - " << std::endl << std::endl;
    }
}