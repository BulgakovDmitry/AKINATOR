#ifndef AKINATORFUNCTIONS_H
#define AKINATORFUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>

#include "akinatorTree.h"
#include "akinatorStack.h"

#define SUCCESS \
    printf("\n%s!!!%s_________%sTHE PROGRAM FINISHED WITHOUT SIGFAULT%s_________%s!!!%s\n", RED, YELLOW, GREEN, YELLOW, RED, RESET);

#define FREE(ptr_) \
    do{free(ptr_)  ; ptr_ = NULL;} while(false)

#define FCLOSE(ptr_) \
    do{fclose(ptr_); ptr_ = NULL;} while(false)    

#define POINT(num_) \
    printf("%s%d%s) %s", GREEN, (int)num_, BLUE, RESET);

struct WayOfNode
{
    Stack* stk;
    Node* defNode;
};


enum Options
{
    OPTION_AKINATOR_START   = 'a',
    OPTION_GET_DEFINITION   = 'd',
    OPTION_SHOW_DUMP_TREE   = 's',
    OPTION_EXIT_OF_AKINATOR = 'e',
    OPTION_COMPARE          = 'c',
};



void run(Node* mainNode);
void runPrint();
void akinator(Node* node);
void definition(Node* node);
WayOfNode* getWayOfNode(Node* node);
void compareDifinition(Node* node);
Node* searchNode(Node* node, nodeData_t nodeData); 
void fillStack(Node* mainnode, Node* defNode, Stack* stk);
void clearBuffer();
bool checkYesAnswer(nodeData_t answer);
bool checkNoAnswer(nodeData_t answer);



Node* startReadingAkinatorData(const char* const nameFile);
int readAkinatorData(FILE* file, Node* prev_node, size_t sizeFile);

void rewriteTree(Node* node, const char* const nameFile);
void writeNodeToFile(Node* node, FILE* file, size_t numberOfTabs);

size_t getSizeOfFile(FILE* file, const char* const nameFile);

#endif