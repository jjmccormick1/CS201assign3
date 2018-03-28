 
// Jeremy McCormick
// dll.c
// CS201 Assignment 0
#include <stdio.h>
#include "dll.h"
#include <assert.h>
#include <stdlib.h>

void circularFixup(DLL *);

struct dll
{
    NODE *head;
    NODE *tail;
    int size;
    NODE * iterator;
    void (*display)(void *,FILE *);
    void (*free)(void *);
};

//d is the display function
//f is the freeing function
DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
{
    DLL *items = malloc(sizeof(DLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->iterator = 0;
        items->display = d;
        items->free = f;
        return items;
}
void insertDLL(DLL *items,int index,void *value)
{
    NODE * newNode = newNODE(value,0);
    //setNODEnext(newNode,newNode); //set new now next to itself
    if(items->size == 0) //only node in so far
    {
        items->head = newNode;
        items->tail = newNode;
        items->size += 1;
        return;
    }
    if(index == 0) //insert at front
    {
        setNODEnext(newNode,items->head);
        setNODEprev(items->head, newNode);
        items->head = newNode;
        items->size += 1;
        return;
    }
    if(index == items->size) //insert at tail
    {
        
        setNODEnext(items->tail,newNode);
        setNODEprev(newNode, items->tail);
        items->tail = newNode;
        items->size += 1;
        return;
    }
    NODE *trailing = items->head;
    NODE * current = items->head;
    current = getNODEnext(current);

    for(int i = 1;i<items->size;i++)
    {
        if(i == index)
        {         
            setNODEnext(trailing,newNode);
            setNODEprev(newNode,trailing);
            setNODEnext(newNode,current);
            setNODEprev(current, newNode);
                items->size += 1;
            return;
        }
        current = getNODEnext(current);
        trailing = getNODEnext(trailing);
    }

    circularFixup(items);
    return;       

}
void circularFixup(DLL * items)
{
            //Make it circular
    setNODEnext(items->tail, items->head);
    setNODEprev(items->head, items->tail);
}
    
void *removeDLL(DLL *items,int index)
{
    if(items->size == 0)
        return NULL;
    if(index == 0) //remove at front
    {
        void * val = getNODEvalue(items->head);
        items->head = getNODEnext(items->head);
        items->size -= 1;
        return val;
    }
    if(index == items->size-1 )
    {
        void * val = getNODEvalue(items->tail);
        items->tail = getNODEprev(items->tail);
        items->size -= 1;
        return val;
    }

        NODE * current = items->head; //Make a couple temp
        NODE * trailing = items->head;//pointers for insertion
        current = getNODEnext(current);//get current one step ahead
        
        for(int i = 1; i < items->size; i++) //dont start at front so current lags by one
        {
            if(i == index)
            {
                    void * val = getNODEvalue(current);
                    setNODEnext(trailing,getNODEnext(current));
                    setNODEprev(getNODEnext(current), trailing);
                    
                    items->size -= 1;
                    return val;
            }
            current = getNODEnext(current); //set both to next
            trailing = getNODEnext(trailing);
                
        }
    circularFixup(items);
    return NULL;       
}

void unionDLL(DLL *recipient,DLL *donor)
{
    setNODEnext(recipient->tail,donor->head);
    setNODEprev(donor->head, recipient->tail);
    recipient->tail = donor->tail;
    recipient->size += donor->size;
    circularFixup(recipient);
}
void *getDLL(DLL *items,int index)
{
    NODE * current = items->head;
    for(int i = 0;i<=index; i++)
    {
        if((i) == index)
        {        
            return getNODEvalue(current);
        }
        current = getNODEnext(current);
    }
    return NULL;      
}
void *setDLL(DLL *items,int index,void *value)
{
    NODE * current = items->head;
    for(int i = 0;i<=index; i++)
    {
        if((i) == index)
        {      
            setNODEvalue(current,value);
            return getNODEvalue(current);
        }
        current = getNODEnext(current);
    }

     return NULL;     
}
int sizeDLL(DLL *items)
{
    return items->size;
}
void displayDLL(DLL *items,FILE *file)
{
    NODE * current = items->head;
    printf("{");
    for(int i = 0; i<items->size; i++)
    {
        items->display(getNODEvalue(current),file);
        if(i != items->size - 1)
                fprintf(file,",");
        current = getNODEnext(current);
    }
    printf("}");
}

void displayDLLdebug(DLL *items,FILE *file)
{
	NODE * current = items->head;
	    printf("head->{");
	    for(int i = 0; i<items->size; i++)
	    {
	    	void * tmp = getNODEvalue(current);
	        items->display(tmp,file);
            if(i < items->size - 1)
                fprintf(file,",");
	        current = getNODEnext(current);
	    }
	    printf("},tail->{");
        if(items->size > 0)
        {
            items->display(getNODEvalue(items->tail),file);
        }
        
	    printf("}");
}
void freeDLL(DLL *items)
{
    NODE * current = items->head;
    for(int i = 0; i < items->size; i++)
    {
            NODE * temp = getNODEnext(current);
            //freeNODE(current, items->free);
            free(current);
            current = temp;
    }
    //free(items);
    return;
}

void removeDLLall(DLL * dll)
{
    NODE * current = dll->head;
    for(int i = 0; i < dll->size; i++)
    {
            NODE * temp = getNODEnext(current);
            free(current);
            current = temp;
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return;
}
void *removeDLLnode(DLL * dll, void * in)
{
    NODE * node = in;
    void * retval = getNODEvalue(node);
    if(node == dll->head)
    {
        dll->head = getNODEnext(node);
    }
    else if(node == dll->tail)
    {
        dll->tail = getNODEprev(node);
    }
    else
    {
        setNODEnext( getNODEprev(node) , getNODEnext(node) );
        setNODEprev( getNODEnext(node) , getNODEprev(node) );
    }
    free(node);
    return retval;
}
void firstDLL(DLL * dll)
{
    dll->iterator = dll->head;
}
void lastDLL(DLL * dll)
{
    dll->iterator = dll->tail;
}
int moreDLL(DLL * dll)
{
    if(dll->iterator == NULL)
        return 0;
    else 
        return 1;
}
void nextDLL(DLL * dll)
{
    if(dll->iterator != NULL)
        dll->iterator = getNODEnext(dll->iterator);
}
void prevDLL(DLL * dll )
{
     if(dll->iterator != NULL)
        dll->iterator = getNODEnext(dll->iterator);
}
void * currentDLL(DLL * dll)
{
    if(dll->iterator == NULL)
        return NULL;
    return getNODEvalue(dll->iterator);
}



//node.c here for privacy
struct node
    {
    void *value;
    NODE *next;
    NODE *prev;
    };

/*************** public interface *************/

/* constructors */

NODE *
newNODE(void *v,NODE *n)
    {
    NODE *p = malloc(sizeof(NODE));
    if (p == 0) { fprintf(stderr,"out of memory\n"); exit(1); }
    p->value = v;
    p->next = n;
    p->prev = NULL;
    return p;
    }

/* accessors */

void  *getNODEvalue(NODE *n) { return n->value; }
NODE  *getNODEnext(NODE *n)  { return n->next; }
NODE  *getNODEprev(NODE *n)  { return n->prev; }

/* mutators */
void setNODEprev(NODE *n, NODE *p)  { n->prev = p; }
void  setNODEvalue(NODE *n,void *v) { n->value = v; }
void  setNODEnext(NODE *n,NODE *p)  { n->next = p; }

/* visualizers */

void displayNODE(NODE *n,FILE *fp,void (*d)(FILE *,void *))
    {
    fprintf(fp,"[[");
    d(fp,n->value);
    fprintf(fp,"]]");
    }

void displayNODEdebug(NODE *n,FILE *fp,void (*d)(FILE *,void *))
    {
    fprintf(fp,"[[");
    d(fp,n->value);
    fprintf(fp,"@%p->%p]]",(void *)n,(void *)n->next);
    }

void
freeNODE(NODE *n,void (*release)(void *))
    {
    if (release != 0) release(n->value);
    free(n);
    }
