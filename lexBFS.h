/*lexBFS.h*/
#ifndef LEXBFS_H
#define LEXBFS_H
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct set{
    bool flag;
    struct adjlist *vertexSet; // Also a Double Linked List
    struct set *previous;
    struct set *next;
};

struct vertexInfo{
    int index;
    struct set *setPointer;
    struct adjlist_node *adjlist_node_pointer;
};

struct s{
    int num_members;
    struct set *head;
};

struct setFlagUpdate{
    struct set *setToUpdate;
    struct setFlagUpdate *next;
};

struct output{
    int *sigma;
    int *index; // equivalent: sigma_{-1}
};

void displaySet(struct set *set){
    struct set *setPtr = set;
    int counter = 0;
    while (setPtr)
    {
        counter++;
        printf("Set %d\n", counter);
        displayAdjacencyList(*(setPtr->vertexSet));
        setPtr = setPtr->next;

        printf("\n");
    }
}

struct output lexBFS(struct graph *g){
    
    int *sigma = (int *)malloc(g->n * sizeof(int));
    int *index = (int *)malloc(g->n * sizeof(int));
    int i = g->n + 1;

    /* Initializing Structures */

    struct vertexInfo *vertexTable = (struct vertexInfo *)malloc(g->n * sizeof(struct vertexInfo));
    struct s *s = (struct s *)malloc(sizeof(struct s));
    s->num_members = g->n;

    struct set *unique = (struct set *)malloc(sizeof(struct set));
    unique->flag = false;
    unique->previous = NULL;
    unique->next = NULL;

    s->head = unique;

    struct adjlist *adjlistUnique = (struct adjlist *)malloc(sizeof(struct adjlist));
    adjlistUnique->num_members = g->n;

    unique->vertexSet = adjlistUnique;
    
    int k =g->n - 1;
    struct adjlist_node *last_node = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
    last_node->vertex = k;
    last_node->next = NULL;
    last_node->previous = NULL;
    vertexTable[k].index = 0;
    vertexTable[k].setPointer = unique;
    vertexTable[k].adjlist_node_pointer = last_node;

    struct adjlist_node *node_pointer = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
    node_pointer = last_node;

    for(k=g->n - 2; k>=0; k--){

        vertexTable[k].index = 0;

        struct adjlist_node *node = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
        node->vertex = k;
        node->next = node_pointer;
        node_pointer->previous = node;

        node_pointer = node; // Updating node pointer
                
        vertexTable[k].setPointer = unique;
        vertexTable[k].adjlist_node_pointer = node;
    }

    node_pointer->previous = NULL;
    adjlistUnique->head = node_pointer;

    /* Finished Structures Initialization */

