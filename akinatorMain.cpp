#include <stdio.h>
#include <assert.h>

#include "akinatorTree.h"
#include "akinatorStack.h"
#include "akinatorFunctions.h"

int main(void)
{
    FILE* akinatorDataFile = fopen(nameFile, "r");
    Node* mainNode = startReadingAkinatorData(nameFile);
    dump(mainNode);
    FCLOSE(akinatorDataFile);
    run(mainNode);
    rewriteTree(mainNode, nameFile);
    dtorTree(mainNode);
     
    return 0;
}

