#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

typedef struct _SearchQueue {
    BSTree *data;
} SearchQueue;

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele) {
    SearchQueue *q = NULL;

    if(!print_ele || !cmp_ele) {
        return NULL;
    }

    q = (SearchQueue *)malloc(sizeof(SearchQueue));
    if (!q) {
        return NULL;
    }

    q->data = tree_init(print_ele, cmp_ele);
    if (!q->data) {
        free(q);
        return NULL;
    }

    return q;
}



void search_queue_free(SearchQueue *q) {
    if (!q) {
        return;
    }

    tree_destroy(q->data);
    free(q);

    return;
}

Bool search_queue_isEmpty(const SearchQueue *q) {
    if (!q) {
        return TRUE;
    }

    return tree_isEmpty(q->data);
}

Status search_queue_push(SearchQueue *q, void *ele) {
    if (!q || !ele) {
        printf("da error aqui\n");
        return ERROR;
    }
    return tree_insert(q->data, (const void*)ele);
}

void *search_queue_pop(SearchQueue *q) {
    void *ele = NULL;

    if (!q) {
        return NULL;
    }

    ele = tree_find_min(q->data);
    tree_remove(q->data, ele);

    return ele;
}


void *search_queue_getFront(const SearchQueue *q) {
    void *ele = NULL;

    if (!q) {
        return NULL;
    }
    if(tree_isEmpty(q->data)) {
        return NULL;
    }
    else {
        ele = tree_find_min(q->data);
    }
    return ele;
}

void *search_queue_getBack(const SearchQueue *q) {
    void *ele = NULL;

    if (!q) {
        return NULL;
    }
    if (tree_isEmpty(q->data)){
        return NULL;
    }
    ele = tree_find_max(q->data);

    return ele;
}

size_t search_queue_size(const SearchQueue *q) {
    if (!q) {
        return -1;
    }

    return tree_size(q->data);
}

int search_queue_print(FILE *fp, const SearchQueue *q) {
    if (!fp || !q) {
        return -1;
    }
    return tree_inOrder(fp, q->data);
}

