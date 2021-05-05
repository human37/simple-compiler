#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Token.h"

const std::string gTokenTypeNames[] = {
    // Reserved words
    "VOID", "MAIN", "INT", "COUT", "ENDL",
    "IF", "WHILE", "FOR", "RESERVED_COUNT",
    // Scope tokens
    "SEMICOLON",
    "LEFT_PAREN", "RIGHT_PAREN",
    "LEFT_BRACE", "RIGHT_BRACE",
    // Relational tokens
    "LESS", "LESS_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "EQUAL", "NOT_EQUAL",
    "BITWISE_AND", "BITWISE_OR",
    "NOT", "AND", "OR",
    "INSERTION", "EXTRACTION", "ASSIGNMENT",
    "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
    "PLUS_EQUALS", "MINUS_EQUALS",
    "MULTIPLY_BY",
    // Other token types
    "IDENTIFIER", "INTEGER",
    "BAD", "END_FILE"};

std::string toUpper(std::string in)
{
    std::string up = in;
    for (int i = 0; i < up.length(); i++)
    {
        up[i] = toupper(up[i]);
    }
    return up;
}

const std::string &Token::GetTokenTypeName(TokenType type)
{
    return gTokenTypeNames[type];
}

Token::Token()
{
}

Token::Token(TokenType type, const std::string &lexeme)
    : type(type), lexeme(lexeme), filename(""), line(1)
{
}

Token::Token(TokenType type, const std::string &lexeme, std::string fileName, int line)
    : type(type), lexeme(lexeme), filename(fileName), line(line) {}

Token::~Token()
{
}

const std::string &Token::GetTokenTypeName() const
{
    return gTokenTypeNames[this->type];
}

TokenType Token::GetTokenType() const
{
    return this->type;
}

std::string Token::GetLexeme() const
{
    return this->lexeme;
}

void Token::CheckReserved()
{
    for (int i = 0; i < RESERVED_COUNT; i++)
    {
        if (toUpper(this->lexeme) == gTokenTypeNames[i])
        {
            this->type = TokenType(i);
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Token &tc)
{
    out.setf(std::ios::left);
    out << "type: "
        << "\e[31m" << std::setw(15) << tc.GetTokenTypeName() << "\e[0m"
        << "lexeme: "
        << "\e[31m" << std::setw(5) << tc.GetLexeme() << "\e[0m";
    return out;
}