#include "Scanner.h"

ScannerClass::ScannerClass(std::string input)
    : mFileName(input), mLineNumber(1)
{
    MSG("initializing ScannerClass constructor");
    mFin.open(mFileName, std::ios::binary);
    if (!mFin.is_open())
    {
        std::cout << "could not open: " << input << std::endl;
        exit(EXIT_FAILURE);
    }
}

ScannerClass::~ScannerClass()
{
    MSG("closing the file stream");
    mFin.close();
}

int ScannerClass::getLineNumber()
{
    return mLineNumber;
}

Token ScannerClass::getNextToken()
{
    StateMachine stateMachine;
    MachineState currentState = START_STATE;
    TokenType type;
    std::string lexeme = "";
    do
    {
        char c = mFin.get();
        lexeme += c;
        currentState = stateMachine.UpdateState(c, type);
        if (currentState == START_STATE)
            lexeme = "";
        if (c == '\n' && currentState == CANTMOVE_STATE)
            mLineNumber++;
    } while (!mFin.eof() && currentState != CANTMOVE_STATE);
    if (mFin.eof())
        type = ENDFILE_TOKEN;
    mFin.unget();
    lexeme.pop_back();
    if (type == BAD_TOKEN)
    {
        std::cout << "bad token found bro: \n"
                  << type << "\n";
        exit(EXIT_FAILURE);
    }
    MSG("type is: " + type);
    Token token = Token(type, lexeme);
    return token;
}

Token ScannerClass::peekNextToken() {
    std::streampos pos = mFin.tellg();
    int line = mLineNumber;
    int column = mColumnNumber;
    Token token = getNextToken();
    if (!mFin) {
        mFin.clear();
    }
    mFin.seekg(pos);
    mLineNumber = line;
    mColumnNumber = column;
    return token;
}