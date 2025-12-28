#include <stdio.h> 

#include <stdlib.h> 

  

typedef struct node { 

    int key; 

    struct node* left; 

    struct node* right; 

} NodeT; 

  

// ===================== CREARE NOD ===================== 

  

NodeT* createNode(int key) { 

    NodeT* p = (NodeT*)malloc(sizeof(NodeT)); 

    p->key = key; 

    p->left = p->right = NULL; 

    return p; 

} 

  

// ===================== INSERARE NERECURSIVĂ ===================== 

  

NodeT* insertNode(NodeT* root, int key) { 

    NodeT* p = createNode(key); 

  

    if (root == NULL) 

        return p; 

  

    NodeT* parent = NULL; 

    NodeT* current = root; 

  

    while (current != NULL) { 

        parent = current; 

        if (key < current->key) 

            current = current->left; 

        else if (key > current->key) 

            current = current->right; 

        else { 

            free(p); // cheie duplicată 

            return root; 

        } 

    } 

  

    if (key < parent->key) 

        parent->left = p; 

    else 

        parent->right = p; 

  

    return root; 

} 

  

// ===================== CĂUTARE ===================== 

  

NodeT* searchKey(NodeT* root, int key) { 

    while (root != NULL) { 

        if (key == root->key) 

            return root; 

        else if (key < root->key) 

            root = root->left; 

        else 

            root = root->right; 

    } 

    return NULL; 

} 

  

// ===================== TRAVERSĂRI ===================== 

  

void inOrder(NodeT* p) { 

    if (p != NULL) { 

        inOrder(p->left); 

        printf("%d ", p->key); 

        inOrder(p->right); 

    } 

} 

  

void preOrder(NodeT* p) { 

    if (p != NULL) { 

        printf("%d ", p->key); 

        preOrder(p->left); 

        preOrder(p->right); 

    } 

} 

  

void postOrder(NodeT* p) { 

    if (p != NULL) { 

        postOrder(p->left); 

        postOrder(p->right); 

        printf("%d ", p->key); 

    } 

} 

  

// ===================== MINIM / MAXIM ===================== 

  

NodeT* findMin(NodeT* node) { 

    if (node == NULL) return NULL; 

    while (node->left != NULL) 

        node = node->left; 

    return node; 

} 

  

NodeT* findMax(NodeT* node) { 

    if (node == NULL) return NULL; 

    while (node->right != NULL) 

        node = node->right; 

    return node; 

} 

  

// ===================== SUCCESOR ===================== 

  

NodeT* succesor(NodeT* root, NodeT* node) { 

    if (node->right != NULL) 

        return findMin(node->right); 

  

    NodeT* succ = NULL; 

    NodeT* current = root; 

  

    while (current != NULL) { 

        if (node->key < current->key) { 

            succ = current; 

            current = current->left; 

        } else if (node->key > current->key) { 

            current = current->right; 

        } else break; 

    } 

    return succ; 

} 

  

// ===================== PREDECESOR ===================== 

  

NodeT* predecesor(NodeT* root, NodeT* node) { 

    if (node->left != NULL) 

        return findMax(node->left); 

  

    NodeT* pred = NULL; 

    NodeT* current = root; 

  

    while (current != NULL) { 

        if (node->key > current->key) { 

            pred = current; 

            current = current->right; 

        } else if (node->key < current->key) { 

            current = current->left; 

        } else break; 

    } 

    return pred; 

} 

  

// ===================== ȘTERGERE ===================== 

  

NodeT* deleteNode(NodeT* root, int key) { 

    if (root == NULL) 

        return root; 

  

    if (key < root->key) 

        root->left = deleteNode(root->left, key); 

    else if (key > root->key) 

        root->right = deleteNode(root->right, key); 

    else { 

        // 1. Fără copii 

        if (root->left == NULL && root->right == NULL) { 

            free(root); 

            return NULL; 

        } 

        // 2. Un copil 

        else if (root->left == NULL) { 

            NodeT* temp = root->right; 

            free(root); 

            return temp; 

        } 

        else if (root->right == NULL) { 

            NodeT* temp = root->left; 

            free(root); 

            return temp; 

        } 

        // 3. Doi copii 

        NodeT* temp = findMin(root->right); 

        root->key = temp->key; 

        root->right = deleteNode(root->right, temp->key); 

    } 

    return root; 

} 

  

// ===================== ELIBERARE MEMORIE ===================== 

  

void freeTree(NodeT* root) { 

    if (root == NULL) return; 

    freeTree(root->left); 

    freeTree(root->right); 

    free(root); 

} 

  

// ===================== MAIN ===================== 

  

int main() { 

    NodeT* root = NULL; 

  

    printf("=== LABORATOR 5: ARBORI BINARI DE CAUTARE ===\n\n"); 

  

    int values[] = {15, 6, 18, 20, 17, 7, 13, 3, 2, 4, 9}; 

    int n = sizeof(values) / sizeof(values[0]); 

  

    printf("Inserare valori: "); 

    for (int i = 0; i < n; i++) { 

        printf("%d ", values[i]); 

        root = insertNode(root, values[i]); 

    } 

    printf("\n\n"); 

  

    printf("Inordine:   "); 

    inOrder(root); 

    printf("\n"); 

  

    printf("Preordine:  "); 

    preOrder(root); 

    printf("\n"); 

  

    printf("Postordine: "); 

    postOrder(root); 

    printf("\n\n"); 

  

    printf("Minim: %d\n", findMin(root)->key); 

    printf("Maxim: %d\n\n", findMax(root)->key); 

  

    int key = 13; 

    NodeT* node = searchKey(root, key); 

    if (node) { 

        NodeT* s = succesor(root, node); 

        NodeT* p = predecesor(root, node); 

        printf("Succesor(%d) = %d\n", key, s ? s->key : -1); 

        printf("Predecesor(%d) = %d\n\n", key, p ? p->key : -1); 

    } 

  

    printf("Stergere nod 6...\n"); 

    root = deleteNode(root, 6); 

    printf("Inordine dupa stergere: "); 

    inOrder(root); 

    printf("\n"); 

  

    freeTree(root); 

    return 0; 

} 

 