#include "Symbol.h"

SymbolTableClass::SymbolTableClass()
{}

SymbolTableClass::~SymbolTableClass()
{}

bool SymbolTableClass::Exists(const std::string &s)
{
    for (int i = 0; i < symbolTable.size(); i++)
    {
        if (symbolTable[i].mLabel == s)
            return true;
    }
    return false;
}

void SymbolTableClass::AddEntry(const std::string &s)
{
    if (!Exists(s)) 
    {
        Variable v = {s, 0};
        symbolTable.push_back(v);
    }
}

int SymbolTableClass::GetValue(const std::string &s)
{
    if (!Exists(s))
    {
        std::cout << "error, label:" << s << " does not exist" << std::endl;
        exit(EXIT_FAILURE);
    }
    int index = GetIndex(s);
    if (index != -1)
        return symbolTable[index].mValue;
    return -1;
}

void SymbolTableClass::SetValue(const std::string &s, int v)
{
    if (!Exists(s))
    {
        std::cout << "error, label:" << s << " does not exist" << std::endl;
        exit(EXIT_FAILURE);
    }
    int index = GetIndex(s);
    if (index != -1)
        symbolTable[index].mValue = v;
}

int SymbolTableClass::GetIndex(const std::string &s)
{
    for (int i = 0; i < symbolTable.size(); i++)
    {
        if (symbolTable[i].mLabel == s)
            return i;
    }
    return -1;
}