/*Para comprobar el correcto funcionamiento del TAD SQ, se pide implementar un nuevo programa prin‑
cipal, p4_e2.c, que reciba dos argumentos, correspondientes al nombre de un fichero de entrada, y al
nombre de un fichero de salida.
A continuación, el programa leerá cada línea del fichero de entrada, insertando la cadena leída en una
cola SQ. Una vez leído el fichero de entrada, se vaciará la cola elemento a elemento imprimiendo cada
línea en el fichero de salida. De esta forma, cuando termine la ejecución el fichero de salida deberá con‑
tener las líneas del fichero de entrada, pero ordenadas alfabéticamente.
El programa debe funcionar sin fugas de memoria. Como ejemplo de ejecución, se puede ver el fichero
de salida esperado data_string_10.out cuando el fichero de entrada es data_string_10.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_queue.h"
#include "vertex.h"

#define MAX 256

int main(int argc, char*argv[]) {
    FILE *f_in = NULL, *f_out = NULL;
    SearchQueue *q = NULL;
    char line[MAX];

    if(argc != 3) {
        fprintf(stderr, "Error en el número de argumentos\n Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }


    f_in = fopen(argv[1], "r");
    if (!f_in) {
        exit(EXIT_FAILURE);
    }

    f_out = fopen(argv[2], "w");
    if (!f_out) {
        exit(EXIT_FAILURE);
    }

    q = search_queue_new((P_ele_print)vertex_print, (P_ele_cmp)vertex_cmp);
    if (!q) {
        fclose(f_in);
        fclose(f_out);
        exit(EXIT_FAILURE);
    }

    while(fgets(line, MAX, f_in) != NULL) {
        if(search_queue_push(q, line) == ERROR) {
            fprintf(stderr, "Error en la inserción de la cola\n");
            fclose(f_in);
            fclose(f_out);
            search_queue_free(q);
            exit(EXIT_FAILURE);
        }
        else printf("Insertado %s\n", line);
    }

    while(!search_queue_isEmpty(q)) {
        fprintf(f_out, "%s", (char*)search_queue_pop(q));
        printf("Extraído\n");
    }

    fclose(f_in);
    fclose(f_out);
    search_queue_free(q);

    return EXIT_SUCCESS;
}