#if !defined(MATH_H)
#define MATH_H

#include "value.h"
#include "operator.h"

class PlusNode;
class MinusNode;
class TimesNode;
class DividesNode;
class ExponentNode;

class PlusNode : public BinaryOperatorNode {
private:

public:
    PlusNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class MinusNode : public BinaryOperatorNode {
private:

public:
    MinusNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class TimesNode : public BinaryOperatorNode {
private:

public:
    TimesNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class DivideNode : public BinaryOperatorNode {
private:

public:
    DivideNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class ExponentNode : public BinaryOperatorNode {
private:

public:
    ExponentNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class NegativeNode : public UnaryOperatorNode {
private:

public:
    NegativeNode(ExpressionNode* val);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

#endif // MATH_H
