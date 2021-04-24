#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Node.h"
#include "Parser.h"
#include "Instructions.h"

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
    Token tc;
    do
    {
        tc = scanner.getNextToken();
        std::cout << tc << std::endl;
    } while (tc.GetTokenType() != ENDFILE_TOKEN);
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

void testInterpreter()
{
    ScannerClass *scanner = new ScannerClass("input.c");
    SymbolTableClass *symbols = new SymbolTableClass();
    Parser parser(scanner, symbols);

    parser.Start()->Interpret();
}

void CodeAndExecute()
{
    // Create scanner, symbol table, and parser objects.
    ScannerClass scanner("input.c");
    SymbolTableClass symbolTable;
    Parser parser(&scanner, &symbolTable);
    // Do the parsing, which results in a parse tree.
    StartNode * root = parser.Start();
    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    root->Code(machineCode);
    machineCode.Finish();
    machineCode.PrintAllMachineCodes();
    // Execute the machine code instructions previously created
    machineCode.Execute();
    // cleanup recursively
    delete root;
}

int main()
{
    // testInterpreter();
    CodeAndExecute();
}
