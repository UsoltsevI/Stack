#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include "color.h"

typedef int Elent;

struct struct_stack {

    Elent *data;
    size_t a;
    size_t copacity;
};

void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func);
int stack_ok(struct_stack *stk);
void stack_push(struct_stack *stk, Elent value);
Elent stack_pop(struct_stack *stk);
int stack_dtor(struct_stack *stk);

#define stack_dump(stk) stack_dump_d(stk, __LINE__, __FILE__, __func__)
#define check_error(a)  if (a) { \
                            result += rate; \
                        } \
                        rate *= 2;


#endif // STACK_H_INCLUDED
