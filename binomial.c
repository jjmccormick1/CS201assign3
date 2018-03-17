#include "dll.h"
#include "binomial.h"

BINNODE * newBINNODE( BINOMIAL*,void *);

struct binomial {
    DLL * roots;
    int size;
    NODE * extreme;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*swapper)(void *, void *);
    void (*free)(void *);
};
typedef struct binnode {
    void * value;
    int freq;
    BINNODE * parent;
    DLL * children;
}BINNODE;

BINOMIAL *newBINOMIAL(void (*display)(void *,FILE *),int (*compare)(void *,void *),void (*swapper)(void *,void *),void (*free)(void *))
{
    BINOMIAL * bin = malloc(sizeof(BINOMIAL));
    bin->roots = newDLL(display, free);
    bin->size =0;
    bin->extreme = NULL;
    bin->display = display;
    bin->compare = compare;
    bin->swapper = swapper;
    bin->free = free;
    
}
BINNODE * newBINNODE(BINOMIAL * b,void * value)
{
        BINNODE * node = malloc(sizeof(BINNODE));
        node->value = value;
        node->parent = node;
        node->freq = 1;
        node->children = newDLL(b->display, b->free);
}

void *insertBINOMIAL(BINOMIAL * b,void * value)
{
    BINNODE newNode = newBINNODE(b, value);
    insertDLL(b->roots, newNode);
    b->size++;
    //Cnsolodate
    return newNode;
}

int sizeBINOMIAL(BINOMIAL *b)
{
    return b->size;
}

void unionBINOMIAL(BINOMIAL * b,BINOMIAL * donor)
{
    unionDLL(b->roots , donor->roots);
    b->size += donor->size;
    donor->roots = newDLL(NULL, NULL);
    donor->size = 0;
    donor->extreme = NULL;
    //consolodate root list using comparator
}

void deleteBINOMIAL(BINOMIAL *b,void *node)
{
    
}

void bubbleUp(BINOMIAL * b, BINNODE * n)
{
    
}
void decreaseKeyBINOMIAL(BINOMIAL *b,void *node,void *value)
{
    
}
    extern void *peekBINOMIAL(BINOMIAL *b);
    extern void *extractBINOMIAL(BINOMIAL *b);
    extern void statisticsBINOMIAL(BINOMIAL *b,FILE *fp);
    extern void displayBINOMIAL(BINOMIAL *b,FILE *fp);
    extern void displayBINOMIALdebug(BINOMIAL *b,FILE *fp);
    extern void freeBINOMIAL(BINOMIAL *b); 
