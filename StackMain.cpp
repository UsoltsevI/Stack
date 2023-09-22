#include "StackMain.h"

int main() {

    struct_stack stk = {};

    stack_push(&stk, 4);
    stack_push(&stk, 48);
    stack_push(&stk, 6);

    stack_dump(&stk);

    printf("%d\n", stack_pop(&stk));

    stack_dtor(&stk);
    stack_dump(&stk);

    return 0;
}