    for(k=0; k < g->n - 1; k++){
        
        // printf("### %dº loop\n", k+1);

        int choosen_vertex = s->head->vertexSet->head->vertex;

        // printf("Choosen vertex: %d\n", choosen_vertex);

        /* Deleting choosen_vertex of s */

        s->head->vertexSet->num_members--;
        s->head->vertexSet->head = s->head->vertexSet->head->next;
        
        if(s->head->vertexSet->head == NULL){ // Deleting s->head because it is empty

            s->num_members--;
            s->head = s->head->next;
            if(s->head != NULL)
                s->head->previous = NULL;
        }
        else
            s->head->vertexSet->head->previous = NULL;
    
        /* Finished Deleting */


        /* Updating labels */

        i--;
        sigma[i-1] = choosen_vertex;
        index[choosen_vertex] = i-1;
        vertexTable[choosen_vertex].index = i;

        /* Finished updating labels */


        /* Updating adjacency of choosen_vertex */

        struct setFlagUpdate *set_flag_update = (struct setFlagUpdate *)malloc(sizeof(struct setFlagUpdate));
        int counter = 0;
        
        struct adjlist_node *adjlistPtr = g->adjlistArr[choosen_vertex].head;
        while (adjlistPtr)
        {
            int vertex = adjlistPtr->vertex;
            bool future_change = true;
            
            if(vertexTable[vertex].index == 0){ // Only the ones not already choosen

                // printf("Updating label of vertex %d\n", vertex);
                if(vertexTable[vertex].setPointer->flag == false){
                    
                    /* Deleting node from original */        
                    
                    if(vertexTable[vertex].adjlist_node_pointer->previous == NULL){
                        
                        if(vertexTable[vertex].adjlist_node_pointer->next == NULL){
                            // No future changes of creating new set
                            future_change = false;
                        }
                        else{
                            vertexTable[vertex].setPointer->vertexSet->num_members--;
                            // Updating head
                            vertexTable[vertex].setPointer->vertexSet->head = vertexTable[vertex].adjlist_node_pointer->next;
                            vertexTable[vertex].adjlist_node_pointer->next->previous = NULL;
                        }

                    }
                    else{
                        vertexTable[vertex].setPointer->vertexSet->num_members--;
                        vertexTable[vertex].adjlist_node_pointer->previous->next = vertexTable[vertex].adjlist_node_pointer->next;

                        if(vertexTable[vertex].adjlist_node_pointer->next != NULL){
                            vertexTable[vertex].adjlist_node_pointer->next->previous = vertexTable[vertex].adjlist_node_pointer->previous;
                        }
                    }

                    /* Finished Deleting node from original if necessary (future_change) */

                    /* Creating new set in vertexTable:
                        future_change = 0 means that there was only 1 node in adjlist, that is, 
                        we would simply create another adjlist with the same vertex */

                    if(future_change){

                        s->num_members++;
        
                        struct set *new_set = (struct set *)malloc(sizeof(struct set));
                        new_set->flag = false;
                        new_set->previous = vertexTable[vertex].setPointer->previous;
                        new_set->next = vertexTable[vertex].setPointer;
                        vertexTable[vertex].setPointer->previous = new_set;
                        vertexTable[vertex].setPointer->flag = true;
    
                        if(counter==0){
                            set_flag_update->setToUpdate = vertexTable[vertex].setPointer;
                            set_flag_update->next = NULL;
                        }
                        else{
                            struct setFlagUpdate *new_set_flag_update = (struct setFlagUpdate *)malloc(sizeof(struct setFlagUpdate));
                            new_set_flag_update->setToUpdate = vertexTable[vertex].setPointer;
                            new_set_flag_update->next = set_flag_update;
                            set_flag_update = new_set_flag_update;
                        }
                        counter++;


                        if(new_set->previous == NULL) // Update head if necessary
                            s->head = new_set;
                        else
                            new_set->previous->next = new_set;

                        /* Adding node into new_set */

                        struct adjlist *new_vertexSet = (struct adjlist *)malloc(sizeof(struct adjlist));
                        new_set->vertexSet = new_vertexSet;
                        new_vertexSet->num_members = 1;
                        new_vertexSet->head = vertexTable[vertex].adjlist_node_pointer;
                        vertexTable[vertex].adjlist_node_pointer->next = NULL;
                        vertexTable[vertex].adjlist_node_pointer->previous = NULL;

                        /* Finished adding node into new_set */

                        
                        /* Updating vertexTable */

                        vertexTable[vertex].setPointer = new_set;
    
                        /* Finished updating vertexTable */
                    }

                    /* Finished creating new set in vertexTable */
                }
                else{
                    /* Deleting node from original */

                    vertexTable[vertex].setPointer->vertexSet->num_members--;

                    if(vertexTable[vertex].adjlist_node_pointer->previous == NULL){
                        // Updating head
                        vertexTable[vertex].setPointer->vertexSet->head = vertexTable[vertex].adjlist_node_pointer->next;

                        if(vertexTable[vertex].adjlist_node_pointer->next == NULL){
                            // That will be empty, so we need to delete the whole set
                            vertexTable[vertex].setPointer->previous->next = vertexTable[vertex].setPointer->next;
                            if(vertexTable[vertex].setPointer->next != NULL)
                                vertexTable[vertex].setPointer->next->previous = vertexTable[vertex].setPointer->previous;
                        }
                        else{
                            vertexTable[vertex].adjlist_node_pointer->next->previous = NULL;
                        }

                    }
                    else{
                        vertexTable[vertex].adjlist_node_pointer->previous->next = vertexTable[vertex].adjlist_node_pointer->next;

                        if(vertexTable[vertex].adjlist_node_pointer->next != NULL){
                            vertexTable[vertex].adjlist_node_pointer->next->previous = vertexTable[vertex].adjlist_node_pointer->previous;
                        }
                    }

                    /* Finished Deleting node from original if necessary */

                    /* Adding current node into the already created new set */

                    vertexTable[vertex].setPointer->previous->vertexSet->num_members++;
                    vertexTable[vertex].setPointer->previous->vertexSet->head->previous = vertexTable[vertex].adjlist_node_pointer;
                    vertexTable[vertex].adjlist_node_pointer->next = vertexTable[vertex].setPointer->previous->vertexSet->head;
                    vertexTable[vertex].adjlist_node_pointer->previous = NULL;
                    vertexTable[vertex].setPointer->previous->vertexSet->head = vertexTable[vertex].adjlist_node_pointer;
                    
                    /* Updating vertexTable */

                    vertexTable[vertex].setPointer = vertexTable[vertex].setPointer->previous;
    
                    /* Finished updating vertexTable */

                    /* Finished adding current node */
                }
            }
            adjlistPtr = adjlistPtr->next;
        }

        /* Updating flag all to false */

        struct setFlagUpdate *set_flag_update_ptr = set_flag_update;
        for(int x=0; x<counter; x++){

            set_flag_update_ptr->setToUpdate->flag = false;
            set_flag_update_ptr = set_flag_update_ptr->next;
        }

        /* Finished updating flag all to false */

        /* Finished updating adjacency of choosen_vertex */
        
        // displaySet(s->head);
        // printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    }

    sigma[0] = s->head->vertexSet->head->vertex;
    index[s->head->vertexSet->head->vertex] = 0;
    
    struct output result;
    result.index = index;
    result.sigma = sigma;

    return result;
}

#endif