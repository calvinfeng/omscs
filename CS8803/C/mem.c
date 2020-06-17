#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int age;
} Person;

Person *new_person(char *name, int age) {
    Person * p = malloc(sizeof(Person));
    p->name = name;
    p->age = age;

    return p;
}

int main() {
  int i;
  for (i = 0; i < 1000000000; i++) {
    Person *p = new_person("Calvin", 25);
    free(p);
  };

  return 0;
}