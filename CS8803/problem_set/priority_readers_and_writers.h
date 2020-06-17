#ifndef PRIORITY_READERS_AND_WRITERS_H

#define PRIORITY_READERS_AND_WRITERS_H
int main(int argc, char** argv);
void* read_routine(void* thr_arg);
void* write_routine(void* thr_arg);

#endif
