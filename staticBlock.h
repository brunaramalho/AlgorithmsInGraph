/*staticBlock.h*/
#ifndef STATICBLOCK_H
#define STATICBLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <time.h>

void combinationUtil(int arr[], int data[],  
                    int start, int end,  
                    int index, struct graph *g);

// including start and end as vertexes
void addAllEdges(int start, int end, struct graph *g){ 
    int data[2];
    int n = end-start + 1;
    
    int arr[n];
    for(int i=0; i<n; i++){
        arr[i] = start+i;
    }

    combinationUtil(arr, data, 0, n-1, 0, g); 
} 

void combinationUtil(int arr[], int data[], int start, int end, 
                     int index, struct graph *g){
    if (index == 2) 
    { 
        addEdge(g, data[0], data[1]);
        return; 
    }

    for (int i=start; i<=end && end-i+1 >= 2-index; i++) 
    { 
        data[index] = arr[i]; 
        combinationUtil(arr, data, i+1, end, index+1, g); 
    } 
} 

struct graph* createStatic(int n){
    srand(time(NULL));

    struct graph *g = createGraph(n);
   
    int n_vertex = rand() % n + 1;
    addAllEdges(0, n_vertex - 1, g);
    int remaining = n - n_vertex;

    while(remaining > 0){
        n_vertex = rand() % remaining + 1;
        addAllEdges(n-remaining, n-remaining+n_vertex-1, g);
        int choosen = rand() % (n-remaining);
        for(int i=n-remaining; i <= n-remaining+n_vertex-1; i++){
            addEdge(g, choosen, i);
        }
        remaining = remaining - n_vertex;
    }

    return g;
}

#endif