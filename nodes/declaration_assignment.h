#if !defined(DECLARATION_ASSIGNMENT_H)
#define DECLARATION_ASSIGNMENT_H

#include "base.h"
#include "value.h"


class DeclarationStatementNode;
class DeclarationAssignmentStatementNode;
class AssignmentStatementNode;

class PlusEqualsStatementNode;
class MinusEqualsStatementNode;
class MultiplyEqualsStatementNode;
class DivideEqualsStatementNode;

class IncrementStatementNode;
class DecrementStatementNode;

class DeclarationStatementNode : public StatementNode {
protected:
    IdentifierNode* IDNode;
public:
    DeclarationStatementNode(IdentifierNode* in);
    ~DeclarationStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class DeclarationAssignmentStatementNode : public DeclarationStatementNode {
private:
    ExpressionNode* expNode;
public:
    DeclarationAssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~DeclarationAssignmentStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class AssignmentStatementNode : public StatementNode {
protected:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~AssignmentStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class PlusEqualsStatementNode : public AssignmentStatementNode {
private:

public:
    PlusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class MinusEqualsStatementNode : public AssignmentStatementNode {
private:

public:
    MinusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class MultiplyEqualsStatementNode : public AssignmentStatementNode {
private:

public:
    MultiplyEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class DivideEqualsStatementNode : public AssignmentStatementNode {
private:

public:
    DivideEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class IncrementStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    IncrementStatementNode(IdentifierNode* in);
    ~IncrementStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class DecrementStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    DecrementStatementNode(IdentifierNode* in);
    ~DecrementStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

#endif // DECLARATION_ASSIGNMENT_H
