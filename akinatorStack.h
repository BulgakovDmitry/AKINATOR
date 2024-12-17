#ifndef AKINATORSTACK_H
#define AKINATORSTACK_H

#include "akinatorTree.h"

struct Stack
{
    size_t size, capasity;
    Node** data;
};

const int STARTCAPASITY = 50;

Stack* stackCtor();
void stackDtor(Stack* stk);
void stackPush(Stack* stk, Node* value);
Node* stackPop(Stack* stk);
void stackDump(Stack* stk);
Node* stackGet(Stack* stk);

#endif