#if !defined(RELATIONAL_H)
#define RELATIONAL_H

#include "value.h"
#include "operator.h"

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

class LessNode : public BinaryOperatorNode {
private:

public:
    LessNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class LessEqualNode : public BinaryOperatorNode {
private:

public:
    LessEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class GreaterNode : public BinaryOperatorNode {
private:

public:
    GreaterNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class GreaterEqualNode : public BinaryOperatorNode {
private:

public:
    GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class EqualNode : public BinaryOperatorNode {
private:

public:
    EqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class NotEqualNode : public BinaryOperatorNode {
private:

public:
    NotEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class BitwiseAndNode : public BinaryOperatorNode {
private:

public:
    BitwiseAndNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class BitwiseOrNode : public BinaryOperatorNode {
private:

public:
    BitwiseOrNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class AndNode : public BinaryOperatorNode {
private:

public:
    AndNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};
class OrNode : public BinaryOperatorNode {
private:

public:
    OrNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class NotNode : public UnaryOperatorNode {
private:

public:
    NotNode(ExpressionNode* val);
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

#endif // RELATIONAL_H
