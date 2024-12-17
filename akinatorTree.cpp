#include "akinatorTree.h"

Node* createAndWriteNode(const char* value)
{
    assert(value);
    Node* node = createNode();
    node->data = strdup(value);
    return node;
}

Node* createNode()
{
    Node* node = (Node*)     calloc(1,        sizeof(Node));
    assert(node);

    node->data = (nodeData_t)calloc(DATASIZE, sizeof(char));  
    assert(node->data);

    node->left  = NULL;
    node->right = NULL;

    return node;
}

void deleteNode(Node* node)  
{
    if (!node) {
        printf(RED "The node is not deleted\n" RESET); 
        return;
    }
    if (node->data) FREE(node->data);
    FREE(node);
}

void dtorTree(Node* node)
{
    assert(node);

    if (node->left)  dtorTree(node->left) ;
    if (node->right) dtorTree(node->right);
    deleteNode(node);
}

void connectNode(Node* port, Node* cable, ConnectionTypes type)
{
    if      (type == CONNECT_RIGHT  && port->right  == NULL) {port->right  = cable;}
    else if (type == CONNECT_LEFT   && port->left   == NULL) {port->left   = cable;}
    else if (type == CONNECT_PARENT && port->parent == NULL) {port->parent = cable;}
    else    {printf("%s__connectNode__ERROR!___%s\n", RED, RESET);} 
}

void connectRight(Node* port, Node* cable)
{
    if (!port->right)
        port->right = cable;
    else    
        printf("%s__connectNode__ERROR!___%s\n", RED, RESET);  
}

void connectLeft(Node* port, Node* cable)
{
    if (!port->left)
        port->left = cable;
    else    
        printf("%s__connectNode__ERROR!___%s\n", RED, RESET);  
}

void connectParent(Node* port, Node* cable)
{
    if (!port->parent)
        port->parent = cable;
    else    
        printf("%s__connectNode__ERROR!___%s\n", RED, RESET);  
}

void dumpPrint(Node* node)
{
    int colorCounter = 0;
    print(node, colorCounter);
    putchar('\n');
}

Node* insertAndName()
{
    nodeData_t nodeData = (nodeData_t)calloc(DATASIZE, sizeof(char));   
    assert(nodeData);                                                 
    scanf("%s", nodeData);  
    Node* node = createAndWriteNode(nodeData);              
    assert(node);                  
    return node;
}

void insertAndFillNode(Node* oldNode)
{
    assert(oldNode);
    
    printf("%sEnter your answer of new node: %s", GREEN, RESET);    
    Node* falseAnswerNode = insertAndName(); 
    assert(falseAnswerNode);                

    printf("%sEnter the question of new node: %s", GREEN, RESET);                                                 
    Node* questionNode = insertAndName();
    assert(questionNode);

    Node* trueAnswerNode = createAndWriteNode(oldNode->data);
    assert(trueAnswerNode);

    if (oldNode->parent->right == oldNode)  
        oldNode->parent->right = questionNode;
    else if (oldNode->parent->left == oldNode) 
        oldNode->parent->left = questionNode;
    else
        printf("%sERROR IN FUNCTION INSERT%s\n", RED, RESET);

    questionNode->parent = oldNode->parent;
    questionNode->right = trueAnswerNode;
    questionNode->left = falseAnswerNode;

    trueAnswerNode->parent = questionNode;
    trueAnswerNode->left = NULL;
    trueAnswerNode->right = NULL;

    falseAnswerNode->parent = questionNode;
    falseAnswerNode->left = NULL;
    falseAnswerNode->right = NULL;
}

void print(Node* node, int colorCounter)
{
    assert(node);

    if (colorCounter > NCOLORS) 
        colorCounter = MINCOLOR;

    if (!node) return;

    printf("%s (%s ", colArr[colorCounter], colArr[4]);
    printf("%s%s%s", WHITE, node->data, RESET);

    if (node->left)  
        print(node->left,  colorCounter + STEPCOLOR);

    if (node->right)   
        print(node->right, colorCounter + STEPCOLOR); 

    if (colorCounter < MINCOLOR) 
        colorCounter = NCOLORS;

    printf("%s )%s", colArr[colorCounter], RESET);
}

void printDebug(int ind)
{
    printf("%s!!!%s_________%sTHIS IS OK%s_________%s!!!%s (%s%d%s) %s\n", RED, YELLOW, GREEN, YELLOW, RED, MANG, YELLOW, ind,  MANG, RESET);
}

void dumpListNodes(Node* node, FILE* dumpFile)
{
    assert(dumpFile);

    if(!node) return;

    fprintf(dumpFile, "    node_%p [shape=record, color=olivedrab4, label=\" {addr: %llX | data: %s | {left: %llX | right: %llX}} \"];\n",
                                     node,  (size_t)node, node->data,   (size_t)node->left,   (size_t)node->right);

    if (node->left)  dumpListNodes(node->left, dumpFile);
    if (node->right) dumpListNodes(node->right, dumpFile);
}

void dumpConnectNodes(Node* node, FILE* dumpFile)
{
    assert(dumpFile);
    if (!node) return;

    static int flag = 0;

    if (node->left)
    {
        fprintf(dumpFile, "    node_%p -> node_%p ", node, node->left);
        dumpConnectNodes(node->left, dumpFile);
    }

    if (node->right)
    {
        fprintf(dumpFile, "    node_%p -> node_%p", node, node->right);
        dumpConnectNodes(node->right, dumpFile);
    }

    if (flag) {fprintf(dumpFile, ";"), flag++;}
}

void dump(Node* node)   
{
    assert(node);
    const char* dumpFileName = "dumpFile.gv";
    FILE* dumpFile = fopen(dumpFileName, "wb");
    assert(dumpFile);

    fprintf(dumpFile, "digraph\n");
    fprintf(dumpFile, "{\n    ");
    fprintf(dumpFile, "node [ style = filled, fontcolor=darkblue, fillcolor=peachpuff, color=\"#252A34\", penwidth = 2.5 ];\n    "); //'RGB: #40e0d0', style='filled', fillcolor='#40e0d0'
    fprintf(dumpFile, "bgcolor = \"lemonchiffon\";\n\n"); 

    dumpListNodes(node, dumpFile);
    dumpConnectNodes(node, dumpFile);

    fprintf(dumpFile, "\n}\n");

    FCLOSE(dumpFile);
    system("dot dumpFile.gv -Tpng -o graphDump.png");
}


