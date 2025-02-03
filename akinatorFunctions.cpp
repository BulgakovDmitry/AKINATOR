//#define TX_USE_SPEAK 
//#include <TXLib.h>
#include "akinatorFunctions.h"
void runPrint()
{
    
    printf(     "\n"
                    "%s(%sa%s)%s -%s to start Akinator\n" 
                    "%s(%sd%s)%s -%s to get difinition\n"
                    "%s(%ss%s)%s -%s to show tree dump\n"
                    "%s(%sc%s)%s -%s to compare difinition\n"
                    "%s(%se%s)%s -%s to exit\n"
                    "%schoose the mode%s: %s",
                    BLUE, MANG, BLUE, RED, GREEN, 
                    BLUE, MANG, BLUE, RED, GREEN, 
                    BLUE, MANG, BLUE, RED, GREEN, 
                    BLUE, MANG, BLUE, RED, GREEN,
                    BLUE, MANG, BLUE, RED, GREEN,
                    CEAN, RED, RESET
               );
}

void run(Node* mainNode)
{
    assert(mainNode);
    char ans = '\0';         
    while (ans != OPTION_EXIT_OF_AKINATOR)
    {                  
        runPrint();
        scanf("%c", &ans);
        clearBuffer();

        switch (ans)
        {
            case OPTION_AKINATOR_START:
            {
                akinator(mainNode);
                break;
            }
            case OPTION_GET_DEFINITION:
            {
                definition(mainNode);
                break;
            }
            case OPTION_SHOW_DUMP_TREE:
            {
                rewriteTree(mainNode, "dataFile.txt");
                dump(mainNode);
                printf("%s___THE TREE REWRITED AND DUMP MADE___%s\n", MANG, RESET);
                continue;
            }
            case OPTION_COMPARE:
            {
                compareDifinition(mainNode);
                break;
            }
            case OPTION_EXIT_OF_AKINATOR:
            {
                printf("%s___EXIT___%s\n", GREEN, RESET); 
                return;
            }
            default:
            {
                printf("%sincorrect entering, please try again%s\n", RED, RESET); 
                continue;
            }
        }

        clearBuffer();    
    }    
}



void compareDifinition(Node* node)
{
    POINT(1); WayOfNode* wn1 = getWayOfNode(node);
    POINT(2); WayOfNode* wn2 = getWayOfNode(node);
    assert(wn1);
    assert(wn2);
    assert(wn1->stk);
    assert(wn2->stk);
    assert(wn1->defNode);
    assert(wn2->defNode);

    if (wn1->defNode == wn2->defNode)
    {
        printf("%sBoth elements have similar difinition\n%s", MANG, RESET);
        return;
    }

    Stack* similar = stackCtor();
    assert(similar);
    Node* a = NULL;
    Node* b = NULL;
    assert(a);
    assert(b);

    int i = 0;
    while((wn1->stk->data[i] != node) && (wn2->stk->data[i] != node))
    {
        a = stackPop(wn1->stk);
        b = stackPop(wn2->stk);
        if (a == b) 
            stackPush(similar, a); // FIXME: dont recopy
        i++;
    }

    printf("%sThese definitions have similar nodes%s:%s", MANG, RED, RESET);
    if (similar->size != 0)
    {
        for (int i = 0; i < (int)similar->size - 1; i++) 
            printf("%s %s %s", GREEN, similar->data[i]->data, RESET);

    }
    putchar('\n');
    printf("%sThe first difference is in node%s     :%s %s%s\n", MANG, RED, GREEN, a->data, RESET);

    stackDtor(similar);
    FREE(a);
    FREE(b);
    stackDtor(wn1->stk);
    stackDtor(wn2->stk);
    wn1->defNode = NULL;
    wn2->defNode = NULL;
}

void clearBuffer()
{
    while (getchar() != '\n');
}

