#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "tools/view/view.h"

int validateParameters (int num_params) {
    if (num_params == 1 ) {
        printf("Número de parâmetros inválido.\n");
        exit(-1);
    }
}

char* handleView (int argc, char *argv[]) {

    if ( argc != 5) {
        printf("Número de parâmetros inválido.\n");
        exit(-1);
    }
    
    char* output = malloc(sizeof(char) * strlen(argv[4]) + 1); 

    strcpy(output, argv[4]);
    
    view(argv[2], output);
}

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "Portuguese");

    validateParameters(argc);

    if (!strcmp(argv[1],"--dot"))
        handleView(argc, argv);

    else
        printf("Funcionalidade não implementada.\n");
    
    return 0;
    
}
