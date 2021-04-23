#if !defined(VALUE_H)
#define VALUE_H

#include <string>
#include "../Symbol.h"
#include "../Instructions.h"

class ExpressionNode;
class IntegerNode;
class IdentifierNode;

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;
};


class IntegerNode : public ExpressionNode {
private:
    int value;
public:
    IntegerNode(int i);
    // Return the integer value
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class IdentifierNode : public ExpressionNode {
private:
    std::string label;
    SymbolTableClass* table;
public:
    IdentifierNode(std::string label, SymbolTableClass* table);
    ~IdentifierNode();

    void DeclareVariable();
    void SetValue(int v);
    // Index into symbol table
    int GetIndex();
    // Return the integer value of the identifier
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

#endif // VALUE_H
