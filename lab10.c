#include <stdio.h> 

#include <stdlib.h> 

  

#define MAXN 100 

  

// 

// =============================================================== 

// 1. DESCOMPUNERE SUMĂ ÎN BANCNOTE (sistem canonic) 

// =============================================================== 

// 

  

int notes[] = {500, 200, 100, 50, 10, 5, 1}; 

int n_notes = 7; 

  

void greedy_change(int x) { 

    printf("Descompunerea sumei %d:\n", x); 

    for (int i = 0; i < n_notes; i++) { 

        while (x >= notes[i]) { 

            printf("%d ", notes[i]); 

            x -= notes[i]; 

        } 

    } 

    printf("\n"); 

} 

  

// 

// =============================================================== 

// 2. SELECTIA ACTIVITATILOR (interval scheduling) 

// =============================================================== 

// 

  

typedef struct { 

    int start, finish; 

} Activity; 

  

int cmp_activity(const void* a, const void* b) { 

    Activity* x = (Activity*)a; 

    Activity* y = (Activity*)b; 

    return x->finish - y->finish; 

} 

  

void greedy_activities(Activity A[], int n) { 

    qsort(A, n, sizeof(Activity), cmp_activity); 

  

    printf("Activitati selectate:\n"); 

  

    int last = 0; 

    printf("[%d, %d] ", A[0].start, A[0].finish); 

  

    for (int i = 1; i < n; i++) { 

        if (A[i].start >= A[last].finish) { 

            printf("[%d, %d] ", A[i].start, A[i].finish); 

            last = i; 

        } 

    } 

    printf("\n"); 

} 

  

// 

// =============================================================== 

// 3. CONVERSIE NUMĂR ÎN BAZA b 

// =============================================================== 

// 

  

void greedy_convert(long long x, int b) { 

    printf("Reprezentarea lui %lld în baza %d: ", x, b); 

  

    int digits[100]; 

    int k = 0; 

  

    while (x > 0) { 

        digits[k++] = x % b; 

        x /= b; 

    } 

  

    for (int i = k - 1; i >= 0; i--) 

        printf("%d", digits[i]); 

  

    printf("\n"); 

} 

  

// 

// =============================================================== 

// 4. PROBLEMA BUCĂȚILOR (optimal merge pattern) 

// =============================================================== 

// 

  

int cmp_int(const void* a, const void* b) { 

    return (*(int*)a) - (*(int*)b); 

} 

  

int greedy_merge(int a[], int n) { 

    int cost = 0; 

  

    while (n > 1) { 

        qsort(a, n, sizeof(int), cmp_int); 

  

        int x = a[0]; 

        int y = a[1]; 

        int merged = x + y; 

  

        cost += merged; 

  

        a[0] = merged; 

        for (int i = 1; i < n - 1; i++) 

            a[i] = a[i + 1]; 

  

        n--; 

    } 

  

    return cost; 

} 

  

// 

// =============================================================== 

// MAIN 

// =============================================================== 

// 

  

int main() { 

    printf("=== LABORATOR 10: GREEDY ===\n\n"); 

  

    // 

    // 1. DESCOMPUNERE SUMĂ 

    // 

    greedy_change(786); 

  

    // 

    // 2. SELECTIA ACTIVITATILOR 

    // 

    Activity A[] = { 

        {1, 4}, {3, 5}, {0, 6}, {5, 7}, 

        {3, 9}, {5, 9}, {6, 10}, {8, 11}, 

        {8, 12}, {2, 14}, {12, 16} 

    }; 

    int nA = sizeof(A) / sizeof(A[0]); 

  

    printf("\nSelectia activitatilor:\n"); 

    greedy_activities(A, nA); 

  

    // 

    // 3. CONVERSIE NUMĂR ÎN BAZA b 

    // 

    printf("\nConversie numar:\n"); 

    greedy_convert(123456, 7); 

  

    // 

    // 4. PROBLEMA BUCĂȚILOR 

    // 

    int pieces[] = {1, 1, 4}; 

    int np = 3; 

  

    printf("\nCostul optim de imbinare: %d\n", greedy_merge(pieces, np)); 

  

    return 0; 

} 

 