#include <stdio.h>

#include <stdlib.h>



//

// ===================== STACK (LISTĂ SIMPLU ÎNLĂNȚUITĂ) =====================

//



typedef struct node {

    int key;

    struct node* next;

} NodeT;



NodeT* initStack() {

    return NULL;

}



void push(NodeT** stack, int key) {

    NodeT* p = (NodeT*)malloc(sizeof(NodeT));

    p->key = key;

    p->next = *stack;

    *stack = p;

}



int pop(NodeT** stack) {

    if (*stack == NULL) {

        printf("Stack underflow\n");

        return -1;

    }

    NodeT* p = *stack;

    int val = p->key;

    *stack = p->next;

    free(p);

    return val;

}



void printStack(NodeT* stack) {

    printf("Stack: ");

    for (NodeT* p = stack; p != NULL; p = p->next)

        printf("%d ", p->key);

    printf("\n");

}



//

// ===================== QUEUE (VECTOR CIRCULAR) =====================

//



#define CAPACITY 10



typedef struct queue {

    int vec[CAPACITY];

    int head, tail, size;

} Queue;



void initQueue(Queue* q) {

    q->head = q->tail = q->size = 0;

}



void enqueue(Queue* q, int key) {

    if (q->size == CAPACITY) {

        printf("Queue overflow\n");

        return;

    }

    q->vec[q->tail] = key;

    q->tail = (q->tail + 1) % CAPACITY;

    q->size++;

}



int dequeue(Queue* q) {

    if (q->size == 0) {

        printf("Queue underflow\n");

        return -1;

    }

    int val = q->vec[q->head];

    q->head = (q->head + 1) % CAPACITY;

    q->size--;

    return val;

}



void printQueue(Queue* q) {

    printf("Queue: ");

    int idx = q->head;

    for (int i = 0; i < q->size; i++) {

        printf("%d ", q->vec[idx]);

        idx = (idx + 1) % CAPACITY;

    }

    printf("\n");

}



//

// ===================== LISTĂ DUBLU ÎNLĂNȚUITĂ =====================

//



typedef struct nodeDL {

    int key;

    struct nodeDL* next;

    struct nodeDL* prev;

} NodeDL;



typedef struct {

    NodeDL* first;

    NodeDL* last;

} ListDL;



void initList(ListDL* L) {

    L->first = L->last = NULL;

}



void insert_first(ListDL* L, int key) {

    NodeDL* p = (NodeDL*)malloc(sizeof(NodeDL));

    p->key = key;

    p->prev = NULL;

    p->next = L->first;



    if (L->first == NULL)

        L->first = L->last = p;

    else {

        L->first->prev = p;

        L->first = p;

    }

}



void insert_last(ListDL* L, int key) {

    NodeDL* p = (NodeDL*)malloc(sizeof(NodeDL));

    p->key = key;

    p->next = NULL;

    p->prev = L->last;



    if (L->last == NULL)

        L->first = L->last = p;

    else {

        L->last->next = p;

        L->last = p;

    }

}



NodeDL* searchDL(ListDL* L, int key) {

    for (NodeDL* p = L->first; p != NULL; p = p->next)

        if (p->key == key)

            return p;

    return NULL;

}



void insert_after_key(ListDL* L, int afterKey, int key) {

    NodeDL* q = searchDL(L, afterKey);

    if (!q) return;



    NodeDL* p = (NodeDL*)malloc(sizeof(NodeDL));

    p->key = key;



    p->next = q->next;

    p->prev = q;



    if (q->next != NULL)

        q->next->prev = p;

    else

        L->last = p;



    q->next = p;

}



void delete_first(ListDL* L) {

    if (L->first == NULL) return;



    NodeDL* p = L->first;

    L->first = p->next;



    if (L->first == NULL)

        L->last = NULL;

    else

        L->first->prev = NULL;



    free(p);

}



void delete_last(ListDL* L) {

    if (L->last == NULL) return;



    NodeDL* p = L->last;

    L->last = p->prev;



    if (L->last == NULL)

        L->first = NULL;

    else

        L->last->next = NULL;



    free(p);

}



void delete_key(ListDL* L, int key) {

    NodeDL* p = searchDL(L, key);

    if (!p) return;



    if (p == L->first)

        delete_first(L);

    else if (p == L->last)

        delete_last(L);

    else {

        p->prev->next = p->next;

        p->next->prev = p->prev;

        free(p);

    }

}



void print_forward(ListDL* L) {

    printf("Forward: ");

    for (NodeDL* p = L->first; p != NULL; p = p->next)

        printf("%d ", p->key);

    printf("\n");

}



void print_backward(ListDL* L) {

    printf("Backward: ");

    for (NodeDL* p = L->last; p != NULL; p = p->prev)

        printf("%d ", p->key);

    printf("\n");

}



//

// ===================== MAIN =====================

//



int main() {

    printf("=== LABORATOR 3: STIVE, COZI, LISTE DUBLU INLANTUITE ===\n\n");



    //

    // TEST STACK

    //

    printf("=== TEST STACK ===\n");

    NodeT* stack = initStack();

    push(&stack, 10);

    push(&stack, 20);

    push(&stack, 30);

    printStack(stack);



    printf("Pop: %d\n", pop(&stack));

    printStack(stack);



    //

    // TEST QUEUE

    //

    printf("\n=== TEST QUEUE ===\n");

    Queue q;

    initQueue(&q);



    enqueue(&q, 5);

    enqueue(&q, 10);

    enqueue(&q, 15);

    printQueue(&q);



    printf("Dequeue: %d\n", dequeue(&q));

    printQueue(&q);



    //

    // TEST LISTĂ DUBLU ÎNLĂNȚUITĂ

    //

    printf("\n=== TEST LISTA DUBLU INLANTUITA ===\n");

    ListDL L;

    initList(&L);



    insert_first(&L, 3);

    insert_first(&L, 1);

    insert_last(&L, 5);

    insert_after_key(&L, 3, 4);



    print_forward(&L);

    print_backward(&L);



    delete_first(&L);

    delete_last(&L);

    delete_key(&L, 3);



    print_forward(&L);

    print_backward(&L);



    return 0;

}

 deDL;