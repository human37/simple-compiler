#include "instructions.h"
#include <iostream>

int main()
{
    InstructionsClass ic;
    ic.PushValue(1000);
    ic.PopAndWrite();
    ic.Finish();
    ic.PrintAllMachineCodes();
    ic.Execute();
    std::cout << "success." << std::endl;
    return 0;
}