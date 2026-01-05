#include <stdio.h> 

#include <stdlib.h> 

#include <string.h> 

  //

// 

// =============================================================== 

// 1. CĂUTARE BINARĂ (returnează poziția sau locul de inserare) 

// =============================================================== 

// 

  

int binary_search(int a[], int n, int key) { 

    int left = 0, right = n - 1, mid; 

  

    while (left <= right) { 

        mid = (left + right) / 2; 

  

        if (a[mid] == key) 

            return mid; 

  

        if (a[mid] < key) 

            left = mid + 1; 

        else 

            right = mid - 1; 

    } 

  

    // dacă nu există, returnăm poziția unde ar trebui inserat 

    return left; 

} 

  

// 

// =============================================================== 

// 2. SORTARE PRIN INTERCLASARE (MERGE SORT) 

// =============================================================== 

// 

  

void merge(int a[], int left, int mid, int right) { 

    int n1 = mid - left + 1; 

    int n2 = right - mid; 

  

    int* L = (int*)malloc(n1 * sizeof(int)); 

    int* R = (int*)malloc(n2 * sizeof(int)); 

  

    for (int i = 0; i < n1; i++) L[i] = a[left + i]; 

    for (int i = 0; i < n2; i++) R[i] = a[mid + 1 + i]; 

  

    int i = 0, j = 0, k = left; 

  

    while (i < n1 && j < n2) { 

        if (L[i] <= R[j]) 

            a[k++] = L[i++]; 

        else 

            a[k++] = R[j++]; 

    } 

  

    while (i < n1) a[k++] = L[i++]; 

    while (j < n2) a[k++] = R[j++]; 

  

    free(L); 

    free(R); 

} 

  

void merge_sort(int a[], int left, int right) { 

    if (left >= right) 

        return; 

  

    int mid = (left + right) / 2; 

  

    merge_sort(a, left, mid); 

    merge_sort(a, mid + 1, right); 

  

    merge(a, left, mid, right); 

} 

  

// 

// =============================================================== 

// 3. ÎNMULȚIREA KARATSUBA 

// =============================================================== 

// 

  

// Elimină zerourile din față 

void trim(char* s) { 

    int i = 0; 

    while (s[i] == '0' && s[i + 1] != '\0') 

        i++; 

    if (i > 0) 

        memmove(s, s + i, strlen(s) - i + 1); 

} 

  

// Adunare de numere mari 

void add(char* res, const char* a, const char* b) { 

    int la = strlen(a), lb = strlen(b); 

    int carry = 0, i = la - 1, j = lb - 1, k = 0; 

    char temp[10000]; 

  

    while (i >= 0 || j >= 0 || carry) { 

        int x = (i >= 0 ? a[i--] - '0' : 0); 

        int y = (j >= 0 ? b[j--] - '0' : 0); 

        int s = x + y + carry; 

        temp[k++] = (s % 10) + '0'; 

        carry = s / 10; 

    } 

  

    temp[k] = '\0'; 

  

    // inversăm rezultatul 

    for (int i = 0; i < k; i++) 

        res[i] = temp[k - 1 - i]; 

    res[k] = '\0'; 

} 

  

// Scădere de numere mari (a >= b) 

void subtract(char* res, const char* a, const char* b) { 

    int la = strlen(a), lb = strlen(b); 

    int borrow = 0, i = la - 1, j = lb - 1, k = 0; 

    char temp[10000]; 

  

    while (i >= 0) { 

        int x = a[i--] - '0'; 

        int y = (j >= 0 ? b[j--] - '0' : 0); 

        x -= borrow; 

  

        if (x < y) { 

            x += 10; 

            borrow = 1; 

        } else { 

            borrow = 0; 

        } 

  

        temp[k++] = (x - y) + '0'; 

    } 

  

    temp[k] = '\0'; 

  

    // inversăm rezultatul 

    for (int i = 0; i < k; i++) 

        res[i] = temp[k - 1 - i]; 

    res[k] = '\0'; 

  

    trim(res); 

} 

  

// Înmulțire clasică pentru numere mici 

void multiply_small(char* res, const char* a, const char* b) { 

    int la = strlen(a), lb = strlen(b); 

    int temp[10000] = {0}; 

  

    for (int i = la - 1; i >= 0; i--) { 

        for (int j = lb - 1; j >= 0; j--) { 

            temp[i + j + 1] += (a[i] - '0') * (b[j] - '0'); 

        } 

    } 

  

    for (int i = la + lb - 1; i > 0; i--) { 

        temp[i - 1] += temp[i] / 10; 

        temp[i] %= 10; 

    } 

  

    int k = 0; 

    int i = 0; 

    while (i < la + lb - 1 && temp[i] == 0) i++; 

  

    for (; i < la + lb; i++) 

        res[k++] = temp[i] + '0'; 

  

    res[k] = '\0'; 

} 

  

// Karatsuba 

void karatsuba(char* res, const char* x, const char* y) { 

    trim((char*)x); 

    trim((char*)y); 

  

    int n = strlen(x); 

    int m = strlen(y); 

  

    if (n < 10 || m < 10) { 

        multiply_small(res, x, y); 

        return; 

    } 

  

    int k = (n > m ? n : m) / 2; 

  

    char x1[10000], x0[10000], y1[10000], y0[10000]; 

    strcpy(x1, x); 

    strcpy(y1, y); 

  

    x1[n - k] = '\0'; 

    y1[m - k] = '\0'; 

  

    strcpy(x0, x + (n - k)); 

    strcpy(y0, y + (m - k)); 

  

    char z0[10000], z1[10000], z2[10000]; 

    char t1[10000], t2[10000]; 

  

    karatsuba(z0, x0, y0); 

    karatsuba(z2, x1, y1); 

  

    add(t1, x1, x0); 

    add(t2, y1, y0); 

  

    karatsuba(z1, t1, t2); 

  

    subtract(z1, z1, z2); 

    subtract(z1, z1, z0); 

  

    char temp[10000] = "0"; 

  

    // z2 * 10^(2k) 

    for (int i = 0; i < 2 * k; i++) 

        strcat(z2, "0"); 

  

    // z1 * 10^k 

    for (int i = 0; i < k; i++) 

        strcat(z1, "0"); 

  

    add(temp, z2, z1); 

    add(res, temp, z0); 

  

    trim(res); 

} 

  

// 

// =============================================================== 

// MAIN 

// =============================================================== 

// 

  

int main() { 

    printf("=== LABORATOR 11: DIVIDE ET IMPERA ===\n\n"); 

  

    // 

    // 1. CĂUTARE BINARĂ 

    // 

    int a[] = {1, 3, 5, 7, 9, 11}; 

    int pos = binary_search(a, 6, 8); 

    printf("Pozitia pentru 8 este: %d\n", pos); 

  

    // 

    // 2. MERGE SORT 

    // 

    int b[] = {38, 27, 43, 3, 9, 82, 10}; 

    int nb = 7; 

  

    merge_sort(b, 0, nb - 1); 

  

    printf("\nVector sortat: "); 

    for (int i = 0; i < nb; i++) 

        printf("%d ", b[i]); 

    printf("\n"); 

  

    // 

    // 3. KARATSUBA 

    // 

    char x[10000] = "123456789123456789"; 

    char y[10000] = "987654321987654321"; 

    char result[10000]; 

  

    karatsuba(result, x, y); 

  

    printf("\nKaratsuba:\n%s * %s =\n%s\n", x, y, result); 

  

    return 0; 

} 

 