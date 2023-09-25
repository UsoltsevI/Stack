#include "Stack.h"

#ifdef debugon

static void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func);
static int create_check_stack(struct_stack *stk);
static int stack_str_cmp(const char * s1, const char *s2);

struct struct_stack *stk_c = {};
static char * *stk_c_name = {};
static size_t num_stk_c = 0;

#define stack_dump(stk) stack_dump_d(stk, __LINE__, __FILE__, __func__);

#endif

#ifdef debugon

static void stack_dump_d(struct_stack *stk, int line, const char *file, const char *func) {

    C(ORANGE);
    printf("At the file %s at the function %s at the line %d:\n\t{\n", file, func, line);

    printf("\t struct_stack %s, defined in file %s in func %s at line %d:\n",
            stk->name_stk, stk->def_file_name, stk->def_func_name, stk->def_line);

    printf("\t copacity = %d\n",     stk->copacity);
    printf("\t a = %d\n",            stk->a);
    printf("\t data = %d\n",         stk->data);
    printf("\t data[%p]:\n\t\t{\n", &stk->data);

    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t *[%d] = %d\n", i, stk->data[i]);

    printf("\t\t}\n\t}\n\n");

    int check = -1;

    for (int i = 0; i < num_stk_c; i++) {
        if (stack_str_cmp(stk_c_name[i], stk->name_stk) == 0) {
            check = i;
            break;
        }
    }

    if (check == -1) {

        printf("check == -1 at line %d in func %s in file %s\n", __LINE__, __func__, __FILE__);
        printf("stk->name_stk = %s\n", stk->name_stk);

        for (int i = 0; i < num_stk_c; i++)
            printf("stk_c_name[%d] = %s\n", i, stk_c_name[i]);
    }

    C(LBLUE);
    printf("But stk_c has following parameters:\n");

    printf("\t stk_c[%d].copacity = %d\n",    check,  stk_c[check].copacity);
    printf("\t stk_c[%d].a = %d\n",           check,  stk_c[check].a);
    printf("\t stk_c[%d].data = %d\n",        check,  stk_c[check].data);
    printf("\t stk_c[%d].data[%p]:\n\t\t{\n", check, &stk_c[check].data);

    for (size_t i = 0; i < stk->copacity; i++)
        printf("\t\t stk_c[%d].data[%d] = %d\n", check, i, stk_c[check].data[i]);

    printf("\t\t}\n\t}\n\n");

    C(WHITE);
}

#endif

int stack_ok(struct_stack *stk) {

    int result = 0;

    check_error(stk == NULL);
    check_error(stk->data == NULL);
    check_error(stk->a > stk->copacity);

#ifdef debugon

    int check = -1;

    for (int i = 0; i < num_stk_c; i++) {
        if (stack_str_cmp(stk_c_name[i], stk->name_stk) == 0) {
            check = i;
            break;
        }
    }

    if (check == -1) {
        printf("check == -1 at line %d in func %s in file %s\n", __LINE__, __func__, __FILE__);
        printf("stk->name_stk = %s\n", stk->name_stk);

        for (int i = 0; i < num_stk_c; i++)
            printf("stk_c_name[%d] = %s\n", i, stk_c_name[i]);
    }

    check_error(stk->def_line      != stk_c[check].def_line     );
    check_error(stk->def_file_name != stk_c[check].def_file_name);
    check_error(stk->def_func_name != stk_c[check].def_func_name);
    check_error(stk->name_stk      != stk_c[check].name_stk     );
    check_error(stk->a             != stk_c[check].a            );
    check_error(stk->copacity      != stk_c[check].copacity     );

    for (size_t i = 0; i < stk->copacity; i++)
        check_error(stk->data[i] != stk_c[check].data[i]);

    if (result != 0)
        printf("stack_ok failed\n");

#endif

    return result;
}

void stack_push(struct_stack *stk, Elent value) {

#ifdef debugon
    if ((stk->copacity != 0) || (stk == NULL))
        if (stack_ok(stk)) {
            stack_dump(stk);
    }
#endif


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
    create_check_stack(stk);
    if (stack_ok(stk))
        stack_dump(stk);
#endif

}

