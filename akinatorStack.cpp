#include "akinatorStack.h"

Stack* stackCtor()
{
    Stack* stk = (Stack*)calloc(1, sizeof(Stack));
    assert(stk);
    stk->data = (Node**)calloc(STARTCAPASITY, sizeof(Node*));
    assert(stk->data);
    stk->size = 0;
    stk->capasity = STARTCAPASITY;
    return stk;
}

void stackDtor(Stack* stk)
{
    assert(stk);
    for (int i = 0; i < (int)stk->capasity; i++) stk->data[i] = NULL;
    FREE(stk->data);
    stk->size = 0;
    stk->capasity = 0;
    FREE(stk);
}

void stackDump(Stack* stk)
{
    assert(stk);
    for (int i = 0; i < (int)stk->capasity; i++)
        printf("%s[%s%d%s] %s%llX%s\n", BLUE, MANG, i, BLUE, GREEN, (size_t)stk->data[i], RESET);
}

void stackPush(Stack* stk, Node* value)
{
    assert(stk);
    assert(value);
    if (stk->size < stk->capasity)
    {
        stk->data[stk->size] = value;
        stk->size++;
    }
    else 
        printf("%s IT IS IMPOSSIBLE TO PUSH\n%s", RED, RESET);    
}

Node* stackPop(Stack* stk)
{
    assert(stk);
    if (stk->size == 0)
        return NULL;
    stk->size--;
    return stk->data[stk->size];   
}

Node* stackGet(Stack* stk)
{
    assert(stk);
    if (stk->size > 0)
        return stk->data[stk->size - 1];
    else    
    {
        printf("%sSTACK IS EMTY%s\n", RED, RESET);
        return NULL;
    }    
}