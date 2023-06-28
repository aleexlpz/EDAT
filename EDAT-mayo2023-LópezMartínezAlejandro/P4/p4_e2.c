#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_queue.h"
#include "vertex.h"

#define MAX 256

int string_print(FILE *pf, const void *src) {
  if (!pf || !src)
    return -1;
  return fprintf(pf, "%s", (char *)src);
}

int main(int argc, char*argv[]) {
    FILE *f_in = NULL, *f_out = NULL;
    
    char** line = NULL;
    int i = 0, numLineas = 0;
    char aux;
    SearchQueue *q = search_queue_new((P_ele_print)string_print, (P_ele_cmp)strcmp);
    if (!q) {
        fprintf(stderr, "Error en la creación de la cola\n");
        return EXIT_FAILURE;
    }

    if(argc != 3) {
        fprintf(stderr, "Error en el número de argumentos\n Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    f_in = fopen(argv[1], "r");
    if (!f_in) {
        fprintf(stderr, "Error en la apertura del fichero %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    while ((aux = fgetc(f_in)) != EOF) {
        if (aux == '\n') {
            numLineas++;
        }
    }
    fclose(f_in);

    line = (char**)malloc(numLineas*sizeof(char*));
    if (!line) {
        fprintf(stderr, "Error en la reserva de memoria\n");
        return EXIT_FAILURE;
    }
    for(i = 0; i < numLineas; i++) {
        line[i] = (char*)malloc(MAX*sizeof(char));
        if (!line[i]) {
            fprintf(stderr, "Error en la reserva de memoria\n");
            return EXIT_FAILURE;
        }
    }
    f_in = fopen(argv[1], "r");
    if (!f_in) {
        fprintf(stderr, "Error en la apertura del fichero %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    f_out = fopen(argv[2], "w");
    if (!f_out) {
        fprintf(stderr, "Error en la apertura del fichero %s\n", argv[2]);
        fclose(f_in);
        exit(EXIT_FAILURE);
    }
    i = 0;
    for(i = 0; i < numLineas; i++) {
        fgets(line[i], MAX, f_in);
        if(search_queue_push(q, (void*)line[i]) == ERROR) {
            fprintf(stderr, "Error en la inserción de la cola\n");
            fclose(f_in);
            fclose(f_out);
            search_queue_free(q);
            for(i = 0; i < numLineas; i++) {
                free(line[i]);
            }
            exit(EXIT_FAILURE);
        }

    }

    while(!search_queue_isEmpty(q)) {
        char *str = (char*)search_queue_pop(q);
        fprintf(f_out, "%s", str);
        free(str);
    }

    fclose(f_in);
    fclose(f_out);
    search_queue_free(q);
    free(line);

    return EXIT_SUCCESS;
}