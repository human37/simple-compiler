#include <iostream>
#include <iomanip>
#include "Parser.h"

Parser::Parser(ScannerClass *scanner, SymbolTableClass *table)
    : scanner(scanner), table(table) {}

Parser::~Parser()
{
    delete this->scanner;
    delete this->table;
}

Token Parser::Match(TokenType expected)
{
    Token t = this->scanner->getNextToken();
    if (t.GetTokenType() != expected)
    {
        std::cerr << "Error in parser match. " << std::endl;
        std::cerr << "Expected token type " << Token::GetTokenTypeName(expected) << ", but got type " << t.GetTokenTypeName() << ": " << t << std::endl;
        exit(1);
    }
    MSG(std::setw(5) << "lexeme: "
                     << "\e[34m" << std::setw(5) << t.GetLexeme() << "\e[0m" << std::setw(7)
                     << "   token: "
                     << "\e[32m" << t.GetTokenTypeName() << "\e[0m");
    return t;
}

StartNode *Parser::Start()
{
    ProgramNode *pn = this->Program();
    this->Match(ENDFILE_TOKEN);
    return new StartNode(pn);
}

ProgramNode *Parser::Program()
{
    this->Match(VOID_TOKEN);
    this->Match(MAIN_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode *bn = this->Block();
    return new ProgramNode(bn);
}

BlockNode *Parser::Block()
{
    this->Match(LEFT_BRACE_TOKEN);
    StatementGroupNode *sgn = this->StatementGroup();
    this->Match(RIGHT_BRACE_TOKEN);
    return new BlockNode(sgn);
}

StatementGroupNode *Parser::StatementGroup()
{
    StatementGroupNode *sgn = new StatementGroupNode();
    StatementNode *sn;
    do
    {
        sn = this->Statement();
        if (sn != NULL)
        {
            sgn->AddStatement(sn);
        }
    } while (sn != NULL);
    return sgn;
}

StatementNode *Parser::Statement()
{
    TokenType t = this->scanner->peekNextToken().GetTokenType();
    switch (t)
    {
    case INT_TOKEN:
        return this->DeclarationStatement();
    case IDENTIFIER_TOKEN:
        return this->AssignmentStatement();
    case IF_TOKEN:
        return this->IfStatement();
    case WHILE_TOKEN:
        return this->WhileStatement();
    case FOR_TOKEN:
        return this->ForStatement();
    case COUT_TOKEN:
        return this->CoutStatement();
    }
    return NULL;
}

DeclarationStatementNode *Parser::DeclarationStatement()
{
    this->Match(INT_TOKEN);
    IdentifierNode *in = this->Identifier();
    Token t = this->scanner->peekNextToken();
    TokenType tt = t.GetTokenType();
    switch (tt)
    {
    case SEMICOLON_TOKEN:
        this->Match(tt);
        return new DeclarationStatementNode(in);
    case ASSIGNMENT_TOKEN:
    {
        this->Match(tt);
        ExpressionNode *en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new DeclarationAssignmentStatementNode(in, en);
    }
    default:
        std::cerr << "error: invalid declaration: " << t << std::endl;
        break;
    }
    return NULL;
}

AssignmentStatementNode *Parser::AssignmentStatement()
{
    IdentifierNode *in = this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    ExpressionNode *en = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    return new AssignmentStatementNode(in, en);
}

IfStatementNode *Parser::IfStatement()
{
    this->Match(IF_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    ExpressionNode *en = this->Expression();
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode *bn = this->Block();
    return new IfStatementNode(en, bn);
}

WhileStatementNode *Parser::WhileStatement()
{
    this->Match(WHILE_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    ExpressionNode *en = this->Expression();
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode *bn = this->Block();
    return new WhileStatementNode(en, bn);
}

ForStatementNode *Parser::ForStatement()
{
    this->Match(FOR_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    StatementNode *initializer = this->Statement();
    ExpressionNode *comparison = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    IdentifierNode *in = this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    ExpressionNode *en = this->Expression();
    AssignmentStatementNode *incrementer = new AssignmentStatementNode(in, en);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode *bn = this->Block();
    return new ForStatementNode(initializer, comparison, incrementer, bn);
}

CoutStatementNode *Parser::CoutStatement()
{
    this->Match(COUT_TOKEN);
    this->Match(INSERTION_TOKEN);
    ExpressionNode *en = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    return new CoutStatementNode(en);
}

ExpressionNode *Parser::Expression()
{
    return this->Or();
}

ExpressionNode *Parser::Or()
{
    ExpressionNode *current = And();
    TokenType tt = this->scanner->peekNextToken().GetTokenType();
    if (tt == OR_TOKEN)
    {
        Match(tt);
        current = new OrNode(current, Factor());
    }
    return current;
}

ExpressionNode *Parser::And()
{
    ExpressionNode *current = Relational();
    TokenType tt = this->scanner->peekNextToken().GetTokenType();
    if (tt == AND_TOKEN)
    {
        Match(tt);
        current = new AndNode(current, Factor());
    }
    return current;
}

ExpressionNode *Parser::Relational()
{
    ExpressionNode *en = this->PlusMinus();

    TokenType t = this->scanner->peekNextToken().GetTokenType();
    switch (t)
    {
    case LESS_TOKEN:
        this->Match(t);
        en = new LessNode(en, this->PlusMinus());
        break;
    case LESS_EQUAL_TOKEN:
        this->Match(t);
        en = new LessEqualNode(en, this->PlusMinus());
        break;
    case GREATER_TOKEN:
        this->Match(t);
        en = new GreaterNode(en, this->PlusMinus());
        break;
    case GREATER_EQUAL_TOKEN:
        this->Match(t);
        en = new GreaterEqualNode(en, this->PlusMinus());
        break;
    case EQUAL_TOKEN:
        this->Match(t);
        en = new EqualNode(en, this->PlusMinus());
        break;
    case NOT_EQUAL_TOKEN:
        this->Match(t);
        en = new NotEqualNode(en, this->PlusMinus());
        break;
    case BITWISE_AND_TOKEN:
        this->Match(t);
        en = new BitwiseAndNode(en, this->PlusMinus());
        break;
    case BITWISE_OR_TOKEN:
        this->Match(t);
        en = new BitwiseOrNode(en, this->PlusMinus());
        break;
    }
    return en;
}

ExpressionNode *Parser::PlusMinus()
{
    ExpressionNode *en = this->TimesDivide();

    for (;;)
    {
        TokenType t = this->scanner->peekNextToken().GetTokenType();
        switch (t)
        {
        case PLUS_TOKEN:
            this->Match(t);
            en = new PlusNode(en, this->TimesDivide());
            break;
        case MINUS_TOKEN:
            this->Match(t);
            en = new MinusNode(en, this->TimesDivide());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode *Parser::TimesDivide()
{
    ExpressionNode *en = this->Factor();

    while (true)
    {
        TokenType t = this->scanner->peekNextToken().GetTokenType();
        switch (t)
        {
        case MULTIPLY_TOKEN:
            this->Match(t);
            en = new TimesNode(en, this->Factor());
            break;
        case DIVIDE_TOKEN:
            this->Match(t);
            en = new DivideNode(en, this->Factor());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode *Parser::Factor()
{
    ExpressionNode *en;
    TokenType t = this->scanner->peekNextToken().GetTokenType();
    switch (t)
    {
    case IDENTIFIER_TOKEN:
        en = this->Identifier();
        break;
    case INTEGER_TOKEN:
        en = this->Integer();
        break;
    case LEFT_PAREN_TOKEN:
        this->Match(LEFT_PAREN_TOKEN);
        en = this->Expression();
        this->Match(RIGHT_PAREN_TOKEN);
        break;
    default:
        std::cerr << "error: expected factor type, got: " << Token::GetTokenTypeName(t) << std::endl;
        exit(EXIT_FAILURE);
    }
    return en;
}

IdentifierNode *Parser::Identifier()
{
    Token t = this->Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(t.GetLexeme(), this->table);
}

IntegerNode *Parser::Integer()
{
    Token t = this->Match(INTEGER_TOKEN);
    int i = atoi(t.GetLexeme().c_str());
    return new IntegerNode(i);
}