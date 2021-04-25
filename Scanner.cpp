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
    StateMachine sm = StateMachine();
    MachineState state;
    char next;
    TokenType type;
    std::string lexeme = "";
    do
    {
        next = this->mFin.get();
        state = sm.UpdateState(next, type);
        lexeme += next;
        if (state == START_STATE)
        {
            lexeme = "";
        }
        if (next == '\n' && state != CANTMOVE_STATE)
        {
            this->mLineNumber++;
        }
    } while (state != CANTMOVE_STATE);

    this->mFin.unget();
    lexeme.pop_back();
    if (type == BAD_TOKEN)
    {
        std::cout << "bad token parsed: " << std::endl;
        exit(EXIT_FAILURE);
    }
    Token tok = Token(type, lexeme, this->mFileName, mLineNumber);
    tok.CheckReserved();
    return tok;
}

Token ScannerClass::peekNextToken()
{
    std::streampos pos = mFin.tellg();
    int line = mLineNumber;
    Token token = getNextToken();
    if (!mFin)
    {
        mFin.clear();
    }
    mFin.seekg(pos);
    mLineNumber = line;
    return token;
}