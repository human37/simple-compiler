#if !defined(NODE_H)
#define NODE_H

#include <vector>
#include "Symbol.h"
#include "Instructions.h"

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class DeclarationAssignmentStatementNode;
class AssignmentStatementNode;
class IfStatementNode;
class WhileStatementNode;
class ForStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DividesNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;
class BitwiseAndNode;
class BitwiseOrNode;
class AndNode;
class OrNode;

class Node
{
public:
    virtual ~Node();
    virtual void Interpret() = 0;
    virtual void Code(InstructionsClass &machineCode) = 0;
};

class StartNode : public Node
{
private:
    ProgramNode *programNode;

public:
    StartNode(ProgramNode *pn);
    void Code(InstructionsClass &machineCode);
    ~StartNode();
    void Interpret();
};

class ProgramNode : public Node
{
private:
    BlockNode *blockNode;

public:
    ProgramNode(BlockNode *bn);
    void Code(InstructionsClass &machineCode);
    ~ProgramNode();
    void Interpret();
};

class StatementNode : public Node
{
private:
public:
};

class BlockNode : public StatementNode
{
private:
    StatementGroupNode *sgNode;

public:
    BlockNode(StatementGroupNode *sgn);
    void Code(InstructionsClass &machineCode);
    ~BlockNode();

    void Interpret();
};

class StatementGroupNode : public Node
{
private:
    std::vector<StatementNode *> nodes;

public:
    StatementGroupNode();
    ~StatementGroupNode();

    void Interpret();
    void AddStatement(StatementNode *node);
    void Code(InstructionsClass &machineCode);
};

class DeclarationStatementNode : public StatementNode
{
protected:
    IdentifierNode *IDNode;

public:
    DeclarationStatementNode(IdentifierNode *in);
    ~DeclarationStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

class DeclarationAssignmentStatementNode : public DeclarationStatementNode
{
private:
    ExpressionNode *expNode;

public:
    DeclarationAssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    ~DeclarationAssignmentStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

class AssignmentStatementNode : public StatementNode
{
private:
    IdentifierNode *IDNode;
    ExpressionNode *expNode;

public:
    AssignmentStatementNode(IdentifierNode *in, ExpressionNode *en);
    ~AssignmentStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

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

class WhileStatementNode : public StatementNode
{
private:
    ExpressionNode *expNode;
    BlockNode *blockNode;

public:
    WhileStatementNode(ExpressionNode *en, BlockNode *bn);
    ~WhileStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};
class ForStatementNode : public StatementNode
{
private:
    StatementNode *initializer;
    ExpressionNode *comparison;
    StatementNode *incrementer;
    BlockNode *blockNode;

public:
    ForStatementNode(
        StatementNode *initializer,
        ExpressionNode *comparison,
        StatementNode *incrementer,
        BlockNode *bn);
    ~ForStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

class ForeStatementNode : public StatementNode
{
private:
    StatementNode *initializer;
    ExpressionNode *comparison;
    StatementNode *incrementer;
    BlockNode *blockNode;

public:
    ForeStatementNode(
        StatementNode *initializer,
        ExpressionNode *comparison,
        StatementNode *incrementer,
        BlockNode *bn);
    ~ForeStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

class CoutStatementNode : public StatementNode
{
private:
    std::vector<ExpressionNode *> expNodes;

public:
    CoutStatementNode(std::vector<ExpressionNode *> expNodes);
    ~CoutStatementNode();
    void Code(InstructionsClass &machineCode);
    void Interpret();
};

class ExpressionNode
{
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;
};

class IntegerNode : public ExpressionNode
{
private:
    int value;

public:
    IntegerNode(int i);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class IdentifierNode : public ExpressionNode
{
private:
    std::string label;
    SymbolTableClass *table;

public:
    IdentifierNode(std::string label, SymbolTableClass *symTable);
    ~IdentifierNode();
    void CodeEvaluate(InstructionsClass &machineCode);
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    int Evaluate();
};

class BinaryOperatorNode : public ExpressionNode
{
protected:
    ExpressionNode *left;
    ExpressionNode *right;

public:
    BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
    ~BinaryOperatorNode();
};

// Mathematical operators

class PlusNode : public BinaryOperatorNode
{
private:
public:
    PlusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class MinusNode : public BinaryOperatorNode
{
private:
public:
    MinusNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class TimesNode : public BinaryOperatorNode
{
private:
public:
    TimesNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class DivideNode : public BinaryOperatorNode
{
private:
public:
    DivideNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

// Relational operators

class LessNode : public BinaryOperatorNode
{
private:
public:
    LessNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class LessEqualNode : public BinaryOperatorNode
{
private:
public:
    LessEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterNode : public BinaryOperatorNode
{
private:
public:
    GreaterNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterEqualNode : public BinaryOperatorNode
{
private:
public:
    GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class EqualNode : public BinaryOperatorNode
{
private:
public:
    EqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class NotEqualNode : public BinaryOperatorNode
{
private:
public:
    NotEqualNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class BitwiseAndNode : public BinaryOperatorNode
{
private:
public:
    BitwiseAndNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class BitwiseOrNode : public BinaryOperatorNode
{
private:
public:
    BitwiseOrNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class AndNode : public BinaryOperatorNode
{
private:
public:
    AndNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

class OrNode : public BinaryOperatorNode
{
private:
public:
    OrNode(ExpressionNode *left, ExpressionNode *right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass &machineCode);
};

#endif // NODE_H