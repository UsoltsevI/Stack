#include "Stack.h"

int main() {

    return 0;
}

int stack_dump(int_stack *stk, char *line, char *file, char *func) {

    printf("copacity = %d\n", stk->copacity);
    printf("a = %d\n", stk->a);

    printf("data[%d]:\n\t{\n", &stk->data);
    C(GREY);
    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t*[%d] = %d\n", i, stk->data[i]);
    C(WHITE);
    printf("\t}\n}\n");
}

int stack_ok(int_stack *stk) {

    int result = 0, rate = 1;

    C(RED);

    if (stk == NULL) {
        result += rate;
        printf("stk == NULL");
    }

    C(WHITE);

    return result;
}

int stack_push(int_stack *stk, Elent value) {

    if (stack_ok(stk))
        stack_dumb(&stk);

    if (stk->a >= stk->copacity) {

        stk->copasuty = stk->copasity * 2;

        stk->data = (Elent *) realloc(stk->data, str->copasity * sizeof(Elent));
    }

    str->data[str->a++] = value;
}

int stack_pop(int_stack *stk, Elent x) {

    if (stack_ok(&stk))
        stack_dumb(&stk);

    if (stk->a < stk->copacity / 2) {

        stk->copacity = stk->copacity / 2;

        free(stk->data + stk->copacity);
    }

    stk->data[--stk->a] = NULL;

    return stk->data[stk->a];
}

