#include "list.h"
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Error en la linea de comandos: se debe indicar el orden de insercion\n");
        return 1;
    }
    
    int order = atoi(argv[2]);
    if (order != 1 && order != -1)
    {
        fprintf(stderr, "Error en la linea de comandos: el orden de insercion debe ser 1 o -1\n");
        return 1;
    }
    List *l = list_new();
    List *sorted_list = list_new();
    FILE *fp = fopen(argv[1], "r");
    int i = 0, j;
    fscanf(fp, "%d", &j);
    float *note = (float *)malloc(sizeof(float) * j);
    void *aux = NULL;
    while(fscanf(fp, "%f", &note[i]) != EOF)
    {
        if (i % 2 == 0)
        {
            list_pushBack(l, &note[i]);
        }
        else
        {
            list_pushFront(l, &note[i]);
        }
        i++;
    }

    
    fclose(fp);
    printf("SIZE: %d\n", j);
    if(list_print(stdout, l, float_print) == 0){
        fprintf(stderr, "Error printing list\n");
        list_free(l);
        list_free(sorted_list);
        free(note);
        return EXIT_FAILURE;
    }
    printf("\nFinished inserting. Now we extract from the beginning and insert in order: \n");

    for(i = 0; i < j/2; i++){
        aux = list_popFront(l);
        float_print(stdout, aux);
        printf(" ");
        if(list_pushInOrder(sorted_list, aux, float_cmp, order) == ERROR){
            fprintf(stderr, "Error inserting in order\n");
            list_free(l);
            list_free(sorted_list);
            free(note);
            return EXIT_FAILURE;
        }
    }
    printf("\nNow we extract from the end and insert in order: \n");
    for(i = j-1; i >= j/2; i--){
        aux = (float *)list_popBack(l);
        float_print(stdout, aux);
        printf(" ");
        if(list_pushInOrder(sorted_list, aux, float_cmp, order) == ERROR){
            fprintf(stderr, "Error inserting in order\n");
            list_free(l);
            list_free(sorted_list);
            free(note);
            return EXIT_FAILURE;
        }
        
    }
    printf("\nSIZE: %d\n", j);
    if(list_print(stdout, sorted_list, float_print) == ERROR){
        fprintf(stderr, "Error printing the list\n");
        list_free(l);
        list_free(sorted_list);
        free(note);
        return EXIT_FAILURE;
    }

    printf("\n");
    

    list_free(l);
    list_free(sorted_list);
    free(note);

    return 0;
}