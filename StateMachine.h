#if !defined(STATEMACHINE_H)
#define STATEMACHINE_H

#include "Token.h"

enum MachineState
{
    START_STATE,
    IDENTIFIER_STATE,
    INTEGER_STATE,
    LEFT_PAREN_STATE,
    RIGHT_PAREN_STATE,
    LEFT_BRACE_STATE,
    RIGHT_BRACE_STATE,
    ASSIGNMENT_STATE,
    PLUS_STATE,
    MINUS_STATE,
    DIVIDE_STATE,
    MULTIPLY_STATE,
    EQUALITY_STATE,
    NOT_EQUAL_STATE,
    LESS_STATE,
    LESS_EQUAL_STATE,
    GREATER_STATE,
    GREATER_EQUAL_STATE,
    NOT_STATE,
    INSERTION_STATE,
    EXTRACTION_STATE,
    SEMICOLON_STATE,
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
    LEFT_PAREN_CHAR,
    RIGHT_PAREN_CHAR,
    LEFT_BRACE_CHAR,
    RIGHT_BRACE_CHAR,
    EQUALS_CHAR,
    PLUS_CHAR,
    MINUS_CHAR,
    FORWARD_SLASH_CHAR,
    STAR_CHAR,
    LESS_CHAR,
    GREATER_CHAR,
    BANG_CHAR,
    SEMICOLON_CHAR,
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