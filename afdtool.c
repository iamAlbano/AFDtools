#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "tools/view/view.h"
#include "tools/complement/complement.h"
#include "tools/union/union.h"
#include "tools/recognize/recognize.h"

int validateParameters (int num_params) {
    if (num_params == 1 ) {
        printf("Número de parâmetros inválido.\n");
        exit(-1);
    }
}

char* handleStartFunction (int argc, char *argv[]) {

    if ( argc != 5) {
        printf("Número de parâmetros inválido.\n");
        exit(-1);
    }
    
    char* output = malloc(sizeof(char) * strlen(argv[4]) + 1); 

    strcpy(output, argv[4]);
    
    if (!strcmp(argv[1],"--dot")) 
        view(argv[2], output); 
    
    else if (!strcmp(argv[1],"--complemento")) 
        exportComplement(argv[2], output);
    
}

/* Função para iniciar a execução do programa com dois parâmetros de afd de entrada */
char* handleStartFunction2 (int argc, char *argv[]) {

    if ( argc != 6) {
        printf("Número de parâmetros inválido.\n");
        exit(-1);
    }
    
    char* output = malloc(sizeof(char) * strlen(argv[5]) + 1); 
    strcpy(output, argv[5]); 
    
    if (!strcmp(argv[1],"--reconhecer")) 
        recognize(argv[2], argv[3], output);
}

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "Portuguese");

    validateParameters(argc);

    if (!strcmp(argv[1],"--dot") || !strcmp(argv[1],"--complemento"))
        handleStartFunction(argc, argv);

    else if (!strcmp(argv[1],"--reconhecer"))
        handleStartFunction2(argc, argv);

    else
        printf("Funcionalidade não implementada.\n");
    
    return 0;
    
}
