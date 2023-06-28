#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delivery.h"
#include "graph.h"
#include "types.h"


Delivery *build_delivery(FILE *pf);


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if(!f){
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    Delivery *d = build_delivery(f);
    if(!d){
        printf("Error reading delivery\n");
        fclose(f);
        return 1;
    }
    if(!delivery_run_plan(stdout, d, vertex_print, vertex_free)){
        printf("Error running delivery\n");
        delivery_free(d);
        fclose(f);
        return 1;
    }
    fclose(f);
    delivery_free(d);
}


Delivery *build_delivery(FILE *pf){
    char name[100], product_name[100], line[100];
    int n, i;
    Delivery *d;
    
    if(!pf){
        return NULL;
    }
    if(fscanf(pf, "%s %s %d\n", name, product_name, &n) != 3){
        return NULL;
    }
    Vertex *v;
    d = delivery_init(name, product_name);
    if(!d){
        return NULL;
    }
    for(i = 0; i < n; i++){
        if(!fgets(line, 100, pf)){
            delivery_free(d);
            return NULL;
        }
        v = vertex_initFromString(line);
        if (!v)
        {
            delivery_free(d);
            return NULL;
        }
        if(!delivery_add(stdout, d, v, vertex_print)){
            delivery_free(d);
            return NULL;
        }
    }    
    fprintf(stdout, "\n\n");
    return d;
}