#include <stdio.h> 

#include <stdlib.h> 

  

#define M 7   // dimensiunea tabelei 

  

// 

// ===================== CHAINING ===================== 

// 

  

typedef struct node { 

    int key; 

    struct node* next; 

} NodeT; 

  

NodeT* hTable[M]; 

  

void initChaining() { 

    for (int i = 0; i < M; i++) 

        hTable[i] = NULL; 

} 

  

int h(int key) { 

    return key % M; 

} 

  

void insertChaining(int key) { 

    int index = h(key); 

    NodeT* p = (NodeT*)malloc(sizeof(NodeT)); 

    p->key = key; 

    p->next = hTable[index]; 

    hTable[index] = p; 

} 

  

NodeT* findChaining(int key) { 

    int index = h(key); 

    NodeT* p = hTable[index]; 

    while (p != NULL) { 

        if (p->key == key) 

            return p; 

        p = p->next; 

    } 

    return NULL; 

} 

  

void deleteChaining(int key) { 

    int index = h(key); 

    NodeT* p = hTable[index]; 

    NodeT* prev = NULL; 

  

    while (p != NULL) { 

        if (p->key == key) { 

            if (prev == NULL) 

                hTable[index] = p->next; 

            else 

                prev->next = p->next; 

            free(p); 

            return; 

        } 

        prev = p; 

        p = p->next; 

    } 

} 

  

void printChaining() { 

    printf("\n=== HASH TABLE (CHAINING) ===\n"); 

    for (int i = 0; i < M; i++) { 

        printf("%d: ", i); 

        NodeT* p = hTable[i]; 

        while (p != NULL) { 

            printf("%d -> ", p->key); 

            p = p->next; 

        } 

        printf("NULL\n"); 

    } 

} 

  

// 

// ===================== LINEAR PROBING ===================== 

// 

  

int linearTable[M]; 

  

void initLinear() { 

    for (int i = 0; i < M; i++) 

        linearTable[i] = -1; 

} 

  

int h0(int key) { 

    return key % M; 

} 

  

void insertLinear(int key) { 

    int index = h0(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i) % M; 

        if (linearTable[pos] == -1) { 

            linearTable[pos] = key; 

            return; 

        } 

    } 

    printf("Linear probing overflow\n"); 

} 

  

int findLinear(int key) { 

    int index = h0(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i) % M; 

        if (linearTable[pos] == key) 

            return pos; 

        if (linearTable[pos] == -1) 

            return -1; 

    } 

    return -1; 

} 

  

void printLinear() { 

    printf("\n=== HASH TABLE (LINEAR PROBING) ===\n"); 

    for (int i = 0; i < M; i++) 

        printf("%d: %d\n", i, linearTable[i]); 

} 

  

// 

// ===================== QUADRATIC PROBING ===================== 

// 

  

int quadTable[M]; 

  

void initQuadratic() { 

    for (int i = 0; i < M; i++) 

        quadTable[i] = -1; 

} 

  

void insertQuadratic(int key) { 

    int index = h0(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i*i) % M; 

        if (quadTable[pos] == -1) { 

            quadTable[pos] = key; 

            return; 

        } 

    } 

    printf("Quadratic probing overflow\n"); 

} 

  

int findQuadratic(int key) { 

    int index = h0(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i*i) % M; 

        if (quadTable[pos] == key) 

            return pos; 

        if (quadTable[pos] == -1) 

            return -1; 

    } 

    return -1; 

} 

  

void printQuadratic() { 

    printf("\n=== HASH TABLE (QUADRATIC PROBING) ===\n"); 

    for (int i = 0; i < M; i++) 

        printf("%d: %d\n", i, quadTable[i]); 

} 

  

// 

// ===================== DOUBLE HASHING ===================== 

// 

  

int doubleTable[M]; 

  

void initDouble() { 

    for (int i = 0; i < M; i++) 

        doubleTable[i] = -1; 

} 

  

int h1(int key) { 

    return key % M; 

} 

  

int h2(int key) { 

    return 5 - (key % 5); 

} 

  

void insertDouble(int key) { 

    int index = h1(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i * h2(key)) % M; 

        if (doubleTable[pos] == -1) { 

            doubleTable[pos] = key; 

            return; 

        } 

    } 

    printf("Double hashing overflow\n"); 

} 

  

int findDouble(int key) { 

    int index = h1(key); 

    for (int i = 0; i < M; i++) { 

        int pos = (index + i * h2(key)) % M; 

        if (doubleTable[pos] == key) 

            return pos; 

        if (doubleTable[pos] == -1) 

            return -1; 

    } 

    return -1; 

} 

  

void printDouble() { 

    printf("\n=== HASH TABLE (DOUBLE HASHING) ===\n"); 

    for (int i = 0; i < M; i++) 

        printf("%d: %d\n", i, doubleTable[i]); 

} 

  

// 

// ===================== MAIN ===================== 

// 

  

int main() { 

    int data[] = {36, 14, 26, 21, 5, 19, 4}; 

    int n = sizeof(data) / sizeof(data[0]); 

  

    // 

    // CHAINING 

    // 

    initChaining(); 

    for (int i = 0; i < n; i++) 

        insertChaining(data[i]); 

    printChaining(); 

  

    // 

    // LINEAR PROBING 

    // 

    initLinear(); 

    for (int i = 0; i < n; i++) 

        insertLinear(data[i]); 

    printLinear(); 

  

    // 

    // QUADRATIC PROBING 

    // 

    initQuadratic(); 

    for (int i = 0; i < n; i++) 

        insertQuadratic(data[i]); 

    printQuadratic(); 

  

    // 

    // DOUBLE HASHING 

    // 

    initDouble(); 

    for (int i = 0; i < n; i++) 

        insertDouble(data[i]); 

    printDouble(); 

  

    return 0; 

} 

 