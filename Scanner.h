#if !defined(SCANNER_H)
#define SCANNER_H

#include <string>
#include <fstream>
#include <iostream>
#include "Token.h"
#include "StateMachine.h"
#include "Debug.h"

class ScannerClass
{

public:
    ScannerClass(std::string input);
    ~ScannerClass();
    Token getNextToken();
    int getLineNumber();

private:
    std::ifstream mFin;
    int mLineNumber;
    std::string mFileName;
};

#endif // SCANNER_H