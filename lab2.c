#include <stdio.h>
#include <stdlib.h>

typedef struct nodetype
{
int key;
struct nodetype *next;
} NodeT;


//ex1

NodeT* search(NodeT* first, int givenKey) {
    NodeT* p = first;
    while (p != NULL) {
        if (p->key == givenKey) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//ex2
void insert_first(NodeT** first, NodeT** last, int givenKey) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    newNode->key = givenKey;
    newNode->next = *first;
    *first = newNode;
    if (*last == NULL) {
        *last = newNode;
    }
}

void insert_last(NodeT** first, NodeT** last, int givenKey) {
    NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
    newNode->key = givenKey;
    newNode->next = NULL;
    if (*last != NULL) {
        (*last)->next = newNode;
    } else {
        *first = newNode;
    }
    *last = newNode;
}

void insert_after_key(NodeT** first, NodeT** last, int afterKey, int givenKey) {
    NodeT* p = *first;
    while (p != NULL) {
        if (p->key == afterKey) {
            NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
            newNode->key = givenKey;
            newNode->next = p->next;
            p->next = newNode;
            if (p == *last) {
                *last = newNode;
            }
            return;
        }
        p = p->next;
    }
}

//ex4
void delete_first(NodeT** first, NodeT** last) {
    if (*first == NULL) {
        return;
    }
    NodeT* temp = *first;
    *first = (*first)->next;
    if (*first == NULL) {
        *last = NULL;
    }
    free(temp);
}

void delete_last(NodeT** first, NodeT** last) {
    if (*first == NULL) {
        return;
    }
    if (*first == *last) {
        free(*first);
        *first = NULL;
        *last = NULL;
        return;
    }
    NodeT* p = *first;
    while (p->next != *last) {
        p = p->next;
    }
    free(*last);
    p->next = NULL;
    *last = p;
}

void delete_key(NodeT** first, NodeT** last, int givenKey) {
    if (*first == NULL) {
        return;
    }
    if ((*first)->key == givenKey) {
        delete_first(first, last);
        return;
    }
    NodeT* p = *first;
    while (p->next != NULL) {
        if (p->next->key == givenKey) {
            NodeT* temp = p->next;
            p->next = p->next->next;
            if (temp == *last) {
                *last = p;
            }
            free(temp);
            return;
        }
        p = p->next;
    }
}

void destroy_list(NodeT** first, NodeT** last) {
    NodeT* current = *first;
    NodeT* next_node;

    printf("\nFreeing memory for the list...\n");

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    *first = NULL;
    *last = NULL;
    printf("List memory successfully freed.\n");
}

void print_list(NodeT* first) {
    NodeT* p = first;
    while (p != NULL) {
        printf("%d -> ", p->key);
        p = p->next;
    }
    printf("NULL\n");
}

int main() {
    NodeT *first=NULL, *last=NULL;
    printf("--- Start Operations ---\n");

    // 1. Inserati ca prim element, pe rand, cheile 4 si 1
    insert_first(&first, &last, 4);
    printf("After insert_first(4): ");
    print_list(first);

    insert_first(&first, &last, 1);
    printf("After insert_first(1): ");
    print_list(first);

    // 2. Inserati cheia 3 ca ultim element
    insert_last(&first, &last, 3);
    printf("After insert_last(3): ");
    print_list(first);

    // 3. Cautati cheia 2
    if (search(first, 2) != NULL) {
        printf("Key 2 found in the list.\n");
    } else {
        printf("Key 2 not found in the list.\n");
    }

    // 4. Cautati cheia 3
    if (search(first, 3) != NULL) {
        printf("Key 3 found in the list.\n");
    } else {
        printf("Key 3 not found in the list.\n");
    }

    // 5. Inserati cheia 22 dupa cheia 4
    insert_after_key(&first, &last, 4, 22);
    printf("After insert_after_key(4, 22): ");
    print_list(first);
    // 6. Inserati cheia 25 dupa cheia 3
    insert_after_key(&first, &last, 3, 25);
    printf("After insert_after_key(3, 25): ");
    print_list(first);
    // 7. Afisati pe ecran continutul listei
    printf("\n--- Final List Content ---\n");
    print_list(first);
    destroy_list(&first, &last);
    return 0;
}