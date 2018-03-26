/*smv.h*/
#ifndef SMV_H
#define SMV_H
#include <stdbool.h>
#include <string.h>
#include "graph.h"

struct smvSet{
	struct adjlist *smv;
	int multiplicity;
	struct smvSet *next;
	struct smvSet *previous;
};

struct qSet{
	struct adjlist *q;
	struct qSet *next;
	struct qSet *previous;
};

struct pointer{
	struct qSet *qSetPointer;
	struct smvSet *smvSetPointer;
};

struct smvSet* smv(struct graph *g, int sigma[], int index[]){
	int q=1,j=0;
	int *position = (int *)malloc(g->n * sizeof(int));
	int *last = (int *)malloc(g->n * sizeof(int));
	struct qSet *qSetHead = (struct qSet *)malloc(sizeof(struct qSet));
	struct smvSet *smvSetHead = (struct smvSet *)malloc(sizeof(struct smvSet));
	struct pointer *pointers = (struct pointer *)malloc(g->n * sizeof(struct pointer));

	qSetHead->next = NULL;
	qSetHead->previous = NULL;
	struct adjlist *firstAdjlist = (struct adjlist *)malloc(sizeof(struct adjlist));
	struct adjlist_node *firstNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
	firstNode->next = NULL;
	firstNode->previous = NULL;
	firstNode->vertex = sigma[g->n];
	firstAdjlist->head = firstNode;
	firstAdjlist->num_members = 1;
	
	qSetHead->q = firstAdjlist;
	position[sigma[g->n]] = 1;
	pointers[0].qSetPointer = qSetHead;
	
	smvSetHead->next = NULL;
	smvSetHead->previous = NULL;
	smvSetHead->smv = NULL;
	smvSetHead->multiplicity = 0;
	pointers[0].smvSetPointer = smvSetHead;

	for(int i = 0; i < g->n; i++){
		last[i] = 0;
	}
	
	for(int i = g->n - 2; i >= 0; i--){

		int choosen_vertex = sigma[i];
		
        /* Finding monotone adjacency of vertex in sigma[i] */

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

        printf("Monotone Adjacency list of vertex %d:\t", choosen_vertex);
        displayAdjacencyList(*monotonousAdj);
        
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

	        int k = position[closestVertex];

			if(monotonousAdj->num_members < pointers[k-1].qSetPointer->q->num_members){
				
				q++;

				struct qSet *qSetNew = (struct qSet *)malloc(sizeof(struct qSet));
				qSetNew->next = NULL;
				qSetNew->previous = pointers[q-2].qSetPointer;
				pointers[q-2].qSetPointer->next = qSetNew;

				/* Adding v_i to monotonous adjacency of v_i */

				struct adjlist *newAdj = (struct adjlist *)malloc(sizeof(struct adjlist));
				memcpy(newAdj, monotonousAdj, sizeof(struct adjlist));
				
				newAdj->num_members++;

                struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
                newNode->vertex = sigma[i];
                
                newNode->next = newAdj->head;
                newAdj->head->previous = newNode;
                newNode->previous = NULL;
                newAdj->head = newNode;

                /* Finished adding v_i to monotonous adjacency of v_i */

				qSetNew->q = newAdj;
				pointers[q-1].qSetPointer = qSetNew;

				printf("Creating another Maximal Click Q_%d:\t", q);
				displayAdjacencyList(*newAdj);

				position[sigma[i]] = q;
				
				int tam = monotonousAdj->num_members;
				int c = last[tam];

				bool theSame = true;

				if(pointers[c].smvSetPointer->smv == NULL){
					theSame = false;
				}
				else{
					
					/* Creating another structure to make it linear */

					bool *auxiliar = (bool *)malloc(g->n * sizeof(bool));

			        adjlistPtr = pointers[c].smvSetPointer->smv->head;
			        while (adjlistPtr)
			        {
			            auxiliar[adjlistPtr->vertex] = true;    
			            adjlistPtr = adjlistPtr->next;
			        }

					/* Finished creating another structure to make it linear */ 
					
					adjlistPtr = monotonousAdj->head;
			        while (adjlistPtr)
			        {
			            if(auxiliar[adjlistPtr->vertex] == false){
			                theSame = false;
			                break;
			            }
			            adjlistPtr = adjlistPtr->next;
			        }
				}

				if(!theSame){

					j++;

					struct adjlist *newSmv = (struct adjlist *)malloc(sizeof(struct adjlist));
					memcpy(newSmv, monotonousAdj, sizeof(struct adjlist));

					printf("Creating another smv S_%d:\t", j);
					displayAdjacencyList(*(newSmv));

					struct smvSet *newSmvSet = (struct smvSet *)malloc(sizeof(struct smvSet));
					newSmvSet->smv = newSmv;
					newSmvSet->multiplicity = 1;
					newSmvSet->next = NULL;
					newSmvSet->previous = pointers[j-1].smvSetPointer;
					pointers[j-1].smvSetPointer->next = newSmvSet;
					pointers[j].smvSetPointer = newSmvSet;

					last[tam] = j;
				}
				else{
					printf("Upgrading smv S_%d:\t", c);
					pointers[c].smvSetPointer->multiplicity++;
				}
			}
			else{
				/* Adding v_i to Q_k */

				pointers[k-1].qSetPointer->q->num_members++;

				struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));
			    newNode->vertex = sigma[i];
			    newNode->next = pointers[k-1].qSetPointer->q->head;
			    newNode->previous = NULL;
			    pointers[k-1].qSetPointer->q->head->previous = newNode;
			    pointers[k-1].qSetPointer->q->head = newNode;

				/* Finished adding v_i to Q_k */

				position[sigma[i]] = k;
				
				printf("Upgrading Maximal Click Q_%d:\t", k);
				displayAdjacencyList(*(pointers[k-1].qSetPointer->q));
			}
		}
	}

	return smvSetHead->next;
}


#endif