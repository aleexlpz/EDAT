#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "file_utils.h"
#include "vertex.h"

#define MAX_SIZE 128
#define BUFFERLEN 999

/**
 * @brief: Merges two stacks
 *
 * @param sin1, first input stack
 * @param sin2, second input stack
 * @param sout, result stack
 * @return The function returns OK or ERROR
 **/
Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout, int (*cmp)(const void *, const void *))
{
    Status st = OK;
    Stack *ps;
    void *e;

    if (!sin1 || !sin2)
        return ERROR;

    while (!stack_isEmpty(sin1) && !stack_isEmpty(sin2))
    {
        if (cmp(stack_top(sin1), stack_top(sin2)) > 0)
            e = stack_pop(sin1);
        else
            e = stack_pop(sin2);

        if (!e)
            return ERROR;
        st = stack_push(sout, e);
        if (!st)
            return ERROR;
    }

    if (stack_isEmpty(sin1))
        ps = sin2;
    else
        ps = sin1;

    while (!stack_isEmpty(ps))
    {
        e = stack_pop(ps);
        if (!e)
            return ERROR;
        st = stack_push(sout, e);
    }

    return st;
}

int main(int argc, char *argv[])
{

    Stack *s1, *s2, *s;
    FILE *f;
    char aux[BUFFERLEN];
    Vertex **e1, **e2;
    int n_elems1, n_elems2, i = 0, j = 0;

    if(argc != 3)
        return EXIT_FAILURE;

    /*initialize s1*/
    s1 = stack_init();
    if (!s1)
        return EXIT_FAILURE;

    f = fopen(argv[1], "r");
    if (!f)
    {
        stack_free(s1);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d\n", &n_elems1);

    e1 = (Vertex **)malloc(n_elems1 * sizeof(Vertex *));
    if (!e1)
    {
        stack_free(s1);
        fclose(f);
        return EXIT_FAILURE;
    }
    for (i = 0; i < n_elems1; i++)
    {
        fgets(aux, BUFFERLEN, f);

        e1[i] = vertex_initFromString(aux);
        if (!e1[i])
        {
            stack_free(s1);
            fclose(f);
            for (j = 0; j < i; j++)
            {
                vertex_free(e1[j]);
            }
            return EXIT_FAILURE;
        }

        if (!stack_push(s1, e1[i]))
        {
            stack_free(s1);
            fclose(f);
            for (j = 0; j < i; j++)
            {
                vertex_free(e1[j]);
            }
            return EXIT_FAILURE;
        }
    }
    fclose(f);

    /*print s1*/
    fprintf(stdout, "Ranking 0:\n");
    stack_print(stdout, s1, vertex_print);

    /*initialize s2*/
    s2 = stack_init();
    if (!s2)
    {
        stack_free(s1);
        return EXIT_FAILURE;
    }

    f = fopen(argv[2], "r");
    if (!f)
    {
        stack_free(s1);
        stack_free(s2);
        return EXIT_FAILURE;
    }

    fscanf(f, "%d\n", &n_elems2);

    e2 = (Vertex **)malloc(n_elems2 * sizeof(Vertex *));
    if (!e2)
    {
        stack_free(s1);
        stack_free(s2);
        fclose(f);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n_elems2; i++)
    {
        fgets(aux, BUFFERLEN, f);

        e2[i] = vertex_initFromString(aux);
        if (!e2[i])
        {
            stack_free(s2);
            fclose(f);
            for (j = 0; j < i; j++)
            {
                vertex_free(e2[j]);
            }
            return EXIT_FAILURE;
        }

        if (!stack_push(s2, e2[i]))
        {
            stack_free(s2);
            fclose(f);
            for (j = 0; j < i; j++)
            {
                vertex_free(e2[j]);
            }
            return EXIT_FAILURE;
        }
    }
    fclose(f);

    /*print s2*/
    fprintf(stdout, "Ranking 1:\n");
    stack_print(stdout, s2, vertex_print);

    /*initialize s*/
    s = stack_init();
    if (!s)
    {
        stack_free(s1);
        stack_free(s2);
    }

    if (!mergeStacks(s1, s2, s, vertex_cmp))
    {
        stack_free(s);
        stack_free(s1);
        stack_free(s2);
    }

    /*printf s*/
    fprintf(stdout, "Joint Ranking:\n");
    stack_print(stdout, s, vertex_print);

    /*free allocated memory*/
    for (j = 0; j < n_elems1; j++)
    {
        vertex_free(e1[j]);
    }
    for (j = 0; j < n_elems2; j++)
    {
        vertex_free(e2[j]);
    }
    stack_free(s);
    stack_free(s1);
    stack_free(s2);

    vertex_free(e1);
    vertex_free(e2);
    
    return 0;
}