WayOfNode* getWayOfNode(Node* node)
{
    WayOfNode* wn = (WayOfNode*)calloc(1, sizeof(WayOfNode));
    assert(wn);

    wn->stk = stackCtor();
    assert(wn->stk);

    nodeData_t nodeData = (nodeData_t)calloc(DATASIZE, sizeof(char));
    assert(nodeData);

    printf("%sENTER THE YOUR ELEMENT TO GET DEFINITION%s: %s", MANG, RED, RESET);
    scanf("%s", nodeData);

    wn->defNode = searchNode(node, nodeData);
    assert(wn->defNode);
    if (!wn->defNode)
    {
        printf("%sTHIS ELEMENT IS NOT FIND%s\n", MANG, RESET);
        FREE(nodeData);
        stackDtor(wn->stk);
        return NULL;
    }

    assert(wn->defNode);
    fillStack(node, wn->defNode, wn->stk); 
    stackPush(wn->stk, node);

    FREE(nodeData);
    return wn;
}

void definition(Node* node)
{
    Stack* stk = stackCtor();
    assert(stk);

    nodeData_t nodeData = (nodeData_t)calloc(DATASIZE, sizeof(char));
    assert(nodeData);

    printf("%sENTER THE YOUR ELEMENT TO GET DEFINITION%s: %s", MANG, RED, RESET);
    scanf("%s", nodeData);

    Node* defNode = searchNode(node, nodeData);
    if (!defNode)
    {
        printf("%sTHIS ELEMENT IS NOT FIND%s\n", MANG, RESET);
        FREE(nodeData);
        stackDtor(stk);
        return;
    }

    assert(defNode);
    fillStack(node, defNode, stk);
    stackPush(stk, node);

    if (defNode == node)
    {
        printf(GREEN "%s\n" RESET, defNode->data);
        return;
    }

    size_t treeDepth = stk->size;

    for (size_t i = 0; i < treeDepth; i++) 
    {
        Node* addr = stackPop(stk);
        assert(addr);

        if (i != treeDepth - 1)
        {
            if (addr->right == stackGet(stk))
                printf("%sNO_%s", RED, RESET); 
        }
          
        printf("%s%s%s ", GREEN, addr->data, RESET);
        if (addr != defNode)
            printf("%s-> %s", BLUE, RESET);
        
    }

    putchar('\n');
    stackDtor(stk);
    defNode = NULL;
    FREE(nodeData);
}

void fillStack(Node* mainnode, Node* defNode, Stack* stk)
{
    assert(mainnode);
    assert(defNode);
    assert(stk);
    if (mainnode != defNode)
    {
        stackPush(stk, defNode);
        fillStack(mainnode, defNode->parent, stk);
    }
}

Node* searchNode(Node* node, nodeData_t nodeData)
{
    assert(node);
    assert(nodeData);
    
    static Node* rNode = NULL;

    if (strcmp(node->data, nodeData) != 0)
    {
        if (node->left)
            searchNode(node->left, nodeData);
        if (node->right)
            searchNode(node->right, nodeData); 
        if (node->right == NULL && node->left == NULL) 
            return rNode;
    }
    
    if (strcmp(node->data, nodeData) == 0)
    {
        rNode = node;
        return rNode;
    }

    return rNode;
}

void writeNodeToFile(Node* node, FILE* file, size_t numberOfTabs)
{
    assert(node);
    assert(file);
    
    for (size_t i = 0; i < numberOfTabs; i++) {fprintf(file, "\t");}
    fprintf(file, "\"%s\"\n", node->data);

    if (node->left)  
    {
        for (size_t i = 0; i < numberOfTabs; i++) {fprintf(file, "\t");} 
        fprintf(file, "{\n");
        writeNodeToFile(node->left,  file, numberOfTabs + 1); 
    }
    if (node->right) 
    {
        for (size_t i = 0; i < numberOfTabs; i++) {fprintf(file, "\t");} 
        fprintf(file, "{\n"); 
        writeNodeToFile(node->right, file, numberOfTabs + 1); 
    }

    for (size_t i = 0; i < numberOfTabs - 1; i++) {fprintf(file, "\t");} 
    fprintf(file, "}\n");    
}

