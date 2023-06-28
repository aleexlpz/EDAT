#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "graph.h"
#include "vertex.h"
#include "types.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <file> <origin> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }
    Status st;
    long ini, fin;
    ini = atol(argv[2]);
    fin = atol(argv[3]);
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Error opening file %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    Graph *g = graph_init();
    if (!g)
    {
        printf("Error creating graph\n");
        return EXIT_FAILURE;
    }
    if (graph_readFromFile(f, g) == ERROR)
    {
        printf("Error reading graph\n");
        return EXIT_FAILURE;
    }

    fclose(f);
    printf("Input graph:\n");
    graph_print(stdout, g);
    printf("--------DFS------------\n\n");
    printf("From Vertex id: %ld\nTo vertex id: %ld\nOutput:\n", ini, fin);
    st = graph_depthSearch(g, ini, fin);
    if (st == ERROR)
    {
        printf("Error searching path\n");
    }
    printf("\n--------BFS------------\n\n");
    printf("From Vertex id: %ld\nTo vertex id: %ld\nOutput:\n", ini, fin);
    st = graph_breathSearch(g, ini, fin);
    if (st == ERROR)
    {
        printf("Error searching path\n");
    }
    graph_free(g);
    return EXIT_SUCCESS;
}