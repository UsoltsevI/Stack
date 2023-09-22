#include "Stack.h"

void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func) {

    C(ORANGE);

    printf("At the file %s at the function %s at the line %d:\n\t{\n", file, func, line);

    printf("\t copacity = %d\n", stk->copacity);
    printf("\t a = %d\n", stk->a);
    printf("\t data = %d\n", stk->data);
    printf("\t data[%p]:\n\t\t{\n", &stk->data);

    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t *[%d] = %d\n", i, stk->data[i]);

    printf("\t\t}\n\t}\n\n");

    C(WHITE);
}

int stack_ok(struct_stack *stk) {

    int result = 0, rate = 1;

    check_error(stk == NULL);

    //check_error(stk->copacity < 0);

    //check_error(stk->a < 0);

    check_error(stk->copacity < stk->a);

    check_error(stk->data == NULL);

    return result;
}

void stack_push(struct_stack *stk, Elent value) {

    if ((stk->copacity != 0) || (stk == NULL))
        if (stack_ok(stk))
            stack_dump(stk);

    if (stk->a >= stk->copacity) {

        if (stk->copacity <= 0)
            stk->copacity = 1;

        stk->copacity = stk->copacity * 2;

        stk->data = (Elent *) realloc(stk->data, stk->copacity * sizeof(Elent));

        if (stk->data == NULL)
            printf("realloc failed if file %s in func %s at line %d\n",
                    __FILE__, __func__, __LINE__ - 4);
    }

    if (stack_ok(stk))
        stack_dump(stk);

    stk->data[stk->a++] = value;
}

Elent stack_pop(struct_stack *stk) {

    if (stack_ok(stk))
        stack_dump(stk);

    if (stk->a < stk->copacity / 2) {

        stk->copacity = stk->copacity / 2;

        free(stk->data + stk->copacity);
    }

    Elent result = 0;

    if (stk->a > 0) {
        result = stk->data[--stk->a];
        stk->data[stk->a] = 0;

    } else {
        result = stk->data[stk->a];
        stk->data[stk->a] = 0;
    }

    return result;
}

int stack_dtor(struct_stack *stk) {

    if (stk == NULL)
        return -1;

    free(stk->data);
    stk->data = 0;
    stk->copacity = 0;
    stk->a = 0;

    return 0;
}
