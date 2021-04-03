#include "StateMachine.h"

StateMachine::StateMachine()
{
    currentState = START_STATE;
    // first, initialize all the legalMoves to CANTMOVE_STATE
    // then, reset the legalMoves that are legitimate
    for (int i = 0; i < LAST_STATE; i++)
        for (int j = 0; j < LAST_CHAR; j++)
            this->legalMoves[i][j] = CANTMOVE_STATE;
    
    this->legalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
    this->legalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    this->legalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
    this->legalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
    this->legalMoves[START_STATE][LEFT_PAREN_CHAR] = LEFT_PAREN_STATE;
    this->legalMoves[START_STATE][RIGHT_PAREN_CHAR] = RIGHT_PAREN_STATE;
    this->legalMoves[START_STATE][LEFT_BRACE_CHAR] = LEFT_BRACE_STATE;
    this->legalMoves[START_STATE][RIGHT_BRACE_CHAR] = RIGHT_BRACE_STATE;
    this->legalMoves[START_STATE][EQUALS_CHAR] = ASSIGNMENT_STATE;
    this->legalMoves[ASSIGNMENT_STATE][EQUALS_CHAR] = EQUALITY_STATE;
    this->legalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
    this->legalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
    this->legalMoves[START_STATE][FORWARD_SLASH_CHAR] = DIVIDE_STATE;
    this->legalMoves[START_STATE][AND_CHAR] = BITWISE_AND_STATE;
    this->legalMoves[BITWISE_AND_STATE][AND_CHAR] = AND_STATE;
    this->legalMoves[START_STATE][OR_CHAR] = BITWISE_OR_STATE;
    this->legalMoves[BITWISE_OR_STATE][OR_CHAR] = OR_STATE;

    // line comments
    this->legalMoves[DIVIDE_STATE][FORWARD_SLASH_CHAR] = LINE_COMMENT_STATE;
    for (int s = 0; s < LAST_CHAR; s++)
        this->legalMoves[LINE_COMMENT_STATE][s] = LINE_COMMENT_STATE;
    this->legalMoves[LINE_COMMENT_STATE][NEWLINE_CHAR] = START_STATE;

    // block comments
    this->legalMoves[DIVIDE_STATE][STAR_CHAR] = BLOCK_COMMENT_STATE;
    for (int s = 0; s < LAST_CHAR; s++)
    {
        this->legalMoves[BLOCK_COMMENT_STATE][s] = BLOCK_COMMENT_STATE;
    }
    this->legalMoves[BLOCK_COMMENT_STATE][STAR_CHAR] = BLOCK_COMMENT_ENDING_STATE;
    for (int s = 0; s < LAST_CHAR; s++)
    {
        this->legalMoves[BLOCK_COMMENT_ENDING_STATE][s] = BLOCK_COMMENT_STATE;
    }
    this->legalMoves[BLOCK_COMMENT_ENDING_STATE][STAR_CHAR] = BLOCK_COMMENT_ENDING_STATE;
    this->legalMoves[BLOCK_COMMENT_ENDING_STATE][FORWARD_SLASH_CHAR] = START_STATE;

    this->legalMoves[START_STATE][STAR_CHAR] = MULTIPLY_STATE;
    this->legalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
    this->legalMoves[LESS_STATE][EQUALS_CHAR] = LESS_EQUAL_STATE;
    this->legalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
    this->legalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;
    this->legalMoves[GREATER_STATE][EQUALS_CHAR] = GREATER_EQUAL_STATE;
    this->legalMoves[GREATER_STATE][GREATER_CHAR] = EXTRACTION_STATE;
    this->legalMoves[START_STATE][NOT_CHAR] = NOT_STATE;
    this->legalMoves[NOT_STATE][EQUALS_CHAR] = NOT_EQUAL_STATE;
    this->legalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
    this->legalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
    this->legalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;
    this->legalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
    this->legalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

    // first, initialize all states to correspond to the BAD token type.
    // then, reset the end states to correspond to the correct token types.
    for (int i = 0; i < LAST_STATE; i++)
    {
        this->correspondingTokenTypes[i] = BAD_TOKEN;
    }
    this->correspondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    this->correspondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    this->correspondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    this->correspondingTokenTypes[LEFT_PAREN_STATE] = LEFT_PAREN_TOKEN;
    this->correspondingTokenTypes[RIGHT_PAREN_STATE] = RIGHT_PAREN_TOKEN;
    this->correspondingTokenTypes[LEFT_BRACE_STATE] = LEFT_BRACE_TOKEN;
    this->correspondingTokenTypes[RIGHT_BRACE_STATE] = RIGHT_BRACE_TOKEN;
    this->correspondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    this->correspondingTokenTypes[LESS_EQUAL_STATE] = LESS_EQUAL_TOKEN;
    this->correspondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    this->correspondingTokenTypes[GREATER_EQUAL_STATE] = GREATER_EQUAL_TOKEN;
    this->correspondingTokenTypes[EQUALITY_STATE] = EQUAL_TOKEN;
    this->correspondingTokenTypes[NOT_EQUAL_STATE] = NOT_EQUAL_TOKEN;
    this->correspondingTokenTypes[NOT_STATE] = NOT_TOKEN;
    this->correspondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    this->correspondingTokenTypes[EXTRACTION_STATE] = EXTRACTION_TOKEN;
    this->correspondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    this->correspondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    this->correspondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    this->correspondingTokenTypes[MULTIPLY_STATE] = MULTIPLY_TOKEN;
    this->correspondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    this->correspondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
    this->correspondingTokenTypes[AND_STATE] = AND_TOKEN;
    this->correspondingTokenTypes[OR_STATE] = OR_TOKEN;
}

MachineState StateMachine::UpdateState(char currentCharacter, TokenType &correspondingTokenType)
{
    // convert the input character into an input character type
    CharacterType charType = BAD_CHAR;
    // decide what character type the input char is
    if (isdigit(currentCharacter))
        charType = DIGIT_CHAR;
    else if (isalpha(currentCharacter))
        charType = LETTER_CHAR;
    else if (isblank(currentCharacter))
        charType = WHITESPACE_CHAR;
    else if (currentCharacter == '\n')
        charType = NEWLINE_CHAR;
    else if (currentCharacter == ';')
        charType = SEMICOLON_CHAR;
    else if (currentCharacter == '(')
        charType = LEFT_PAREN_CHAR;
    else if (currentCharacter == ')')
        charType = RIGHT_PAREN_CHAR;
    else if (currentCharacter == '{')
        charType = LEFT_BRACE_CHAR;
    else if (currentCharacter == '}')
        charType = RIGHT_BRACE_CHAR;
    else if (currentCharacter == '=')
        charType = EQUALS_CHAR;
    else if (currentCharacter == '+')
        charType = PLUS_CHAR;
    else if (currentCharacter == '-')
        charType = MINUS_CHAR;
    else if (currentCharacter == '*')
        charType = STAR_CHAR;
    else if (currentCharacter == '/')
        charType = FORWARD_SLASH_CHAR;
    else if (currentCharacter == '<')
        charType = LESS_CHAR;
    else if (currentCharacter == '>')
        charType = GREATER_CHAR;
    else if (currentCharacter == '|')
        charType = OR_CHAR;
    else if (currentCharacter == '&')
        charType = AND_CHAR;
    else if (currentCharacter == EOF)
        charType = ENDFILE_CHAR;

    // update current state and token
    correspondingTokenType = this->correspondingTokenTypes[this->currentState];
    this->currentState = this->legalMoves[this->currentState][charType];
    return this->currentState;
}