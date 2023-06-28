#include "list.h"
#include "file_utils.h"
#include <unistd.h>

struct _List
{
    NodeList *last;
};

struct _NodeList
{
    void *data;
    struct _NodeList *next;
};

NodeList *node_new();

NodeList *node_new()
{
    NodeList *pn = NULL;
    pn = (NodeList *)malloc(sizeof(NodeList));
    if (!pn)
    {
        return NULL;
    }
    pn->data = NULL;
    pn->next = NULL;
    return pn;
}
List *list_new()
{
    List *pl = NULL;
    pl = (List *)malloc(sizeof(List));
    if (pl == NULL)
    {
        return NULL;
    }
    pl->last = NULL;

    return pl;
}

Bool list_isEmpty(const List *pl)
{
    if (!pl)
    {
        return TRUE;
    }
    if (!pl->last)
    {
        return TRUE;
    }
    return FALSE;
}

Status list_pushFront(List *pl, void *e)
{
    NodeList *pn = NULL;
    if (pl == NULL || e == NULL)
    {
        return ERROR;
    }
    pn = node_new();
    if (pn == NULL)
    {
        return ERROR;
    }
    pn->data = (void *)e;
    if (list_isEmpty(pl))
    {
        pn->next = pn;
        pl->last = pn;
    }
    else
    {
        pn->next = pl->last->next;
        pl->last->next = pn;
    }
    return OK;
}

Status list_pushBack(List *pl, void *e)
{
    NodeList *pn = NULL;
    if (pl == NULL || e == NULL)
    {
        return ERROR;
    }
    pn = node_new();
    if (pn == NULL)
    {
        return ERROR;
    }
    pn->data = (void *)e;
    if (list_isEmpty(pl) == TRUE)
    {
        pn->next = pn;
        pl->last = pn;
    }
    else
    {
        pn->next = pl->last->next;
        pl->last->next = pn;
        pl->last = pn;
    }
    return OK;
}
void *list_getLast(List *pl);
void *list_getLast(List *pl)
{
    return pl->last;
}
void *list_getFront(List *pl);
void *list_getFront(List *pl)
{
    return pl->last->next;
}

Status list_pushInOrder(List *pl, void *e, P_ele_cmp f, int order)
{
    if (!pl || !e || f == NULL || order == 0)
        return ERROR;

    NodeList *node1 = NULL, *node2 = NULL;
    Bool found = FALSE;
   
    node2 = node_new();
    if (node2 == NULL)
    {
        free(node1);
        return ERROR;
    } 
    /* Caso : lista vacia*/
    if (list_isEmpty(pl) == TRUE)
    {
        list_pushBack(pl, e);
        free(node1);
        free(node2);
        return OK;
    }

    node1 = pl->last;
    node2->data = (void *)e;
    
    while (node1->next != pl->last && found == FALSE)
    {

        if (order * f(node2->data, node1->next->data) <= 0)
        {
            node2->next = node1->next;
            node1->next = node2;
            found = TRUE;
        }
        else
            node1 = node1->next;
    }

    if (node1->next == pl->last)
    {
        if (order * f(node2->data, node1->next->data) <= 0)
        {
            node2->next = node1->next;
            node1->next = node2;
            found = TRUE;
        }
        else
            node1 = node1->next;
    }
    if (found == FALSE)
    {
        if (list_pushBack(pl, e) == OK){
            found = TRUE;
            free(node2);
        }

    }
    
    return OK;

}

void *list_popFront(List *pl)
{
    NodeList *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE)
    {
        return NULL;
    }
    pn = pl->last->next;
    pe = pn->data;
    if (pl->last->next == pl->last)
    {
        pl->last = NULL;
    }
    else
    {
        pl->last->next = pn->next;
    }
    free(pn);
    return pe;
}

void *list_popBack(List *pl)
{
    NodeList *pn = NULL;
    void *pe = NULL;
    if (pl == NULL || list_isEmpty(pl) == TRUE)
    {
        return NULL;
    }
    if (pl->last->next == pl->last)
    {
        pe = pl->last->data;
        free(pl->last);
        pl->last = NULL;
        return pe;
    }
    pn = pl->last;
    while (pn->next != pl->last)
    {
        pn = pn->next;
    }
    pe = pl->last->data;
    pn->next = pl->last->next;
    free(pl->last);
    pl->last = pn;
    return pe;
}

void list_free(List *pl)
{
    if (pl == NULL)
    {
        return;
    }
    while (list_isEmpty(pl) == FALSE)
    {
        list_popFront(pl);
    }
    free(pl);
}

size_t list_size(const List *pl)
{
    if (!pl)
        return 0;
    if (list_isEmpty(pl) == TRUE)
        return 0;

    NodeList *n;
    n = pl->last;
    size_t s;

    for (s = 1; n->next != pl->last; s++)
    {
        if (s == 1 && n->next == NULL)
            return 1;
        n = n->next;
    }

    return s;
}

int list_print(FILE *fp, const List *pl, P_ele_print f)
{
    NodeList *pn = NULL;
    int return_value = 0;
    int val = 0;

    if (pl == NULL || fp == NULL)
    {
        return EXIT_FAILURE;
    }
    pn = pl->last;
    while (pn->next != pl->last)
    {
        val = f(fp, pn->next->data);
        if (val < 0)
        {
            return EXIT_FAILURE;
        }
        printf(" ");
        if (val < 0)
        {
            return EXIT_FAILURE;
        }
        return_value += val;
        pn = pn->next;
    }
    val = f(fp, pl->last->data);


    return return_value;
}