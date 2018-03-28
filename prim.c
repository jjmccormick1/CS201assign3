//Jeremy McCormick
//CS201 Anderson
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "binomial.h"

int main(int argc,char **argv)
{
    if(strcmp(argv[0],"-v") == 0)
    {
        printf("Jeremy McCormick");
        return 0;
    }
    
    FILE * fp = fopen(argc[0], r);
    if(fp == NULL)
    {
        printf("File not found");
        return 1;
    }
    
    
