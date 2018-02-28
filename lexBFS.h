/*lexBFS.h*/
#ifndef GRAPH_H
#define GRAPH_H
#include "graph.h"
#include <stdbool.h>

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


int* lexicographicSearch(struct graph *g){
	int *sigma = new int[g->n];
	int i = g->n + 1;

    /* Initializing Structures */

    struct vertexInfo *vertexTable[g->n];
    struct s *s;
    s->num_members = g->n;

    struct set *unique = (struct set *)malloc(sizeof(struct set));
    unique->flag = 0;
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
    vertexTable[k]->index = 0;
    vertexTable[k]->setPointer = unique;
    vertexTable[k]->adjlist_node_pointer = last_node;

    struct adjlist_node *node_pointer = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
    node_pointer = last_node;

    for(k=g->n - 2; k>=0; k--){

        vertexTable[k]->index = 0;

        struct adjlist_node *node = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
        node->vertex = k;
        node->next = node_pointer;
        node_pointer->previous = node;

        node_pointer = node; // Updating node pointer
                
        vertexTable[k]->setPointer = unique;
        vertexTable[k]->adjlist_node_pointer = node;
    }

    node_pointer->previous = NULL;
    adjlistUnique->head = node_pointer;

    /* Finished Structures Initialization */


    for(k=0; k<g->n; k++){
    	int choosen_vertex = s->head->vertexSet->head->vertex;

    	/* Deleting choosen_vertex of s */
        
        s->head->vertexSet->num_members--;
		s->head->vertexSet->head = s->head->vertexSet->head->next;
        
        if(s->head->vertexSet->head == NULL){ // Deleting s->head because it is empty

            s->num_members--;

            s->head = s->head->next;
            s->head->previous = NULL;
        }

    	/* Finished Deleting */


        /* Updating labels */

		i--;
    	sigma[i-1] = choosen_vertex;
        vertexTable[choosen_vertex] = i;

        /* Finished updating labels */


        /* Updating adjacency of choosen_vertex */

        struct adjlist_node *adjListPtr = g->adjListArr[choosen_vertex].head;
        while (adjListPtr)
        {
            int vertex = adjListPtr->vertex;
            bool future_change = true;
            
            if(vertexTable[vertex]->setPointer->flag == 0){
                // Create new S'
                struct set *new_set = (struct set *)malloc(sizeof(struct set));
                new_set->flag = 0;
                new_set->previous = vertexTable[vertex]->setPointer->previous;
                new_set->next = vertexTable[vertex]->setPointer;
                vertexTable[vertex]->setPointer->previous = new_set;

                if(new_set->previous == NULL) // Update head if necessary
                    s->head = new_set;
                else
                    vertexTable[vertex]->setPointer->previous->next = new_set;

                /* Deleting node from original */
                
                vertexTable[vertex]->setPointer->vertexSet->num_members--;
                if(vertexTable[vertex]->adjlist_node_pointer->previous == NULL){
                    // Updating head
                    vertexTable[vertex]->setPointer->vertexSet->head = vertexTable[vertex]->adjlist_node_pointer->next;

                    if(vertexTable[vertex]->adjlist_node_pointer->next == NULL){
                        // No future changes of creating new set
                        future_change = false;
                    }
                    else{
                        vertexTable[vertex]->adjlist_node_pointer->next->previous = NULL;
                    }

                }
                else{
                    vertexTable[vertex]->adjlist_node_pointer->previous->next = vertexTable[vertex]->adjlist_node_pointer->next;

                    if(vertexTable[vertex]->adjlist_node_pointer->next != NULL){
                        vertexTable[vertex]->adjlist_node_pointer->next->previous = vertexTable[vertex]->adjlist_node_pointer->previous;
                    }
                }

                



                if(s->head->vertexSet->head == NULL){ // Deleting s->head because it is empty

                    s->num_members--;

                    s->head = s->head->next;
                    s->head->previous = NULL;
                }

                /* Finished Deleting */


                // Add node into new_set

                


                // Update set in vertexTable

            }


            

            // Update vertexTable[??]->setPointer

            // do something with adjListPtr
            
            adjListPtr = adjListPtr->next;

            vertexTable[choosen_vertex]
            tmp->vertex;
        }


        /* Finished updating adjacency of choosen_vertex */


    }

	return sigma;
}

#endif