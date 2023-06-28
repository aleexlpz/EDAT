#include "vertex.h"
#include "graph.h"
#include "stack.h"
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    Graph *g = graph_init();
    if(!g)
    {
        printf("Error initializing graph");
        return EXIT_FAILURE;
    }

    FILE *f;
    int ini, fin;

    ini = atoi(argv[2]);
    fin = atoi(argv[3]);
    f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Error opening file");
        graph_free(g);
        return EXIT_FAILURE;
    }
    if(graph_readFromFile(f, g) == ERROR)
    {
        printf("Error reading file");
        graph_free(g);
        return EXIT_FAILURE;
    }
    fclose(f);
    graph_print(stdout, g);
    if(graph_getNumberOfVertices(g) == 0)
    {
        printf("Error, no vertices");
        graph_free(g);
        return EXIT_FAILURE;
    }
    printf("From Vertex id: %d\n", ini);
    printf("To Vertex id: %d\n", fin);
    printf("Output:\n");

    graph_depthSearch(g, ini, fin);
    
    graph_free(g);
    

    return 0;
}
