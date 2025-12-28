#include <stdio.h> 

#include <stdlib.h> 

  

#define MAXN 100 

  

// ===================== LISTE DE ADIACENȚĂ ===================== 

  

typedef struct node { 

    int v; 

    struct node* next; 

} Node; 

  

Node* L[MAXN]; 

int n; 

  

// ===================== INITIALIZARE ===================== 

  

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

  

// ===================== CITIRE GRAF ===================== 

  

void readGraph(const char* filename) { 

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

  

void printGraph() { 

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

  

// ===================== DFS ITERATIV ===================== 

  

enum { WHITE, GRAY, BLACK }; 

  

int TT_iter[MAXN]; // arbore DFS 

  

void DFS_iterative(int start) { 

    int color[MAXN]; 

    for (int i = 0; i < n; i++) { 

        color[i] = WHITE; 

        TT_iter[i] = -1; 

    } 

  

    int stack[MAXN], top = -1; 

  

    stack[++top] = start; 

  

    printf("\nDFS ITERATIV din %d: ", start); 

  

    while (top >= 0) { 

        int v = stack[top--]; 

  

        if (color[v] == WHITE) { 

            color[v] = GRAY; 

            printf("%d ", v); 

  

            // parcurgem vecinii în ordinea în care apar în listă 

            for (Node* p = L[v]; p != NULL; p = p->next) { 

                int w = p->v; 

                if (color[w] == WHITE) { 

                    TT_iter[w] = v; 

                    stack[++top] = w; 

                } 

            } 

  

            color[v] = BLACK; 

        } 

    } 

    printf("\n"); 

} 

  

// ===================== DFS RECURSIV ===================== 

  

int colorR[MAXN]; 

int TT_rec[MAXN]; 

int d[MAXN], f[MAXN]; 

int timp; 

  

void DFS_visit(int v) { 

    timp++; 

    d[v] = timp; 

    colorR[v] = GRAY; 

  

    printf("%d ", v); 

  

    for (Node* p = L[v]; p != NULL; p = p->next) { 

        int w = p->v; 

        if (colorR[w] == WHITE) { 

            TT_rec[w] = v; 

            DFS_visit(w); 

        } 

    } 

  

    colorR[v] = BLACK; 

    timp++; 

    f[v] = timp; 

} 

  

void DFS_recursive(int start) { 

    for (int i = 0; i < n; i++) { 

        colorR[i] = WHITE; 

        TT_rec[i] = -1; 

        d[i] = f[i] = 0; 

    } 

    timp = 0; 

  

    printf("\nDFS RECURSIV din %d: ", start); 

    DFS_visit(start); 

    printf("\n"); 

} 

  

// ===================== MAIN ===================== 

  

int main() { 

    printf("=== LABORATOR 8: DFS ITERATIV + RECURSIV ===\n"); 

  

    readGraph("graf8.txt"); 

    printGraph(); 

  

    DFS_iterative(0); 

  

    DFS_recursive(0); 

  

    printf("\nTimpii DFS (recursiv):\n"); 

    for (int i = 0; i < n; i++) 

        printf("Nod %d: d=%d f=%d\n", i, d[i], f[i]); 

  

    printf("\nArbore DFS (recursiv):\n"); 

    for (int i = 0; i < n; i++) 

        printf("Parinte[%d] = %d\n", i, TT_rec[i]); 

  

    return 0; 

} 

 