#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define debugon  //detector for debug version

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
    Elent * *addres_data;
    bool is_dtor;
    bool is_ctor;

#endif

};

int stack_ok(struct_stack *stk);

void stack_push(struct_stack *stk, Elent value);

Elent stack_pop(struct_stack *stk);

int stack_dtor(struct_stack *stk);

int stack_copy(struct_stack *stk, struct_stack *stk_cpy);

#ifdef debugon
int stack_ctor_d(struct_stack *stk, const char *name_str, const int line , const char *file, const char *func);
#define stack_ctor(stk) stack_ctor_d(stk, #stk, __LINE__ , __FILE__, __func__);
#endif

#define check_error(a)  if (a) { \
                            result += 1; \
                        } \

#endif // STACK_H_INCLUDED
