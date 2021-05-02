#if !defined(TOKEN_H)
#define TOKEN_H

#include <string>
#include <iostream>

enum TokenType
{
    VOID_TOKEN,
    MAIN_TOKEN,
    INT_TOKEN,
    COUT_TOKEN,
    ENDL_TOKEN,
    IF_TOKEN,
    WHILE_TOKEN,
    FOR_TOKEN,
    TRUE_TOKEN,
    FALSE_TOKEN,
    RESERVED_COUNT,
    SEMICOLON_TOKEN,
    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    LEFT_BRACE_TOKEN,
    RIGHT_BRACE_TOKEN,
    LESS_TOKEN,
    LESS_EQUAL_TOKEN,
    GREATER_TOKEN,
    GREATER_EQUAL_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,
    BITWISE_AND_TOKEN,
    BITWISE_OR_TOKEN,
    NOT_TOKEN,
    AND_TOKEN,
    OR_TOKEN,
    INSERTION_TOKEN,
    EXTRACTION_TOKEN,
    ASSIGNMENT_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIVIDE_TOKEN,
    PLUS_EQUALS_TOKEN,
    MINUS_EQUALS_TOKEN,
    IDENTIFIER_TOKEN,
    INTEGER_TOKEN,
    BAD_TOKEN,
    ENDFILE_TOKEN,
};

class Token
{
private:
    TokenType type;
    std::string lexeme;
    std::string filename;
    int line;

public:
    static const std::string &GetTokenTypeName(TokenType type);

    Token();
    Token(TokenType type, const std::string &lexeme);
    Token(TokenType type, const std::string& lexeme, std::string fileName, int line);
    ~Token();

    const std::string &GetTokenTypeName() const;
    TokenType GetTokenType() const;
    std::string GetLexeme() const;

    // if this lexeme is one of the reserved words, then assign it that token
    void CheckReserved();

    friend std::ostream &operator<<(std::ostream &out, const Token &tc);
};

#endif // TOKEN_H