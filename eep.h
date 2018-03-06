/*eep.h*/
#ifndef EEP_H
#define EEP_H
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool eep(struct graph *g, int sigma[], int index[]){
    
    bool eep = true;

    /* Creating and initializing vector A */

    struct adjlist *adjToCheck = (struct adjlist *)malloc(g->n * sizeof(struct adjlist));
    for(int i=0; i < g->n; i++){
        adjToCheck[i].num_members = 0;
        adjToCheck[i].head = NULL;
    }
    
    /* Finished creating vector A */
    
    /* Traveling around the vertices of sigma */

    for(int i=1; i < g->n; i++){
        int choosen_vertex = sigma[i];
        
        printf("Loop %d: vertex %d in sigma\n", i, choosen_vertex);

        /* Finding monotonous adjacency of vertex in sigma[i] */

        struct adjlist *monotonousAdj = (struct adjlist *)malloc(sizeof(struct adjlist));
        monotonousAdj->num_members = 0;
        monotonousAdj->head = NULL;

        struct adjlist_node *adjlistPtr = g->adjlistArr[choosen_vertex].head;
        while (adjlistPtr)
        {
            if(i < index[adjlistPtr->vertex]){
                monotonousAdj->num_members++;

                struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
                newNode->vertex = adjlistPtr->vertex;
                
                if(monotonousAdj->head == NULL){
                    monotonousAdj->head = newNode;
                    newNode->next = NULL;
                    newNode->previous = NULL;
                }
                else{
                    newNode->next = monotonousAdj->head;
                    monotonousAdj->head->previous = newNode;
                    newNode->previous = NULL;
                    monotonousAdj->head = newNode;
                }
            }

            adjlistPtr = adjlistPtr->next;
        }

        printf("Adjacency list of vertex %d:\t", choosen_vertex);
        displayAdjacencyList(*monotonousAdj);
        
        /* Finisehd finding monotonous adjacency */

        if(monotonousAdj->num_members > 0){
            
            /* Finding the closest vertex to sigma[i] */

            int smallestPosition = g->n;

            adjlistPtr = monotonousAdj->head;
            while (adjlistPtr)
            {
                if(index[adjlistPtr->vertex] < smallestPosition)
                    smallestPosition = index[adjlistPtr->vertex];

                adjlistPtr = adjlistPtr->next;
            }

            int closestVertex = sigma[smallestPosition];
            printf("Closest vertex: %d\n", closestVertex);

            /* Finished finding the closest vertex */

            /* Adding each vertex of monotonous adjacency, excepting closestVertex, to adjToCheck */

            adjToCheck[closestVertex].num_members++;
            
            adjlistPtr = monotonousAdj->head;
            while (adjlistPtr)
            {
                if(adjlistPtr->vertex != closestVertex){
                    
                    struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
                    newNode->vertex = adjlistPtr->vertex;
                    newNode->previous = NULL;

                    if(adjToCheck[closestVertex].head == NULL)
                        newNode->next = NULL;
                    else{
                        newNode->next = adjToCheck[closestVertex].head;
                        adjToCheck[closestVertex].head->previous = newNode;
                    }

                    adjToCheck[closestVertex].head = newNode;
                }

                adjlistPtr = adjlistPtr->next;
            }

            /* Finished completing adjToCheck */
        }
        
        printf("Adjacency to check: \t");
        displayAdjacencyList(*adjToCheck);

        /* Comparing adjToCheck and adjacency of choosen_vertex */

        // solução encontrada para consumo de tempo linear
        bool *neighborhood = (bool *)malloc(g->n * sizeof(bool));

        adjlistPtr = g->adjlistArr[choosen_vertex].head;
        while (adjlistPtr)
        {
            neighborhood[adjlistPtr->vertex] = true;    
            adjlistPtr = adjlistPtr->next;
        }


        adjlistPtr = adjToCheck[choosen_vertex].head;
        while (adjlistPtr)
        {
            if(neighborhood[adjlistPtr->vertex] == false){
                eep = false;
                return eep;
            }

            adjlistPtr = adjlistPtr->next;
        }

        /* Finished comparing adjacencies */
    }

    return eep;
}

#endif