#include <stdio.h>
#include <string.h>


int increment() {
    int count = 0;
    count++;
    return count;
}

typedef struct {
    char *name;
    int age;
} person;

struct cat {
    char * name;
    int age;
};

void add_one(int *n) {
    (*n)++;
}

void age_person(person *p) {
    p->age++;
}

int main() {
    person p;
    p.name = "Calvin";
    p.age = 27;

    struct cat momo;
    momo.name = "Momo";

    printf("%s\n", p.name);
    printf("%s\n", momo.name);

    int n = 10;
    add_one(&n);
    printf("what is n? %d\n", n);

    age_person(&p);
    printf("what is %s's age? %d\n", p.name, p.age);

    return 0;
}