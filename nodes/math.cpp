#include <cmath>
#include "math.h"

// =========================================================
// Mathematical operators
// =========================================================


PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int PlusNode::Evaluate() {
    return this->left->Evaluate() + this->right->Evaluate();
}
void PlusNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}


MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int MinusNode::Evaluate() {
    return this->left->Evaluate() - this->right->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int TimesNode::Evaluate() {
    return this->left->Evaluate() * this->right->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int DivideNode::Evaluate() {
    return this->left->Evaluate() / this->right->Evaluate();
}
void DivideNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

ExponentNode::ExponentNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int ExponentNode::Evaluate() {
    return pow(this->left->Evaluate(), this->right->Evaluate());
}
void ExponentNode::CodeEvaluate(InstructionsClass& machineCode) {
    // FIX:
    int val = pow(this->left->Evaluate(), this->right->Evaluate());
    machineCode.PushValue(val);
}

NegativeNode::NegativeNode(ExpressionNode* val)
    : UnaryOperatorNode(val) {}
int NegativeNode::Evaluate() {
    return -1 * this->val->Evaluate();
}
void NegativeNode::CodeEvaluate(InstructionsClass& machineCode) {
    this->val->CodeEvaluate(machineCode);
    machineCode.PushValue(-1);
    machineCode.PopPopMulPush();
}