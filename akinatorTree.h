#ifndef AKINATORTREE_H
#define AKINATORTREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "color_list.h"

typedef char* nodeData_t;

#define FREE(ptr_) \
    do{free(ptr_)  ; ptr_ = NULL;} while(false)

#define FCLOSE(ptr_) \
    do{fclose(ptr_); ptr_ = NULL;} while(false) 

struct Node
{
    Node* right;
    Node* left; 
    Node* parent;
    nodeData_t data;
};

enum ConnectionTypes
{
    CONNECT_LEFT   = 1,
    CONNECT_RIGHT  = 2,
    CONNECT_PARENT = 3,
};

const char* const colArr[5] = {"\033[1;31m", "\033[1;32m", "\033[1;35m", "\033[1;34m", "\033[0m"};
const int NCOLORS   = 3;
const int MINCOLOR  = 0;
const int STEPCOLOR = 1;
const int DATASIZE = 55;
const char* const nameFile = "dataFile.txt";



Node* createAndWriteNode(const char* value); //
Node* createNode();                          //

void dtorTree(Node* node);                  //
void deleteNode(Node* node);                //

void connectNode(Node* port, Node* cable, ConnectionTypes type); //
void connectLeft  (Node* port, Node* cable);                     //
void connectRight (Node* port, Node* cable);                     //
void connectParent(Node* port, Node* cable);                     //

void insertAndFillNode(Node* oldNode);                           //
Node* insertAndName();                                           //

void dump(Node* node);                                 //
void dumpListNodes(Node* node, FILE* dumpFile);        //
void dumpConnectNodes(Node* node, FILE* dumpFile);     //

void dumpPrint(Node* node);               //
void print(Node* node, int colorCounter); //
void printDebug(int ind);                 //

#endif