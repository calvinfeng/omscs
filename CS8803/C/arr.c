#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void allocate_mem_for_arr() {
  char vowels[] = {'a', 'e', 'i', 'o', 'u'};
  char *pvowels = &vowels;

  int i;
  for (i = 0; i < 5; i++) {
    printf("&vowels[%d]: %u, pvowels + %d: %u, vowels + %d: %u\n", i, &vowels[i], i, pvowels+i, i, vowels +i);
  }
}

int main() {
  int nrows = 3;
  int ncols = 3;

  char **pvowels = (char **) malloc(nrows * sizeof(char *));

  int i, j;
  for (i = 0; i < nrows; i++) {
    pvowels[i] = (char *) malloc(ncols * sizeof(char));
    for (j = 0; j < ncols; j++) {
        pvowels[i][j] = 'a';
    }
  }

  for (i = 0; i < nrows; i++) {
    for (j = 0; j < ncols; j++) {
      printf("%c\n", pvowels[i][j]);
    }
  }
}