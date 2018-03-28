#include "dll.h"
#include "binomial.h"
#include "queue.h"
#include <stdlib.h>
#include <math.h>

struct binnode {
    void * value;
    int freq;
    BINNODE * parent;
    DLL * children;
};

BINNODE * newBINNODE( BINOMIAL*,void *);
void bubbleUp(BINOMIAL *, BINNODE *);
void updateConsolidationArray(BINOMIAL *,BINNODE * arr[], BINNODE * spot);
void combine(BINOMIAL * b, BINNODE * x, BINNODE * y);
void displayDebugRecurse(BINNODE * node);

struct binomial {
    DLL * roots;
    int size;
    BINNODE * extreme;
    void (*display)(void *, FILE *);
    int (*compare)(void *, void *);
    void (*swapper)(void *, void *);
    void (*free)(void *);
};



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
    BINNODE * newNode = newBINNODE(b, value);
    insertDLL(b->roots,0, newNode);
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

void deleteBINOMIAL(BINOMIAL *b,void * node)
{
    decreaseKeyBINOMIAL(b, node, NULL);
    extractBINOMIAL(b);
}

void bubbleUp(BINOMIAL * b, BINNODE * n)
{
    if(getDLL(b->roots, n) != NULL)
        return n;
    else if(b->compare(n->value , (n->parent)->value) > 0 )
        return n;
    else
    {
        n->parent = (n->parent)->parent;
        n->parent = n;
        b->swapper(n->value, (n->parent)->value);
        return bubbleUp(b, n->parent);
    }
}
void decreaseKeyBINOMIAL(BINOMIAL *b,BINNODE * node,void *value)
{
    node->value = value;
    bubbleUp(b, node);
    int cmp = b->compare((b->extreme)->value, value)
    if(cmp < 0)
        b->extreme = node;
}
void *peekBINOMIAL(BINOMIAL *b)
{
    return (b->extreme)->value;
}
void *extractBINOMIAL(BINOMIAL *b)
{
    BINNODE * extremeNode = b->extreme;
    removeDLL
}
void consolidate(BINOMIAL * b)
{
    int arrsize = log2(sizeBINOMIAL(b)) + 1;
    BINNODE * array[arrsize];
    for(int i = 0; i < arrsize; i++)
    {
        array[i] = NULL;
    }
    
    while(sizeDLL(b->roots) > 0)
    {
        BINNODE * spot = removeDLL(b->roots,0);
        updateConsolidationArray(b, array, spot);
    }
    
    b->extreme = NULL;
    for(int i = 0; i < arrsize; i++)
    {
        if(array[i] != NULL)
        {
            insertDLL(b->roots, array[i], 0);
            if(b->extreme == NULL || b->compare(array[i]->value , b->extreme) > 0)
                b->extreme = array[i];
        }
    }
        
}
void updateConsolidationArray(BINOMIAL * b, BINNODE * arr[], BINNODE * spot)
{
    int degree = sizeDLL(spot->children);
    while(arr[degree] != NULL)
    {
        spot = combine(b, spot, arr[degree]);
        arr[degree] = NULL;
        degree++;
    }
    arr[degree] = spot;
}

void combine(BINOMIAL * b, BINNODE * x, BINNODE * y)
{
    if(b->compare(x->value , y->value) > 0)
    {
        insertDLL(x->children, y);
        y->parent = x;
        return x;
    }
    else
    {
        insertDLL(y->children,0, x);
        x->parent = y;
        return y;
    }
}
void statisticsBINOMIAL(BINOMIAL *b,FILE *fp)
{
    fprintf(fp, "size: %d\n", sizeBINOMIAL(b));
    fprintf(fp, "rootlist size: %d\n", sizeDLL(b->roots));
    if(b->extreme != NULL)
    {
        fprintf(fp, "extreme: ");
        b->display( (b->extreme)->value, fp);
    }
}
void displayBINOMIAL(BINOMIAL *b,FILE *fp)
{
    fprintf(fp, "rootlist: ");
    for(int i = 0; i < sizeDLL(b->roots) ; i++)
    {
        BINNODE * temp = getDLL(b->roots,i);
        b->display(temp->value,fp);
        fprintf(fp, " ");
    }
}
void displayBINOMIALdebug(BINOMIAL *b,FILE *fp)
{
    QUEUE * queue = newQUEUE(b->display, NULL);
    enqueue(queue, b->roots);
    
    while(sizeQUEUE(queue) > 0)
    {
        int level = sizeQUEUE(queue);
        while(level > 0)
        {
            DLL * outdll = dequeue(queue);
            
        }
    }
}
void displayDebugRecurse(BINNODE * node)
{
    
}
    extern void freeBINOMIAL(BINOMIAL *b); 
