#include "operator.h"

TernaryOperatorNode::TernaryOperatorNode(ExpressionNode* first, ExpressionNode* second, ExpressionNode* third)
    : first(first), second(second), third(third) {}
TernaryOperatorNode::~TernaryOperatorNode() {
    delete first;
    delete second;
    delete third;
}
int TernaryOperatorNode::Evaluate() {
    return first->Evaluate() ? second->Evaluate() : third->Evaluate();
}
void TernaryOperatorNode::CodeEvaluate(InstructionsClass& machineCode) {
    // FIX:
    this->first->CodeEvaluate(machineCode);
    unsigned char* insertAddress = machineCode.SkipIfZeroStack();
    unsigned char* address1 = machineCode.GetAddress();
    this->second->CodeEvaluate(machineCode);
    unsigned char* address2 = machineCode.GetAddress();
    machineCode.SetOffset(insertAddress, (int)(address2 - address1));
}


BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
    : left(left), right(right) {}
BinaryOperatorNode::~BinaryOperatorNode() {
    delete left;
    delete right;
}

UnaryOperatorNode::UnaryOperatorNode(ExpressionNode* val)
    : val(val) {}
UnaryOperatorNode::~UnaryOperatorNode() {
    delete val;
}