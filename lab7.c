#include <stdio.h> 

#include <stdlib.h> 

  

#define MAXN 100 

  

// 

// ===================== MATRICĂ DE ADIACENȚĂ ===================== 

// 

  

int n;                 // număr noduri 

int A[MAXN][MAXN];     // matrice adiacență 

  

void readMatrix(const char* filename) { 

    FILE* f = fopen(filename, "r"); 

    if (!f) { 

        printf("Nu pot deschide fisierul %s\n", filename); 

        exit(1); 

    } 

  

    fscanf(f, "%d", &n); 

  

    for (int i = 0; i < n; i++) 

        for (int j = 0; j < n; j++) 

            fscanf(f, "%d", &A[i][j]); 

  

    fclose(f); 

} 

  

void printMatrix() { 

    printf("\n=== MATRICE DE ADIACENTA ===\n"); 

    for (int i = 0; i < n; i++) { 

        for (int j = 0; j < n; j++) 

            printf("%d ", A[i][j]); 

        printf("\n"); 

    } 

} 

  

// 

// ===================== BFS (MATRICE) ===================== 

// 

  

void BFS_matrix(int start) { 

    int visited[MAXN] = {0}; 

    int queue[MAXN], head = 0, tail = 0; 

  

    visited[start] = 1; 

    queue[tail++] = start; 

  

    printf("\nBFS (matrice) din nodul %d: ", start); 

  

    while (head < tail) { 

        int v = queue[head++]; 

        printf("%d ", v); 

  

        for (int w = 0; w < n; w++) { 

            if (A[v][w] == 1 && !visited[w]) { 

                visited[w] = 1; 

                queue[tail++] = w; 

            } 

        } 

    } 

    printf("\n"); 

} 

  

// 

// ===================== LISTE DE ADIACENȚĂ (DINAMICE) ===================== 

// 

  

typedef struct node { 

    int v; 

    struct node* next; 

} Node; 

  

Node* L[MAXN]; 

  

void initList() { 

    for (int i = 0; i < MAXN; i++) 

        L[i] = NULL; 

} 

  

void addEdge(int u, int v) { 

    Node* p = (Node*)malloc(sizeof(Node)); 

    p->v = v; 

    p->next = L[u]; 

    L[u] = p; 

} 

  

void readList(const char* filename) { 

    FILE* f = fopen(filename, "r"); 

    if (!f) { 

        printf("Nu pot deschide fisierul %s\n", filename); 

        exit(1); 

    } 

  

    fscanf(f, "%d", &n); 

    initList(); 

  

    int u, v; 

    while (fscanf(f, "%d %d", &u, &v) == 2) { 

        addEdge(u, v); 

        addEdge(v, u); // graf neorientat 

    } 

  

    fclose(f); 

} 

  

void printList() { 

    printf("\n=== LISTE DE ADIACENTA ===\n"); 

    for (int i = 0; i < n; i++) { 

        printf("%d: ", i); 

        Node* p = L[i]; 

        while (p) { 

            printf("%d -> ", p->v); 

            p = p->next; 

        } 

        printf("NULL\n"); 

    } 

} 

  

void BFS_list(int start) { 

    int visited[MAXN] = {0}; 

    int queue[MAXN], head = 0, tail = 0; 

  

    visited[start] = 1; 

    queue[tail++] = start; 

  

    printf("\nBFS (liste) din nodul %d: ", start); 

  

    while (head < tail) { 

        int v = queue[head++]; 

        printf("%d ", v); 

  

        for (Node* p = L[v]; p != NULL; p = p->next) { 

            int w = p->v; 

            if (!visited[w]) { 

                visited[w] = 1; 

                queue[tail++] = w; 

            } 

        } 

    } 

    printf("\n"); 

} 

  

// 

// ===================== MAIN ===================== 

// 

  

int main() { 

    printf("=== LABORATOR 7: GRAFURI + BFS ===\n"); 

  

    // 

    // TEST 1: MATRICE DE ADIACENȚĂ 

    // 

    readMatrix("graf_matrice.txt"); 

    printMatrix(); 

    BFS_matrix(0); 

  

    // 

    // TEST 2: LISTE DE ADIACENȚĂ 

    // 

    readList("graf_liste.txt"); 

    printList(); 

    BFS_list(0); 

  

    return 0; 

} 

 