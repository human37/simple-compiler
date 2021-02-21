#if !defined(TOKEN_H)
#define TOKEN_H

#include <string>
#include <iostream>

enum TokenType
{
    // Reserved Words:
    VOID_TOKEN,
    MAIN_TOKEN,
    INT_TOKEN,
    COUT_TOKEN,
    RESERVED_COUNT,
    // Relational Operators:
    LESS_TOKEN,
    LESS_EQUAL_TOKEN,
    GREATER_TOKEN,
    GREATER_EQUAL_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,
    // Other Operators:
    INSERTION_TOKEN,
    EXTRACTION_TOKEN,
    ASSIGNMENT_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIVIDE_TOKEN,
    NOT_TOKEN,
    // Other Characters:
    SEMICOLON_TOKEN,
    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    LEFT_BRACE_TOKEN,
    RIGHT_BRACE_TOKEN,
    // Other Token Types:
    IDENTIFIER_TOKEN,
    INTEGER_TOKEN,
    BAD_TOKEN,
    ENDFILE_TOKEN
};

class Token
{
private:
    TokenType type;
    std::string lexeme;

public:
    static const std::string &GetTokenTypeName(TokenType type);

    Token();
    Token(TokenType type, const std::string &lexeme);
    ~Token();

    const std::string &GetTokenTypeName() const;
    TokenType GetTokenType() const;
    std::string GetLexeme() const;

    // If this lexeme is one of the reserved words, then assign it that token
    void CheckReserved();
};

// Outputs token type, name, and lexeme
std::ostream &operator<<(std::ostream &out, const Token &tc);

#endif // TOKEN_H