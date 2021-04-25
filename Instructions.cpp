#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstdio>
using namespace std;
#include "Instructions.h"

#pragma warning(disable : 4311)

const unsigned char PUSH_EBP = 0x55;
const unsigned char MOV_EBP_ESP1 = 0x8B;
const unsigned char MOV_EBP_ESP2 = 0xEC;
const unsigned char POP_EBP = 0x5D;
const unsigned char NEAR_RET = 0xC3;		 // C3 hex, 195 decimal, 11000011 binary
const unsigned char IMMEDIATE_TO_EAX = 0xB8; // followed by 4 byte value.
const unsigned char PUSH_EAX = 0x50;
const unsigned char CALL = 0xE8; // call within segment, Add 4 byte offset in reverse order
const unsigned char POP_EAX = 0x58;
const unsigned char EAX_TO_MEM = 0xA3; // A3 hex, Add 4 (or 8) byte address value in reverse order
const unsigned char MEM_TO_EAX = 0xA1; // A1 hex, Add 4 (or 8) byte address value in reverse order

const unsigned char POP_EBX = 0x5B;
const unsigned char ADD_EAX_EBX1 = 0x03;
const unsigned char ADD_EAX_EBX2 = 0xC3;
const unsigned char SUB_EAX_EBX1 = 0x2B;
const unsigned char SUB_EAX_EBX2 = 0xC3;
const unsigned char MUL_EAX_EBX1 = 0xF7;
const unsigned char MUL_EAX_EBX2 = 0xEB;
const unsigned char DIV_EAX_EBX1 = 0xF7;
const unsigned char DIV_EAX_EBX2 = 0xFB;
const unsigned char CDQ = 0x99;
const unsigned char CMP_EAX_EBX1 = 0x3B; // compares A and B registers.
const unsigned char CMP_EAX_EBX2 = 0xC3;
const unsigned char JUMP_ALWAYS = 0xEB;
const unsigned char JL = 0x7C;
const unsigned char JLE = 0x7E;
const unsigned char JG = 0x7F;
const unsigned char JGE = 0x7D;
const unsigned char JE = 0x74;
const unsigned char JNE = 0x75;

//const unsigned char JE_WORD = 0x84; // 2 byte jump does NOT work!
const unsigned char JE_FAR1 = 0x0f;			// 4 byte jump
const unsigned char JE_FAR2 = 0x84;			// 4 byte jump
const unsigned char JUMP_ALWAYS_FAR = 0xE9; // 4 byte jump (NOT 2 byte!)

// Initialize static class variables
unsigned char InstructionsClass::mCode[MAX_INSTRUCTIONS] = {0};

// A location to store an integer that is about to be printed.
int InstructionsClass::gPrintInteger = 0;
int InstructionsClass::gReadInteger = 0;

void HelperPrintInteger(void);

void InstructionsClass::Encode(unsigned char c)
{
	if (mCurrent < MAX_INSTRUCTIONS)
		mCode[mCurrent++] = c;
	else
	{
		cerr << "Error. Used up all " << MAX_INSTRUCTIONS << " instructions." << endl;
		exit(1);
	}
}

void InstructionsClass::Encode(int x)
{
	*((int *)(&(mCode[mCurrent]))) = x;
	mCurrent += 4;
}

void InstructionsClass::Encode(long long x)
{
	*((long long *)(&(mCode[mCurrent]))) = x;
	mCurrent += 8;
}

void InstructionsClass::Encode(void *p)
{
	int pointerSize = sizeof(p);

	if (pointerSize == 4)
	{
		Encode((int)(long long)p);
	}
	else if (sizeof(p) == 8)
	{
		Encode((long long)p);
	}
	else
	{
		assert(false);
	}
}

InstructionsClass::InstructionsClass()
{
	void *p = NULL;
	int pointerSize = sizeof(p);
	if (pointerSize == 4)
	{
		cout << "Compiling for 32 bit" << endl;
	}
	else if (sizeof(p) == 8)
	{
		cout << "Compiling for 64 bit" << endl;
	}
	mCurrent = 0;
	Encode(PUSH_EBP);
	Encode(MOV_EBP_ESP1);
	Encode(MOV_EBP_ESP2);
}

