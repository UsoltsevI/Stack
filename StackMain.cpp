#include "StackMain.h"

int main() {

    struct_stack stk = {};

    C(WHITE);

    stack_ctor(&stk);
    stack_push(&stk, 4);
    stack_push(&stk, 48);
    stack_push(&stk, 6);

    printf("%d\n", stack_pop(&stk));

    stack_dtor(&stk);

    return 0;
}
