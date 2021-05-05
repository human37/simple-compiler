#if !defined(PARSER_H)
#define PARSER_H

#include "Scanner.h"
#include "Symbol.h"
#include "Token.h"
#include "Node.h"

class Parser
{
private:
    ScannerClass *scanner;
    SymbolTableClass *table;
    Token Match(TokenType expected);
    ProgramNode *Program();
    BlockNode *Block();
    StatementGroupNode *StatementGroup();
    StatementNode *Statement();
    DeclarationStatementNode *DeclarationStatement();
    DeclarationAssignmentStatementNode *DeclarationAssignmentStatement();
    AssignmentStatementNode *AssignmentStatement();
    IfStatementNode *IfStatement();
    WhileStatementNode *WhileStatement();
    DoStatementNode *DoStatement();
    ForStatementNode *ForStatement();
    CoutStatementNode *CoutStatement();
    ExpressionNode *Expression();
    ExpressionNode *Relational();
    ExpressionNode *PlusMinus();
    ExpressionNode *TimesDivide();
    ExpressionNode *Factor();
    IdentifierNode *Identifier();
    IntegerNode *Integer();
    ExpressionNode *And();
    ExpressionNode *Or();
    ExpressionNode *BitwiseAnd();

public:
    Parser(ScannerClass *scanner, SymbolTableClass *table);
    ~Parser();
    StartNode *Start();
};

#endif // PARSER_H