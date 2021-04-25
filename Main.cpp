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
    StartNode *variable = new StartNode(new ProgramNode(new BlockNode(new StatementGroupNode())));
    delete variable;

    PlusNode *plusvariable = new PlusNode(new IntegerNode(5), new IntegerNode(4));
    std::cout << "5 + 4 = " << plusvariable->Evaluate() << std::endl;
    delete plusvariable;

    MinusNode *minusvariable = new MinusNode(new IntegerNode(5), new IntegerNode(4));
    std::cout << "5 - 4 = " << minusvariable->Evaluate() << std::endl;
    delete minusvariable;
}

void interpretCode(std::string inputFilename)
{
    ScannerClass *scanner = new ScannerClass(inputFilename);
    SymbolTableClass *symbols = new SymbolTableClass();
    Parser parser(scanner, symbols);
    parser.Start()->Interpret();
}

void machineCode(std::string inputFilename)
{
    ScannerClass scanner(inputFilename);
    SymbolTableClass symbolTable;
    Parser parser(&scanner, &symbolTable);
    StartNode *root = parser.Start();
    InstructionsClass machineCode;
    root->Code(machineCode);
    machineCode.Finish();
    machineCode.PrintAllMachineCodes();
    machineCode.Execute();
    delete root;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "not enough parameters provided!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string mode = argv[1];
    std::string fileName = argv[2];
    if (mode == "-i")
    {
        std::cout << "interpreting into c++..." << std::endl;
        interpretCode(fileName);
    }
    else if (mode == "-c")
    {
        std::cout << "compiling to machine code..." << std::endl;
        machineCode(fileName);
    }
    else
    {
        std::cerr << "unknown parameters were provided.";
    }
    return 0;
}
