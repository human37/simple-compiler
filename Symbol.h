#if !defined(SYMBOL_H)
#define SYMBOL_H

#include <string>
#include <vector>
#include <iostream>

class SymbolTableClass
{

    struct Variable
    {
        std::string mLabel;
        int mValue;
    };

private:
    std::vector<Variable> symbolTable;

public:
    SymbolTableClass();
    ~SymbolTableClass();
    // returns true if <s> is already in the symbol table.
    bool Exists(const std::string &s);
    // adds <s> to the symbol table,
    // or quits if it was already there
    void AddEntry(const std::string &s);
    // returns the current value of variable <s>, when
    // interpreting. Meaningless for Coding and Executing.
    // Prints a message and quits if variable s does not exist.
    int GetValue(const std::string &s);
    // sets variable <s> to the given value, when interpreting.
    // Meaningless for Coding and Executing.
    // Prints a message and quits if variable s does not exist.
    void SetValue(const std::string &s, int v);
    // returns the index of where variable <s> is.
    // returns -1 if variable <s> is not there.
    int GetIndex(const std::string &s);
    // returns the current number of variables in the symbol
    // table.
    int GetCount();
};

#endif //SYMBOL_H