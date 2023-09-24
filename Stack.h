#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "color.h"

#define debugon

typedef int Elent;

struct struct_stack {

    Elent *data;
    size_t a;
    size_t copacity;

#ifdef debugon
    int def_line;
    const char *name_stk;
    const char *def_file_name;
    const char *def_func_name;
#endif
};


void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func);

int stack_ok(struct_stack *stk);

void stack_push(struct_stack *stk, Elent value);

Elent stack_pop(struct_stack *stk);

int stack_dtor(struct_stack *stk);

#ifdef debugon
int stack_ctor_d(struct_stack *stk, const char *name_str, const int line , const char *file, const char *func);
int create_copy_stack(struct_stack *stk);

static struct struct_stack stk_c = {};
#endif

#define stack_dump(stk) stack_dump_d(stk, __LINE__, __FILE__, __func__)
#define stack_ctor(stk) stack_ctor_d(stk, #stk, __LINE__ , __FILE__, __func__)
#define check_error(a)  if (a) { \
                            result += 1; \
                        } \


#endif // STACK_H_INCLUDED
