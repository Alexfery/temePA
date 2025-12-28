#include <stdio.h> 

#include <stdlib.h> 

  

#define MAXN 20 

  

// 

// =============================================================== 

// 1. PERMUTĂRI (1..n) 

// =============================================================== 

// 

  

int n; 

int x_perm[MAXN]; 

int used_perm[MAXN]; 

  

void print_perm() { 

    for (int i = 1; i <= n; i++) 

        printf("%d ", x_perm[i]); 

    printf("\n"); 

} 

  

void back_perm(int k) { 

    if (k > n) { 

        print_perm(); 

        return; 

    } 

  

    for (int v = 1; v <= n; v++) { 

        if (!used_perm[v]) { 

            used_perm[v] = 1; 

            x_perm[k] = v; 

  

            back_perm(k + 1); 

  

            used_perm[v] = 0; 

        } 

    } 

} 

  

// 

// =============================================================== 

// 2. COMBINĂRI C(n, k) 

// =============================================================== 

// 

  

int k_comb; 

int x_comb[MAXN]; 

  

void print_comb() { 

    for (int i = 1; i <= k_comb; i++) 

        printf("%d ", x_comb[i]); 

    printf("\n"); 

} 

  

void back_comb(int k, int start) { 

    if (k > k_comb) { 

        print_comb(); 

        return; 

    } 

  

    for (int v = start; v <= n; v++) { 

        x_comb[k] = v; 

        back_comb(k + 1, v + 1); 

    } 

} 

  

// 

// =============================================================== 

// 3. PROBLEMA N REGINE 

// =============================================================== 

// 

  

int nq; 

int x_queen[MAXN]; 

  

int valid_queen(int k) { 

    for (int i = 1; i < k; i++) { 

        if (x_queen[i] == x_queen[k]) return 0; 

        if (abs(x_queen[i] - x_queen[k]) == abs(i - k)) return 0; 

    } 

    return 1; 

} 

  

void print_queens() { 

    for (int i = 1; i <= nq; i++) 

        printf("%d ", x_queen[i]); 

    printf("\n"); 

} 

  

void back_queen(int k) { 

    if (k > nq) { 

        print_queens(); 

        return; 

    } 

  

    for (int col = 1; col <= nq; col++) { 

        x_queen[k] = col; 

        if (valid_queen(k)) 

            back_queen(k + 1); 

    } 

} 

  

// 

// =============================================================== 

// 4. PROBLEMA RESTULUI (COIN CHANGE) – soluție optimă 

// =============================================================== 

// 

  

int coins[MAXN]; 

int ncoins; 

int target; 

  

int x_coin[MAXN]; 

int best_coin[MAXN]; 

int best_count = 999999; 

  

int sum_coins(int k) { 

    int s = 0; 

    for (int i = 1; i <= k; i++) 

        if (x_coin[i] == 1) 

            s += coins[i]; 

    return s; 

} 

  

int count_coins(int k) { 

    int c = 0; 

    for (int i = 1; i <= k; i++) 

        if (x_coin[i] == 1) 

            c++; 

    return c; 

} 

  

void back_coin(int k) { 

    if (k > ncoins) { 

        int s = sum_coins(ncoins); 

        int c = count_coins(ncoins); 

  

        if (s == target && c < best_count) { 

            best_count = c; 

            for (int i = 1; i <= ncoins; i++) 

                best_coin[i] = x_coin[i]; 

        } 

        return; 

    } 

  

    // pruning: dacă deja avem mai multe monede decât soluția optimă 

    if (count_coins(k - 1) >= best_count) 

        return; 

  

    // alegem moneda k 

    x_coin[k] = 1; 

    if (sum_coins(k) <= target) 

        back_coin(k + 1); 

  

    // nu alegem moneda k 

    x_coin[k] = 0; 

    back_coin(k + 1); 

} 

  

void print_best_coin() { 

    printf("Soluția optimă (minim monede):\n"); 

    for (int i = 1; i <= ncoins; i++) 

        if (best_coin[i] == 1) 

            printf("%d ", coins[i]); 

    printf("\n"); 

} 

  

// 

// =============================================================== 

// MAIN 

// =============================================================== 

// 

  

int main() { 

    printf("=== LABORATOR 9: BACKTRACKING ===\n\n"); 

  

    // 

    // 1. PERMUTĂRI 

    // 

    printf("Permutari pentru n = 3:\n"); 

    n = 3; 

    back_perm(1); 

  

    // 

    // 2. COMBINĂRI 

    // 

    printf("\nCombinari C(5, 3):\n"); 

    n = 5; 

    k_comb = 3; 

    back_comb(1, 1); 

  

    // 

    // 3. N REGINE 

    // 

    printf("\nSolutii pentru 4 regine:\n"); 

    nq = 4; 

    back_queen(1); 

  

    // 

    // 4. PROBLEMA RESTULUI 

    // 

    printf("\nProblema restului:\n"); 

    ncoins = 6; 

    coins[1] = 10; 

    coins[2] = 10; 

    coins[3] = 5; 

    coins[4] = 20; 

    coins[5] = 5; 

    coins[6] = 5; 

  

    target = 30; 

  

    back_coin(1); 

    print_best_coin(); 

  

    return 0; 

} 

 