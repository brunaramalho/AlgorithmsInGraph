/*graph.h*/
#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>

struct adjlist_node{
    int vertex;
    struct adjlist_node *next;
    struct adjlist_node *previous;
};

struct adjlist{
    int num_members;
    struct adjlist_node *head;
};

struct graph{
    int n;
    struct adjlist *adjlistArr; /*its size will be the number of vertices in graph*/
};

struct adjlist_node* createNode(int v){
    struct adjlist_node *newNode = (struct adjlist_node *)malloc(sizeof(struct adjlist_node));

    newNode->vertex = v;
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

struct graph* createGraph(int n){
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph));
    graph->n = n;

    /* Create an array of adjacency lists*/
    graph->adjlistArr = (struct adjlist *)malloc(n * sizeof(struct adjlist));

    for(int i = 0; i < n; i++)
    {
        graph->adjlistArr[i].head = NULL;
        graph->adjlistArr[i].num_members = 0;
    }

    return graph;
}

void destroyGraph(struct graph *graph){
    if(graph)
    {
        if(graph->adjlistArr)
        {
            /*Free up the nodes*/
            for (int v = 0; v < graph->n; v++)
            {
                struct adjlist_node *adjlistPtr = graph->adjlistArr[v].head;
                while (adjlistPtr)
                {
                    struct adjlist_node *tmp = adjlistPtr;
                    adjlistPtr = adjlistPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjlistArr);
        }
        /*Free the graph*/
        free(graph);
    }
}

void addEdge(struct graph *graph, int vertex1, int vertex2){
    /* Add an edge from vertex1 to vertex2 in the adjacency list*/
    struct adjlist_node *newNode = createNode(vertex2);
    newNode->next = graph->adjlistArr[vertex1].head;
    newNode->previous = NULL;
    if(graph->adjlistArr[vertex1].head != NULL)
        graph->adjlistArr[vertex1].head->previous = newNode;
    graph->adjlistArr[vertex1].head = newNode;
    graph->adjlistArr[vertex1].num_members++;
    

    /* Add an edge from vertex2 to vertex1 also*/
    newNode = createNode(vertex1);
    newNode->next = graph->adjlistArr[vertex2].head;
    newNode->previous = NULL;
    if(graph->adjlistArr[vertex1].head != NULL)
        graph->adjlistArr[vertex1].head->previous = newNode;
    graph->adjlistArr[vertex2].head = newNode;
    graph->adjlistArr[vertex2].num_members++;
}

void displayAdjacencyList(struct adjlist adjlist){
    struct adjlist_node *adjlistPtr = adjlist.head;

    while (adjlistPtr)
    {
        printf("%d->", adjlistPtr->vertex);
        adjlistPtr = adjlistPtr->next;
    }
    printf("NULL\n");
}

void displayGraph(struct graph *graph){
    for (int i = 0; i < graph->n; i++){
        printf("\n%d: ", i);
        displayAdjacencyList(graph->adjlistArr[i]);
    }
    printf("\n");
}

void displayRepresentationGraph(struct graph *graph, int sigma[]){
    for (int i = 0; i < graph->n; i++){
        printf("\n%d: ", sigma[i]);
        displayAdjacencyList(graph->adjlistArr[sigma[i]]);
    }
    printf("\n");
}

#endif