void InstructionsClass::Finish()
{
	Encode(POP_EBP);
	Encode(NEAR_RET);
	cout << "Finished creating " << mCurrent << " bytes of machine code" << endl;
}

void InstructionsClass::Execute()
{
	cout << "About to Execute the machine code..." << endl;
	void *ptr = InstructionsClass::mCode;
	void (*f)(void);
	f = (void (*)(void))ptr;
	f();
	cout << "\nThere and back again!" << endl
		 << endl;
}

void InstructionsClass::PrintAllMachineCodes()
{
	for (int i = 0; i < mCurrent; i++)
	{
		printf("HEX: %2x  Decimal: %3i\n", (int)InstructionsClass::mCode[i], (int)InstructionsClass::mCode[i]);
	}
}

void InstructionsClass::PushValue(int value)
{
	Encode(IMMEDIATE_TO_EAX);
	Encode(value);
	Encode(PUSH_EAX);
}

void InstructionsClass::Call(void *function_address)
{
	unsigned char *a1 = (unsigned char *)function_address;
	unsigned char *a2 = (unsigned char *)(&InstructionsClass::mCode[mCurrent + 5]);
	int offset = (int)(a1 - a2);
	Encode(CALL);
	Encode(offset);
}

// prints the integer value at location gPrintInteger
// This is called by the generated machine language code.
void HelperPrintInteger(void)
{
	// printf("%i ", InstructionsClass::gPrintInteger);
	cout << InstructionsClass::gPrintInteger;
}

void InstructionsClass::PopAndWrite()
{
	Encode(POP_EAX);
	Encode(EAX_TO_MEM);
	Encode(&gPrintInteger);
	Call((void *)HelperPrintInteger);
}

// returns the address corresponding to variable <index>
// in the mData array.
int *InstructionsClass::GetMem(int index)
{
	if (index >= MAX_DATA)
	{
		cerr << "Error in GetMem. index is " << index << ", but NUM_DATA is only " << MAX_DATA << endl;
		exit(1);
	}
	return &(mData[index]);
}

void InstructionsClass::PushVariable(unsigned int index)
{
	int *variable_address = GetMem(index);
	Encode(MEM_TO_EAX);
	Encode(variable_address);
	Encode(PUSH_EAX);
}

void InstructionsClass::PopAndStore(unsigned int index)
{
	int *variable_address = GetMem(index);
	Encode(POP_EAX);
	Encode(EAX_TO_MEM);
	Encode(variable_address);
}

// prints a carriage return
// This is called by the generated machine language code.
void HelperPrintEndl(void)
{
	cout << endl;
}
void InstructionsClass::WriteEndl()
{
	Call((void *)HelperPrintEndl);
}

void InstructionsClass::PopPopAddPush()
{
	Encode(POP_EBX);
	Encode(POP_EAX);
	Encode(ADD_EAX_EBX1);
	Encode(ADD_EAX_EBX2);
	Encode(PUSH_EAX);
}

void InstructionsClass::PopPopSubPush()
{
	Encode(POP_EBX);
	Encode(POP_EAX);
	Encode(SUB_EAX_EBX1);
	Encode(SUB_EAX_EBX2);
	Encode(PUSH_EAX);
}

void InstructionsClass::PopPopMulPush()
{
	Encode(POP_EBX);
	Encode(POP_EAX);
	Encode(MUL_EAX_EBX1);
	Encode(MUL_EAX_EBX2);
	Encode(PUSH_EAX);
}

void InstructionsClass::PopPopDivPush()
{
	Encode(POP_EBX);
	Encode(POP_EAX);
	Encode(CDQ); // Necessary to clear the D register for a 64 bit divide.
	Encode(DIV_EAX_EBX1);
	Encode(DIV_EAX_EBX2);
	Encode(PUSH_EAX);
}

