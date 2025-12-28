Lab4:

#include <stdio.h>

#include <stdlib.h>



typedef struct node_type {

    int id;

    struct node_type* left;

    struct node_type* right;

} NodeT;



// ================== CREARE ARBORE DIN FIȘIER ==================



NodeT* createBinTreeFromFile(FILE* f) {

    int c;

    if (fscanf(f, "%d", &c) != 1) {

        return NULL; // sfârșit de fișier sau eroare

    }



    if (c == 0) {

        return NULL; // arbore vid pe această ramură

    }



    NodeT* p = (NodeT*)malloc(sizeof(NodeT));

    if (p == NULL) {

        fprintf(stderr, "Nu mai avem memorie in createBinTreeFromFile\n");

        exit(EXIT_FAILURE);

    }



    p->id = c;

    p->left = createBinTreeFromFile(f);

    p->right = createBinTreeFromFile(f);



    return p;

}



// ================== PARCURGERI ==================



void preorder(NodeT* p) {

    if (p != NULL) {

        printf("%d ", p->id);

        preorder(p->left);

        preorder(p->right);

    }

}



void inorder(NodeT* p) {

    if (p != NULL) {

        inorder(p->left);

        printf("%d ", p->id);

        inorder(p->right);

    }

}



void postorder(NodeT* p) {

    if (p != NULL) {

        postorder(p->left);

        postorder(p->right);

        printf("%d ", p->id);

    }

}



// ================== FRUNZE ==================



int countLeaves(NodeT* node) {

    if (node == NULL)

        return 0;

    if (node->left == NULL && node->right == NULL)

        return 1;

    return countLeaves(node->left) + countLeaves(node->right);

}



void printLeaves(NodeT* node) {

    if (node == NULL)

        return;

    if (node->left == NULL && node->right == NULL) {

        printf("%d ", node->id);

        return;

    }

    printLeaves(node->left);

    printLeaves(node->right);

}



// ================== NODURI INTERNE ==================



int countInternalNodes(NodeT* node) {

    if (node == NULL)

        return 0;

    if (node->left == NULL && node->right == NULL)

        return 0; // frunză, nu intern

    return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);

}



// ================== ÎNĂLȚIME ARBORE / NOD ==================



int height(NodeT* node) {

    if (node == NULL)

        return -1; // convenție din laborator

    int hl = height(node->left);

    int hr = height(node->right);

    return 1 + (hl > hr ? hl : hr);

}



// ================== CĂUTARE NOD DUPĂ CHEIE ==================



NodeT* search(NodeT* root, int key) {

    if (root == NULL)

        return NULL;

    if (root->id == key)

        return root;

    NodeT* leftResult = search(root->left, key);

    if (leftResult != NULL)

        return leftResult;

    return search(root->right, key);

}



// ================== ELIBERARE MEMORIE ==================



void freeTree(NodeT* root) {

    if (root == NULL)

        return;

    freeTree(root->left);

    freeTree(root->right);

    free(root);

}



// ================== MAIN ==================



int main(void) {

    FILE* f = fopen("ArboreBinar.txt", "r");

    if (!f) {

        printf("Nu se poate deschide fisierul ArboreBinar.txt\n");

        return -1;

    }



    NodeT* root = createBinTreeFromFile(f);

    fclose(f);



    if (root == NULL) {

        printf("Arbore vid sau fisier invalid.\n");

        return 0;

    }



    printf("=== LAB4: ARBORI BINARI ===\n\n");



    printf("Parcurgere PREORDINE:   ");

    preorder(root);

    printf("\n");



    printf("Parcurgere INORDINE:    ");

    inorder(root);

    printf("\n");



    printf("Parcurgere POSTORDINE:  ");

    postorder(root);

    printf("\n\n");



    int leaves = countLeaves(root);

    int internals = countInternalNodes(root);

    int h = height(root);



    printf("Numar frunze: %d\n", leaves);

    printf("Frunzele:     ");

    printLeaves(root);

    printf("\n");



    printf("Numar noduri interne: %d\n", internals);

    printf("Inaltime arbore:      %d\n\n", h);



    int key;

    printf("Introdu o cheie pentru cautare: ");

    if (scanf("%d", &key) == 1) {

        NodeT* found = search(root, key);

        if (found) {

            int hNode = height(found);

            printf("Cheia %d a fost gasita.\n", key);

            printf("Inaltimea nodului (subarborele radacinat in acest nod): %d\n", hNode);

        } else {

            printf("Cheia %d NU a fost gasita in arbore.\n", key);

        }

    } else {

        printf("Input invalid.\n");

    }



    freeTree(root);

    return 0;

}

