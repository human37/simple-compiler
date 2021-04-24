#include "value.h"

ExpressionNode::~ExpressionNode() {}


IntegerNode::IntegerNode(int i)
    : value(i) {}
int IntegerNode::Evaluate() {
    return this->value;
}
void IntegerNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushValue(this->value);
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* table)
    : label(label), table(table) {}

IdentifierNode::~IdentifierNode() {}

void IdentifierNode::DeclareVariable() {
    this->table->AddEntry(this->label);
}

void IdentifierNode::SetValue(int v) {
    this->table->SetValue(this->label, v);
}

int IdentifierNode::GetIndex() {
    return this->table->GetIndex(this->label);
}

int IdentifierNode::Evaluate() {
    return this->table->GetValue(this->label);
}

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushVariable(this->GetIndex());
}