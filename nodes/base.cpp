#include "base.h"
#include "../Symbol.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* pn)
    : programNode(pn) {}
StartNode::~StartNode() {
    delete this->programNode;
}
void StartNode::Code(InstructionsClass& machineCode) {
    this->programNode->Code(machineCode);
}
void StartNode::Interpret() {
    this->programNode->Interpret();
}

ProgramNode::ProgramNode(BlockNode* bn)
    : blockNode(bn) {}
ProgramNode::~ProgramNode() {
    delete this->blockNode;
}
void ProgramNode::Code(InstructionsClass& machineCode) {
    this->blockNode->Code(machineCode);
}
void ProgramNode::Interpret() {
    this->blockNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* sgn)
    : sgNode(sgn) {}
BlockNode::~BlockNode() {
    delete this->sgNode;
}
void BlockNode::Code(InstructionsClass& machineCode) {
    this->sgNode->Code(machineCode);
}
void BlockNode::Interpret() {
    this->sgNode->Interpret();
}

StatementGroupNode::StatementGroupNode()
    : nodes(std::vector<StatementNode*>{}) {}
StatementGroupNode::~StatementGroupNode() {
    for (auto n : this->nodes) {
        delete n;
    }
}
void StatementGroupNode::Code(InstructionsClass& machineCode) {
    for (auto n : this->nodes) {
        n->Code(machineCode);
    }
}
void StatementGroupNode::Interpret() {
    for (auto n : this->nodes) {
        n->Interpret();
    }
}
void StatementGroupNode::AddStatement(StatementNode* node) {
    this->nodes.push_back(node);
}