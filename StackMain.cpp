#include "StackMain.h"

int main() {

    struct_stack stk = {};
    struct_stack stk1 = {};


    stack_ctor(&stk);
    stack_ctor(&stk1);
    stack_push(&stk, 4);
    stack_push(&stk, 48);
    stack_push(&stk, 6);


    stack_copy(&stk, &stk1);
    printf("%d\n", stack_pop(&stk));
    printf("%d\n", stack_pop(&stk));
    printf("%d\n", stack_pop(&stk));

    stack_push(&stk1, 123);
    printf("%d\n", stack_pop(&stk1));
    printf("%d\n", stack_pop(&stk1));
    printf("%d\n", stack_pop(&stk1));
    //printf("%d\n", stack_pop(&stk));


    stack_dtor(&stk);
    //stack_dtor(&stk);

    //stack_push(&stk, 6);

    return 0;
}
