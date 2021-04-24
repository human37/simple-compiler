#if !defined(KEYWORD_H)
#define KEYWORD_H

#include <vector>
#include "base.h"
#include "value.h"

class IfElseStatementNode;
class WhileStatementNode;
class ForStatementNode;
class ForeStatementNode;
class CoutStatementNode;
class CinStatementNode;

class IfStatementNode : public StatementNode
{
private:
    ExpressionNode *expNode;
    BlockNode *blockNode;

public:
    IfStatementNode(ExpressionNode *en, BlockNode *bn);
    ~IfStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};


class WhileStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    BlockNode* blockNode;
public:
    WhileStatementNode(ExpressionNode* en, BlockNode* bn);
    ~WhileStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ForStatementNode : public StatementNode {
protected:
    StatementNode* initializer;
    ExpressionNode* comparison;
    StatementNode* incrementer;
    BlockNode* blockNode;
public:
    ForStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn);
    ~ForStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ForeStatementNode : public ForStatementNode {
private:
public:
    ForeStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class CoutStatementNode : public StatementNode {
private:
    std::vector<ExpressionNode*> expNodes;
public:
    CoutStatementNode(std::vector<ExpressionNode*> ens);
    ~CoutStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class CinStatementNode : public StatementNode {
private:
    std::vector<IdentifierNode*> variables;
public:
    CinStatementNode(std::vector<IdentifierNode*> vars);
    ~CinStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

#endif // KEYWORD_H
