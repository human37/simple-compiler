#if !defined(OPERATOR_H)
#define OPERATOR_H

#include "value.h"

// Only one ternary operator
class TernaryOperatorNode : public ExpressionNode {
private:
    ExpressionNode* first;
    ExpressionNode* second;
    ExpressionNode* third;
public:
    TernaryOperatorNode(ExpressionNode* first, ExpressionNode* second, ExpressionNode* third);
    ~TernaryOperatorNode();

    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class BinaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode* left;
    ExpressionNode* right;
public:
    BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
    ~BinaryOperatorNode();
};

class UnaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode* val;
public:
    UnaryOperatorNode(ExpressionNode* val);
    ~UnaryOperatorNode();
};

#endif // OPERATOR_H
