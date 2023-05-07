#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/
/*Se pide implementar las siguientes primitivas públicas del TAD BST, junto con sus correspondientes fun‑
ciones privadas (recursivas), y cuya definición completa se encuentra en bstree.h:
• tree_find_min: devuelve el elemento más pequeño almacenado en el árbol (void * )
• tree_find_max: devuelve el elemento más grande almacenado en el árbol (void * )
• tree_contains: comprueba si un elemento existe en el árbol.
• tree_insert: inserta un nuevo elemento en el árbol (si el elemento ya se encuentra en el árbol
no se debe insertar, pero la función devolverá OK).*/

void *tree_find_min(BSTree *tree) {
  BSTNode *pn = NULL;

  if (!tree) {
    return NULL;
  }

  pn = tree->root;
  while (pn->left) {
    pn = pn->left;
  }

  return pn->info;
}

void *tree_find_max(BSTree *tree) {
  BSTNode *pn = NULL;

  if (!tree) {
    return NULL;
  }

  pn = tree->root;
  while (pn->right) {
    pn = pn->right;
  }

  return pn->info;
}

Bool tree_contains(BSTree *tree, const void *elem) {
  BSTNode *pn = NULL;

  if (!tree || !elem) {
    return FALSE;
  }

  pn = tree->root;
  while (pn) {
    if (tree->cmp_ele(elem, pn->info) == 0) {
      return TRUE;
    } else if (tree->cmp_ele(elem, pn->info) < 0) {
      pn = pn->left;
    } else {
      pn = pn->right;
    }
  }

  return FALSE;
}

Status tree_insert(BSTree *tree, const void *pe) {
  BSTNode *pn = NULL, *parent = NULL;

  if (!tree || !pe) {
    return ERROR;
  }

  pn = tree->root;
  while (pn) {
    if (tree->cmp_ele(pe, pn->info) == 0) {
      return OK;
    } 
    else if (tree->cmp_ele(pe, pn->info) < 0) {
      parent = pn;
      pn = pn->left;
    } 
    else {
      parent = pn;
      pn = pn->right;
    }
  }

  pn = _bst_node_new();
  pn->info = (void *)pe;

  if (!pn) {
    return ERROR;
  }

  if (!parent) {
    tree->root = pn;
  } else if (tree->cmp_ele(pe, parent->info) < 0) {
    parent->left = pn;
  } else {
    parent->right = pn;
  }

  return OK;
}

BSTNode *_bst_remove_rec(BSTNode *pn, const void *pe, BSTree *tree) {
  BSTNode *aux = NULL;

  if (!pn) {
    return NULL;
  }

  if (tree->cmp_ele(pe, pn->info) < 0) {
    pn->left = _bst_remove_rec(pn->left, pe, tree);
  } else if (tree->cmp_ele(pe, pn->info) > 0) {
    pn->right = _bst_remove_rec(pn->right, pe, tree);
  } else {
    if (!pn->left && !pn->right) {
      free(pn);
      pn = NULL;
    } else if (!pn->left) {
      aux = pn;
      pn = pn->right;
      free(aux);
    } else if (!pn->right) {
      aux = pn;
      pn = pn->left;
      free(aux);
    } else {
      aux = (BSTNode *)tree_find_min(tree);
      pn->info = aux->info;
      pn->right = _bst_remove_rec(pn->right, aux->info, tree);
    }
  }

  return pn;
}

Status tree_remove(BSTree *tree, const void *pe) {
  if (!tree || !pe) {
    return ERROR;
  }

  tree->root = _bst_remove_rec(tree->root, pe, tree);

  return OK;
}



