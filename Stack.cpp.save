#include "Stack.h"

void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func) {

    C(ORANGE);

    printf("At the file %s at the function %s at the line %d:\n\t{\n", file, func, line);

#ifdef debugon
    printf("\t struct_stack %s, defined in file %s in func %s at line %d:\n",
            stk->name_stk, stk->def_file_name, stk->def_func_name, stk->def_line);
#endif

    printf("\t copacity = %d\n", stk->copacity);
    printf("\t a = %d\n", stk->a);
    printf("\t data = %d\n", stk->data);
    printf("\t data[%p]:\n\t\t{\n", &stk->data);

    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t *[%d] = %d\n", i, stk->data[i]);

    printf("\t\t}\n\t}\n\n");

#ifdef debugon
    C(LBLUE);
    printf("But stk_c has following parameters:\n");

    printf("\t stk_c.copacity = %d\n", stk_c.copacity);
    printf("\t stk_c.a = %d\n", stk_c.a);
    printf("\t stk_c.data = %d\n", stk_c.data);
    printf("\t stk_c.data[%p]:\n\t\t{\n", &stk_c.data);

    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t stk_c.data[%d] = %d\n", i, stk_c.data[i]);

    printf("\t\t}\n\t}\n\n");
#endif

    C(WHITE);
}

int stack_ok(struct_stack *stk) {

    int result = 0;

    check_error(stk == NULL);

    check_error(stk->copacity < stk->a);

    check_error(stk->data == NULL);

    //result += (int) canary_check(stk, check_stk);

#ifdef debugon
    check_error(stk->def_line      != stk_c.def_line     );
    check_error(stk->def_file_name != stk_c.def_file_name);
    check_error(stk->def_func_name != stk_c.def_func_name);
    check_error(stk->name_stk      != stk_c.name_stk     );
    check_error(stk->a             != stk_c.a            );
    check_error(stk->copacity      != stk_c.copacity     );

    for (size_t i = 0; i < stk_c.copacity; i++)
        check_error(stk->data[i] != stk_c.data[i]);

    if (result != 0)
        printf("stack_ok failed\n");
#endif

    return result;
}

void stack_push(struct_stack *stk, Elent value) {

    if ((stk->copacity != 0) || (stk == NULL))
        if (stack_ok(stk)) {
            stack_dump(stk);
    }


    if (stk->a >= stk->copacity) {

        if (stk->copacity <= 0)
            stk->copacity = 1;

        stk->copacity = stk->copacity * 2;

        stk->data = (Elent *) realloc(stk->data, stk->copacity * sizeof(Elent));

        if (stk->data == NULL)
            printf("realloc failed if file %s in func %s at line %d\n",
                    __FILE__, __func__, __LINE__ - 4);
    }

    stk->data[stk->a++] = value;

#ifdef debugon
    create_copy_stack(stk);
    //stack_dump(stk);
    if (stack_ok(stk))
        stack_dump(stk);
#endif
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

#ifdef debugon
    create_copy_stack(stk);
#endif

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

int stack_copy(struct_stack *stk, struct_stack *stk_cpy) {

    if (stack_ok(stk))
        stack_dump(stk);

    stk_cpy->a = stk->a;
    stk_cpy->copacity = stk->copacity;
    stk_cpy->data = (Elent *) calloc(stk_cpy->copacity, sizeof(Elent));

    if (stk_cpy->data == NULL)
        return -1;

    for (size_t i = 0; i < stk_cpy->copacity; i++)
        stk_cpy->data[i] = stk->data[i];

    return 0;
}

#ifdef debugon
int stack_ctor_d(struct_stack *stk, const char *name_stk, const int line, const char *file, const char *func) {

    stk->name_stk = name_stk;
    stk->def_line = line;
    stk->def_file_name = file;
    stk->def_func_name = func;

    stk->data = (Elent *) calloc(2, sizeof(Elent));

    if (stk->data == NULL)
        return -1;

    stk->copacity = 2;
    stk->a = 0;

    create_copy_stack(stk);

    return 0;
}

int create_copy_stack(struct_stack *stk) {


    stk_c.name_stk      = stk->name_stk;
    stk_c.def_line      = stk->def_line;
    stk_c.def_file_name = stk->def_file_name;
    stk_c.def_func_name = stk->def_func_name;
    stk_c.a             = stk->a;
    stk_c.copacity      = stk->copacity;

    stk_c.data = (Elent *) calloc(stk_c.copacity, sizeof(Elent));

    if (stk_c.data == NULL)
        return -1;

    for (size_t i = 0; i < stk_c.copacity; i++)
        stk_c.data[i] = stk->data[i];

    return 0;
}
#endif
