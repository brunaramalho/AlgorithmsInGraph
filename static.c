#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "staticBlock.h"

void main(int argc, char *argv[]){
    int n = atoi(argv[1]);

    struct graph *g = createStatic(n);
    
    // Adjacency List
    for (int i = 0; i < g->n; i++){   
        if(i>0)
            printf("\n");
        printf("%d: [", i+1);
        
        struct adjlist_node *adjlistPtr = g->adjlistArr[i].head;
        
        int count = 0;
        while (adjlistPtr)
        {
            if(count>0)
                printf(", ");
            printf("%d", adjlistPtr->vertex+1);
            adjlistPtr = adjlistPtr->next;
            count++;
        }
        printf("]");
    }

    printf("|");

    // Adjacency Matrix
    for (int i = 0; i < g->n; i++){
        
        if(i>0)
            printf("\n");
        printf("[");

        int adj[n]; 
        for (int j = 0; j < n; j++)
        {
            adj[j]=0;
        }
        
        struct adjlist_node *adjlistPtr = g->adjlistArr[i].head;
        
        while (adjlistPtr)
        {
            adj[adjlistPtr->vertex] = 1;
            adjlistPtr = adjlistPtr->next;
        }

        for (int j = 0; j < n; j++)
        {
            if(j>0)
                printf(", ");
            printf("%d", adj[j]);
        }
        
        printf("]");
    }

    // displayGraph(g);
}