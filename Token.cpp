#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Token.h"

const std::string gTokenTypeNames[] = {
    "VOID", "MAIN", "INT", "COUT", "IF",
    "WHILE", "FOR", "RESERVED_COUNT",
    "SEMICOLON",
    "LEFT_PAREN", "RIGHT_PAREN",
    "LEFT_BRACE", "RIGHT_BRACE",
    "LESS", "LESS_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "EQUAL", "NOT_EQUAL",
    "BITWISE_AND", "BITWISE_OR",
    "NOT", "AND", "OR",
    "INSERTION", "EXTRACTION", "ASSIGNMENT",
    "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
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
    : type(type), lexeme(lexeme)
{
}

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
        << "\e[34m" << std::setw(15) << tc.GetTokenTypeName() << "\e[0m"
        << "lexeme: "
        << "\e[32m" << std::setw(5) << tc.GetLexeme() << "\e[0m";
    return out;
}