#ifndef INSTRUCTIONS
#define INSTRUCTIONS 

const int MAX_INSTRUCTIONS = 5000;
const int MAX_DATA = 5000;

class InstructionsClass
{
public:
	// Helper functions for encoding machine instructions and integers into mCode:
	void Encode(int x);
	void Encode(unsigned char c);
	void Encode(long long x);
	void Encode(void * p);

	// Starting, ending, and executing mCode
	InstructionsClass(); // The constructor initializes the array of machine code to look like a function
	void Finish(); // Finalizes the array of machine code to look like a function
	void Execute(); // Causes the instruction pointer to jump into the array of machine code that behaves like a function
	void PrintAllMachineCodes(); // for debugging

	// Getting numbers on and off the stack, calling, and printing
	void PushValue(int value);  // used by IntegerNode
	void Call(void * function_address);
	void PopAndWrite(); // used by CoutStatementNode
	void WriteEndl();
	int * GetMem(int index); // index is 0 based.
	void PushVariable(unsigned int index); // used by IdentifierNode
	void PopAndStore(unsigned int index); // used by AssignmentStatementNode

	// Mathematical Operators
	void PopPopAddPush(); // Puts resulting integer on stack
	void PopPopSubPush(); 
	void PopPopMulPush(); 
	void PopPopDivPush(); 
	void PopPopShiftRightPush();

	// Relational Operators
	void PopPopComparePush(unsigned char relational_operator); 
		// common code for the relational operators
		// Puts 1 or 0 on stack.
	void PopPopLessPush(); 
	void PopPopLessEqualPush(); 
	void PopPopGreaterPush(); 
	void PopPopGreaterEqualPush(); 
	void PopPopEqualPush(); 
	void PopPopNotEqualPush(); 

	// Logical Operators
	void PopPopAndPush();
	void PopPopOrPush();

	// Jumping around based on the top of stack being 1 or 0.
	unsigned char * SkipIfZeroStack(); // skips some number of bytes forward, if the integer on the stack is zero.
							// The number of bytes to skip forward MUST be later set by calling SetOffset with the return value.
							// The number that was on the stack (1 or 0) gets popped as a side effect.
	unsigned char * GetAddress(); // returns the memory address where the next instruction will go.
	unsigned char * Jump(); // writes code to jump forward or backward some number of bytes.
							// The number of bytes to skip MUST be set later by calling SetOffset with the return value.
							
	void SetOffset(unsigned char * codeAddress, int offset); // After a jump offset becomes known, this method can be used to go back and set it.

	static int gPrintInteger;
private:

	static unsigned char mCode[MAX_INSTRUCTIONS]; // NOTE: Using an stl vector does not work, because they relocate their array sometimes.
	int mCurrent;
	int mData[MAX_DATA]; 
};

#endif

