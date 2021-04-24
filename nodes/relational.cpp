#include "relational.h"

// =========================================================
// Relational operators
// =========================================================


LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int LessNode::Evaluate() {
    return this->left->Evaluate() < this->right->Evaluate();
}
void LessNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int LessEqualNode::Evaluate() {
    return this->left->Evaluate() <= this->right->Evaluate();
}
void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int GreaterNode::Evaluate() {
    return this->left->Evaluate() > this->right->Evaluate();
}
void GreaterNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int GreaterEqualNode::Evaluate() {
    return this->left->Evaluate() >= this->right->Evaluate();
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int EqualNode::Evaluate() {
    return this->left->Evaluate() == this->right->Evaluate();
}
void EqualNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int NotEqualNode::Evaluate() {
    return this->left->Evaluate() != this->right->Evaluate();
}
void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}


// =========================================================
// AND/OR
// =========================================================


BitwiseAndNode::BitwiseAndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int BitwiseAndNode::Evaluate() {
    return this->left->Evaluate() & this->right->Evaluate();
}
void BitwiseAndNode::CodeEvaluate(InstructionsClass& machineCode) {
    // FIX: find code for bitwise AND/OR
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}


BitwiseOrNode::BitwiseOrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int BitwiseOrNode::Evaluate() {
    return this->left->Evaluate() | this->right->Evaluate();
}
void BitwiseOrNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}


AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int AndNode::Evaluate() {
    return this->left->Evaluate() && this->right->Evaluate();
}
void AndNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int OrNode::Evaluate() {
    return this->left->Evaluate() || this->right->Evaluate();
}
void OrNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}

// NOT

NotNode::NotNode(ExpressionNode* val)
    : UnaryOperatorNode(val) {}
int NotNode::Evaluate() {
    return !this->val->Evaluate();
}
void NotNode::CodeEvaluate(InstructionsClass& machineCode) {
    // FIX: this might work actually lol
    this->val->CodeEvaluate(machineCode);
    machineCode.PushValue(1);
    machineCode.PopPopSubPush();
}