#if !defined(STATEMACHINE_H)
#define STATEMACHINE_H

#include "Token.h"

enum MachineState
{
    START_STATE,
    IDENTIFIER_STATE,
    INTEGER_STATE,
    // Scope
    SEMICOLON_STATE,
    LEFT_PAREN_STATE,
    RIGHT_PAREN_STATE,
    LEFT_BRACE_STATE,
    RIGHT_BRACE_STATE,
    // Relational
    LESS_STATE,
    LESS_EQUAL_STATE,
    GREATER_STATE,
    GREATER_EQUAL_STATE,
    EQUALITY_STATE,
    NOT_EQUAL_STATE,
    BITWISE_AND_STATE,
    BITWISE_OR_STATE,
    NOT_STATE,
    AND_STATE,
    OR_STATE,
    INSERTION_STATE,
    EXTRACTION_STATE,
    ASSIGNMENT_STATE,
    PLUS_STATE,
    MINUS_STATE,
    MULTIPLY_STATE,
    DIVIDE_STATE,
    PLUS_EQUALS_STATE,
    MINUS_EQUALS_STATE,
    // Other
    LINE_COMMENT_STATE,
    BLOCK_COMMENT_STATE,
    BLOCK_COMMENT_ENDING_STATE,
    CANTMOVE_STATE,
    ENDFILE_STATE,
    LAST_STATE
};

enum CharacterType
{
    DIGIT_CHAR,
    LETTER_CHAR,
    WHITESPACE_CHAR,
    NEWLINE_CHAR,
    SEMICOLON_CHAR,
    LEFT_PAREN_CHAR,
    RIGHT_PAREN_CHAR,
    LEFT_BRACE_CHAR,
    RIGHT_BRACE_CHAR,
    EQUALS_CHAR,
    PLUS_CHAR,
    MINUS_CHAR,
    STAR_CHAR,
    FORWARD_SLASH_CHAR,
    LESS_CHAR,
    GREATER_CHAR,
    NOT_CHAR,
    AND_CHAR,
    OR_CHAR,
    BAD_CHAR,
    ENDFILE_CHAR,
    LAST_CHAR
};

class StateMachine
{

public:
    StateMachine();
    MachineState UpdateState(char currentCharacter, TokenType &correspondingTokenType);

private:
    MachineState currentState;
    // The matrix of legal moves:
    MachineState legalMoves[LAST_STATE][LAST_CHAR];
    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType correspondingTokenTypes[LAST_STATE];
};

#endif // STATEMACHINE_H