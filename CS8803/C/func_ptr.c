#include<stdio.h>
#include<stdlib.h>

// Void pointer has no associated type with it, it's like an interface{}. Const void means that this
// pointer is not meant to be modified.
int compare(const void* left, const void* right) {
    return (*(int*)right - *(int*)left);
}

int main() {
    int (*cmp) (const void*, const void*);
    cmp = &compare;

    int iarray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // We pass in the array, len, element size, and the comparison function.
    qsort(iarray, sizeof(iarray)/sizeof(*iarray), sizeof(*iarray), cmp);

    int c = 0;
    while (c < sizeof(iarray)/sizeof(*iarray)) {
        printf("%d\t", iarray[c]);
        c++;
    }

    printf("\n");
    return 0;
}