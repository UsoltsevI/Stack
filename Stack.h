#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include "color.h"

typedef int Elent;

struct int_stack {

    Elent *data;
    size_t a;
    size_t copacity;
};

int stack_dump(int_stack *stk, char *line, char *file, char *func);
int stack_ok(int_stack *stk);
int stack_push(int_stack *stk, Elent value);
int stack_pop(int_stack *stk, Elent x);

#define stack_dump(stk) stack_dump(stk, __LINE__, __FILE__, __func__)

#endif // STACK_H_INCLUDED
