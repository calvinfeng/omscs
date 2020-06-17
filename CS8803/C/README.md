# C

## Data Types

### Primitive

* `char`
* `int`
* `short`
* `long`
* `long long`

C does not have boolean type. We must fake it with 0 and 1.

```c
#define BOOL char

#define FALSE 0

#define TRUE 1
```

### Array

There are no dynamic array. Every array has fixed size.

```c
int numbers[10];

numbers[0] = 1;
numbers[1] = 2;
...
```

However, it can still be multi-dimensional.

```c
int matrix[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
}
```

### Strings

Strings are actually arrays of characters, i.e. arrays of integers.

```c
// Read-only string using pointer
char * name = "Calvin Feng";

// Write-able string
char name[] = "Calvin Feng;
```

Just like Go, we can do string format with `printf`.

```c
char * name = "Calvin Feng";
int age = 27;

printf("%s is %d years old.\n", name, age);
```

String length

```c
strlen(name);
```

String comparison `strncmp` compares two strings and return 0 if they are equal. The last argument
specifies how many characters to compare.

```c
if (strncmp(name, "Calvin", 4) == 0) {
    // logic
}
```

String concatenation `strncat` appends first n characters of src string to dest string.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[5]="Hello";
    char src[5]="World";
    strncat(dest,src,5);
    printf("%s\n",dest);
    strncat(dest,src,5);
    printf("%s\n",dest);
    return 0;
}
```

## Conditionals

Just like any other language.

```c
int foo = 1;
int bar = 2;

if (foo < bar) {
    do_something();
}
```

## Loops

For for-loop, we have to declare the index first.

```c
int i;
for (i = 0; i < 10; i++) {
    printf("%d\n", i)
}
```

Since there is no boolean, 0 means false for while loop and 1 means true for while loop.

```c
while (1) {
    // Run infinitely
}
```

## Functions

* Function receive either a fixed or variable amount of arguments.
* Function can only return one value or return no value.

```c
int foo(int bar) {
    return bar * 2;
}

void nothing(int foo) {
    // do something
}
```

## Static

Variables can declared as static to increase their scope up to file containing them.

```c
#include<stdio.h>
int increment()
{
    static int count = 0;
    count++;
    return count;
}

int main()
{
    printf("%d ", increment());
    printf("%d ", increment());
    return 0;
}
```

However, functions are global by default and declaring a function to be static means that its scope
is reduced to the file containing it.

```c
static void fun(void) {
    printf("I am static\n");
}
```

## Pointers

```c
char * name = "Calvin"
```

It does three things.

1. It allocates a local statck variable called `name` which is a pointer to a single character.
2. It causes the string "Calvin" to appear somewhere in the program memory.
3. It initializes the `name` argument to point to where the C character resides at.

Pointer deferencing is the same as Go.

```c
int val = 1;
int * ptr_to_val = &val;

printf("The memory value is %p\n", ptr_to_val);
printf("The actual value is %d\n", *ptr_to_val);
```

## Structs

Similar to that of Go.

```c
struct point {
    int x;
    int y;
}

struct point p;
p.x = 10;
p.y = 10;
```

We can make the expression cleaner using `typedefs` which will enable us to get rid of the `struct`.

```c
typedef struct {
    char * name;
    int age;
} cat;

cat momo;
momo.name = "Momo";
momo.age = 7;
```

## Pass by Reference

This is same as Go.

```c
void add_one(int n) {
    n++;
}

void add_one(int *n) {
    (*n)++;
}
```

Pass a struct by reference.

```c
void move(point *p) {
    (*p).x++;
    (*p).y++;
}
```

However, if we want to dereference a struct and access one of its internal members, we have a shorthand
syntax for that.

```c
void move(point *p) {
    p->x++;
    p->y++;
}
```

## Dynamic Allocation

Allocating memory dynamically helps us to store data without initially knowing the size of the
data in the time we wrote the program.

To allocate a chunk of memory dynamically, we have to have a pointer ready to store the location of
the newly allocated memory. We can access memory that was allocated to us using the same pointer,
and we can use that pointer to free the memory again.

```c
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
```

What if I don't free it up? My program will crash!

```c
int main() {
  int i;
  for (i = 0; i < 1000000000; i++) {
    Person *p = new_person("Calvin", 25);
    free(p)
  }

  return 0;
}
```

## Pointer to Array

We can also create pointers to arrays!

```c
int main() {
  char vowels[] = {'a', 'e', 'i', 'o', 'u'};
  char *pvowels = &vowels;

  int i;
  for (i = 0; i < 5; i++) {
    printf("&vowels[%d]: %u, pvowels + %d: %u, vowels + %d: %u\n", i, &vowels[i], i, pvowels+i, i, vowels +i);
  }
}
```

We can dynamically allocate contiguous memory using block pointers.

```c
// Allocate memory to store five characters
int n = 5;
char *pvowels = (char *) malloc(n * sizeof(char));

int i;
for (i = 0; i < 5; i++) {
    pvowels[i] = 'a';
}
```

Let's try two dimensional array.

```c
int nrows = 3;
int ncols = 3;

char **pvowels = (char **) malloc(nrows * sizeof(char *));

int i, j
for (i = 0; i < nrows; i++) {
    pvowels[i] = (char *) malloc(ncols * sizeof(char));
    for (j = 0; j < ncols; j++) {
        pvowels[i][j] = 'a';
    }
}
```

## Function Pointers

When we want to pass a function into another function, we must use a pointer to a function.

```c
void (*pf)(int);
```

The `*pf` is a pointer to a function and `void` is the return type of that function, while `int` is 
the argument that we supply to the function.

We can do something crazier like...

```c
char* (*pf)(int*);
```

`*char` is the return type of the function and `int*` is the argument type to the function.

```c
#include <stdio.h>

void some_func(int arg) {
    printf("this is some_func being called and arg is %d\n", arg);
}

int main() {
    void (*pf)(int);
    pf = &some_func;
    prinf("about to call some_func via pointer\n");
    (pf)(5);
}
```

Let's put it to practical usage.

```c
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

    return 0;
}
```