void InstructionsClass::PopPopComparePush(unsigned char relational_operator)
{
	Encode(POP_EBX);
	Encode(POP_EAX);
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(IMMEDIATE_TO_EAX); // load A register with 1
	Encode(1);
	Encode(relational_operator); // Possibly skip setting A register to zero, leaving it at 1.
	Encode((unsigned char)5);
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	Encode(PUSH_EAX); // push 1 or 0
}

void InstructionsClass::PopPopLessPush()
{
	PopPopComparePush(JL);
}

void InstructionsClass::PopPopLessEqualPush()
{
	PopPopComparePush(JLE);
}

void InstructionsClass::PopPopGreaterPush()
{
	PopPopComparePush(JG);
}

void InstructionsClass::PopPopGreaterEqualPush()
{
	PopPopComparePush(JGE);
}

void InstructionsClass::PopPopEqualPush()
{
	PopPopComparePush(JE);
}

void InstructionsClass::PopPopNotEqualPush()
{
	PopPopComparePush(JNE);
}

void InstructionsClass::PopPopAndPush()
{
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	Encode(POP_EBX); // load B register with stack item 2
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(POP_EBX); // load B register with stack item 1 (does not affect flags)
	Encode(JE);		 // if stack item 2 is zero, jump to FALSE code
	Encode((unsigned char)11);
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(JE); // if stack item 1 is zero, jump to FALSE code
	Encode((unsigned char)7);
	// TRUE code:
	Encode(IMMEDIATE_TO_EAX); // load A register with 1
	Encode(1);
	Encode(JUMP_ALWAYS); // Jump around FALSE code
	Encode((unsigned char)5);
	// FALSE code:
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	// Save A to the stack
	Encode(PUSH_EAX); // push 1 or 0
}

void HelperReadInteger(void)
{
	cout << ">> ";
	cin >> InstructionsClass::gReadInteger;
}

void InstructionsClass::ReadAndStoreVariable(unsigned int index)
{
	int *variable_address = GetMem(index);

	// Read in integer
	Call((void *)HelperReadInteger);
	// Push on stack
	Encode(MEM_TO_EAX);
	Encode(&gReadInteger);
	Encode(PUSH_EAX);

	// Store
	Encode(POP_EAX);
	Encode(EAX_TO_MEM);
	Encode(variable_address);
}

void InstructionsClass::PopPopOrPush()
{
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	Encode(POP_EBX); // load B register with stack item 2
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(POP_EBX); // load B register with stack item 1 (does not affect flags)
	Encode(JNE);	 // if stack item 2 is not zero, jump to TRUE code
	Encode((unsigned char)11);
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(JNE); // if stack item 1 is not zero, jump to TRUE code
	Encode((unsigned char)7);
	// FALSE code:
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	Encode(JUMP_ALWAYS); // Jump around TRUE code
	Encode((unsigned char)5);
	// TRUE code:
	Encode(IMMEDIATE_TO_EAX); // load A register with 1
	Encode(1);
	// Save A to the stack
	Encode(PUSH_EAX); // push 1 or 0
}

unsigned char *InstructionsClass::SkipIfZeroStack()
{
	Encode(POP_EBX);
	Encode(IMMEDIATE_TO_EAX); // load A register with 0
	Encode(0);
	Encode(CMP_EAX_EBX1);
	Encode(CMP_EAX_EBX2);
	Encode(JE_FAR1); // If stack had zero, skip given number of bytes
	Encode(JE_FAR2);
	unsigned char *addressToFillInLater = GetAddress();
	Encode(0); // the exact number of bytes to skip gets set later,
			   // when we know it!  Call SetOffset() to do that.
	return addressToFillInLater;
}

void InstructionsClass::SetOffset(unsigned char *codeAddress, int offset)
{
	*((int *)codeAddress) = offset;
}

unsigned char *InstructionsClass::GetAddress()
{
	return &(InstructionsClass::mCode[mCurrent]);
}

unsigned char *InstructionsClass::Jump()
{
	Encode(JUMP_ALWAYS_FAR);
	unsigned char *addressToFillInLater = GetAddress();
	Encode(0); // the exact number of bytes to jump gets set later,
			   // when we know it!  Call SetOffset() to do that.
	return addressToFillInLater;
}