Elent stack_pop(struct_stack *stk) {

#ifdef debugon
    if (stack_ok(stk))
        stack_dump(stk);
#endif

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
    create_check_stack(stk);
#endif

    return result;
}

int stack_dtor(struct_stack *stk) {

#ifdef debugon

    int check = -1;

    for (int i = 0; i < num_stk_c; i++) {
        if (stack_str_cmp(stk_c_name[i], stk->name_stk) == 0) {
            check = i;
            break;
        }
    }

    if (check == -1) {
        printf("check == -1 at line %d in func %s in file %s\n", __LINE__, __func__, __FILE__);
        printf("stk->name_stk = %s\n", stk->name_stk);

        for (int i = 0; i < num_stk_c; i++)
            printf("stk_c_name[%d] = %s\n", i, stk_c_name[i]);
    }

#endif

    if (stk == NULL)
        return -1;

    free(stk->data);
    stk->data     = 0;
    stk->copacity = 0;
    stk->a        = 0;

#ifdef debugon

    stk->def_line = 0;
    stk->def_file_name = NULL;
    stk->def_func_name = NULL;

    if (check > -1) {
        stk_c[check].def_file_name = NULL;
        stk_c[check].def_func_name = NULL;
        stk_c[check].data          = NULL;
        stk_c[check].def_line = 0;
        stk_c[check].data     = 0;
        stk_c[check].copacity = 0;
        stk_c[check].a        = 0;
    }

#endif

    return 0;
}

int stack_copy(struct_stack *stk, struct_stack *stk_cpy) {

#ifdef debugon
    if (stack_ok(stk))
        stack_dump(stk);
#endif

    stk_cpy->a = stk->a;
    stk_cpy->copacity = stk->copacity;
    stk_cpy->data = (Elent *) calloc(stk_cpy->copacity, sizeof(Elent));

    if (stk_cpy->data == NULL)
        return -1;

    for (size_t i = 0; i < stk_cpy->copacity; i++)
        stk_cpy->data[i] = stk->data[i];

#ifdef debugon
    if (stack_ok(stk))
        stack_dump(stk);

    create_check_stack(stk_cpy);
#endif

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

    create_check_stack(stk);

    return 0;
}

static int create_check_stack(struct_stack *stk) {

    int check = -1;
    for (int i = 0; i < num_stk_c; i++) {
        if (stack_str_cmp(stk_c_name[i], stk->name_stk) == 0) {
            check = i;
            break;
        }
    }

    if (check == -1) {
        num_stk_c++;
        check = num_stk_c - 1;
        stk_c_name =  (char * *) realloc(stk_c_name, num_stk_c * sizeof(char *));

        stk_c = (struct_stack *) realloc(stk_c,      num_stk_c * sizeof(struct_stack));
        stk_c_name[check] = (char *) calloc(strlen(stk->name_stk) + 1, sizeof(char));
        stk_c_name[check] = (char *) stk->name_stk;

        if ((stk_c_name == NULL) || (stk_c == NULL))
            return -1;
    }

    stk_c[check].name_stk      = stk->name_stk;
    stk_c[check].def_line      = stk->def_line;
    stk_c[check].def_file_name = stk->def_file_name;
    stk_c[check].def_func_name = stk->def_func_name;
    stk_c[check].a             = stk->a;
    stk_c[check].copacity      = stk->copacity;

    stk_c[check].data = (Elent *) calloc(stk_c[check].copacity, sizeof(Elent));

    if (stk_c[check].data == NULL)
        return -1;

    for (size_t i = 0; i < stk_c[check].copacity; i++)
        stk_c[check].data[i] = stk->data[i];

    return 0;
}

static int stack_str_cmp(const char * s1, const char *s2) {

    if (s1 == NULL)
        printf("s1 == NULL\n");

    if (s2 == NULL)
        printf("s2 == NULL\n");

    size_t l1 = strlen(s1);
    size_t l2 = strlen(s2);
    size_t i = 0, j = 0;

    while ((i < l1) && (j < l2)) {

        if (s1[i] == '&')
            i++;

        if (s2[j] == '&')
            j++;

        if ((s1[i] != s2[j]) && (s1[i] != '&') && (s2[j] != '&'))
            return s1[i] - s2[j];

        i++;
        j++;
    }

    return s1[i] - s2[j];
}

#endif

