#include <iostream>
#include "keyword.h"

IfStatementNode::IfStatementNode(ExpressionNode *en, BlockNode *bn)
    : expNode(en), blockNode(bn) {}
IfStatementNode::~IfStatementNode()
{
    delete this->expNode;
    delete this->blockNode;
}
void IfStatementNode::Interpret()
{
    if (this->expNode->Evaluate())
    {
        this->blockNode->Interpret();
    }
}
void IfStatementNode::Code(InstructionsClass &machineCode)
{
    this->expNode->CodeEvaluate(machineCode);
    unsigned char *InsertAddress = machineCode.SkipIfZeroStack();
    unsigned char *address1 = machineCode.GetAddress();
    this->blockNode->Code(machineCode);
    unsigned char *address2 = machineCode.GetAddress();
    machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
}


WhileStatementNode::WhileStatementNode(ExpressionNode* en, BlockNode* bn)
    : expNode(en), blockNode(bn) {}
WhileStatementNode::~WhileStatementNode() {
    delete this->expNode;
    delete this->blockNode;
}
void WhileStatementNode::Interpret() {
    while (this->expNode->Evaluate()) {
        this->blockNode->Interpret();
    }
}
void WhileStatementNode::Code(InstructionsClass& machineCode) {
    unsigned char* address1 = machineCode.GetAddress();
    this->expNode->CodeEvaluate(machineCode);
    unsigned char* insertAddressSkip = machineCode.SkipIfZeroStack();
    unsigned char* address2 = machineCode.GetAddress();
    this->blockNode->Code(machineCode);
    unsigned char* insertAddressJump = machineCode.Jump();
    unsigned char* address3 = machineCode.GetAddress();
    machineCode.SetOffset(insertAddressSkip, (int)(address3 - address2));
    machineCode.SetOffset(insertAddressJump, (int)(address1 - address3));
}


ForStatementNode::ForStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn)
    : initializer(initializer),
    comparison(comparison),
    incrementer(incrementer),
    blockNode(bn) {}
ForStatementNode::~ForStatementNode() {
    delete this->initializer;
    delete this->comparison;
    delete this->incrementer;
    delete this->blockNode;
}
void ForStatementNode::Interpret() {
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        this->blockNode->Interpret();
        this->incrementer->Interpret();
    }
}
void ForStatementNode::Code(InstructionsClass& machineCode) {
    // FIX:
}

ForeStatementNode::ForeStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn)
    : ForStatementNode(initializer, comparison, incrementer, blockNode) {}
void ForeStatementNode::Interpret() {
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        for (int i = 0; i < 4; i++) {
            this->blockNode->Interpret();
        }
        this->incrementer->Interpret();
    }
}
void ForeStatementNode::Code(InstructionsClass& machineCode) {

}


CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode*> ens)
    : expNodes(ens) {}
CoutStatementNode::~CoutStatementNode() {
    for (auto e : this->expNodes) {
        delete e;
    }
}
void CoutStatementNode::Interpret() {
    for (auto e : this->expNodes) {
        if (e == NULL) {
            std::cout << std::endl;
        } else {
            std::cout << e->Evaluate();
        }
    }
}
void CoutStatementNode::Code(InstructionsClass& machineCode) {
    for (auto e : this->expNodes) {
        if (e == NULL) {
            machineCode.WriteEndl();
        } else {
            e->CodeEvaluate(machineCode);
            machineCode.PopAndWrite();
        }
    }
}

CinStatementNode::CinStatementNode(std::vector<IdentifierNode*> vars)
    : variables(vars) {}
CinStatementNode::~CinStatementNode() {
    for (auto e : this->variables) {
        delete e;
    }
}
void CinStatementNode::Interpret() {
    for (auto e : this->variables) {
        int var;
        std::cout << ">> ";
        std::cin >> var;
        e->SetValue(var);
    }
}
void CinStatementNode::Code(InstructionsClass& machineCode) {
    for (auto e : this->variables) {
        machineCode.ReadAndStoreVariable(e->GetIndex());
    }
}
