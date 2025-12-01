#include "liste.c"
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 10

void push(NodeT** stack, int key) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    newNode->key = key;}

NodeT* pop(NodeT** stack){
    if (*stack == NULL) {
        return NULL;
    }
    NodeT* topNode = *stack;
    *stack = (*stack)->next;
    return topNode;
}
typedef struct _queue
{
int vec[CAPACITY];
int size;
int head, tail;
}queueT;

typedef struct node_type
{
int key;
double value;

struct node_type *next;

struct node_type *prev;
} NodeDL;