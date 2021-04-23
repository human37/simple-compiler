#if !defined(BASE_H)
#define BASE_H

#include <vector>
#include "../Instructions.h"

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;

class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass& machineCode) = 0;
};

class StartNode : public Node {
private:
    ProgramNode* programNode;
public:
    StartNode(ProgramNode* pn);
    ~StartNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ProgramNode : public Node {
private:
    BlockNode* blockNode;
public:
    ProgramNode(BlockNode* bn);
    ~ProgramNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class StatementNode : public Node {
private:

public:
};

class BlockNode : public StatementNode {
private:
    StatementGroupNode* sgNode;
public:
    BlockNode(StatementGroupNode* sgn);
    ~BlockNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class StatementGroupNode : public Node {
private:
    std::vector<StatementNode*> nodes;
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);

    void AddStatement(StatementNode* node);
};

#endif // BASE_H