void rewriteTree(Node* node, const char* const nameFile)
{
    assert(node);
    assert(nameFile);

    FILE* file = fopen(nameFile, "w");
    fprintf(file, "{\n");
    size_t numberOfTabs = 1;
    writeNodeToFile(node, file, numberOfTabs);

    FCLOSE(file);
}

Node* startReadingAkinatorData(const char* const nameFile) // NOTE: cringenaming
{       
    FILE* akinatorDataFile = fopen(nameFile, "r");
    assert(akinatorDataFile);

    size_t sizeFile = getSizeOfFile(akinatorDataFile, nameFile);
    nodeData_t buffer = (nodeData_t)calloc(sizeFile, sizeof(char));
    assert(buffer);

    fscanf(akinatorDataFile, "{ \"%[^\"]\"", buffer);
    Node* node = createAndWriteNode(buffer);
    FREE(buffer);

    readAkinatorData(akinatorDataFile, node, sizeFile);

    FCLOSE(akinatorDataFile);
    return node;
}

int readAkinatorData(FILE* file, Node* prevNode, size_t sizeFile)
{
    assert(file);

    nodeData_t buffer = (nodeData_t)calloc(sizeFile, sizeof(char));
    assert(buffer);

    int verifier = fscanf(file, "%s\n", buffer);
    if (verifier == EOF) {FREE(buffer); return 0;}

    if (strcmp(buffer, "{") == 0)
    {
        fscanf(file, "\"%[^\"]\"", buffer);
        Node* node = createAndWriteNode(buffer);
    
        if (prevNode->left == NULL) //NOTE: bad code
        {
            connectLeft  (prevNode, node);
            connectParent(node, prevNode);
        }
        else if (prevNode->right == NULL)
        {
            connectRight (prevNode, node);
            connectParent(node, prevNode);
        }
        else
        {
            printf("%sError in binary tree%s\n", RED, RESET);
            return 0;
        }

        readAkinatorData(file, node, sizeFile);
    }

    if (strcmp(buffer, "}") == 0) { // FIXME: govnocode 
        FREE(buffer);
        readAkinatorData(file, prevNode->parent, sizeFile);
    }


    return 0;
}

size_t getSizeOfFile(FILE* file, const char* const nameFile)
{
    assert(file);
    assert(nameFile);

    struct stat st;     
    stat(nameFile, &st);                                                                             
    size_t size = st.st_size;
    assert(size);

    return size;
}



bool checkYesAnswer(nodeData_t answer)
{
    assert(answer);
    if (strncmp(answer, "yes", 3) == 0)
        return true;
    else 
        return false;    
}

bool checkNoAnswer(nodeData_t answer)
{
    assert(answer);
    if (strncmp(answer, "no", 2) == 0)
        return true;
    else 
        return false;  
}

void akinator(Node* node)
{
    assert(node);

    nodeData_t answer = (nodeData_t)calloc(DATASIZE, sizeof(char));
    assert(answer);

    printf("%sIS IT%s %s %s?%s   (enter 'yes' or 'no') %sANSWER%s: %s", MANG, GREEN, node->data, MANG, BLUE, MANG, RED, RESET);
    scanf("%s", answer);
    
    if (checkYesAnswer(answer) && node->left) 
        akinator(node->left);
    else if (checkNoAnswer(answer) && node->right) 
        akinator(node->right);
    else
    {
        if (checkYesAnswer(answer)) 
        {
            printf("%sI FIND THE ELEMENT%s:%s %s%s\n", BLUE, RED, GREEN, node->data, RESET); 
            return;
        }
        else if (checkNoAnswer(answer)) 
        {
            printf("%sI DO NOT FIND, LETS WRITE IT%s\n", BLUE, RESET); 
            insertAndFillNode(node); 
            return;
        }
        else 
        {
            printf("%sINCORRECT INPUT, PLEASE, TRY AGAIN%s\n", RED, RESET); 
            akinator(node); 
            return;
        }
    }
    FREE(answer);
}


