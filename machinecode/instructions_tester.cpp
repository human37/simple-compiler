#include "instructions.h"
#include <iostream>

int main()
{
    InstructionsClass ic;
    ic.PushVariable(10);
    ic.PopAndWrite();
    ic.Finish();
    ic.PrintAllMachineCodes();
    ic.Execute();
    std::cout << "success." << std::endl;
    return 0;
}