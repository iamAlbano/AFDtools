#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afd.h"

state *createState(state *state, char *identifier)
{
    struct state *state_aux = malloc(sizeof(state));

    strcpy(state_aux->identifier, identifier);
    state_aux->is_final = 0;
    state_aux->is_final = 0;
    state_aux->next = state;

    return state_aux;
}

void setStates( afd_struct *afd, FILE *afd_file) {
    char file_line[50];

    fgets(file_line, 50, afd_file);
    afd->states_size = atoi(file_line);

    if (!afd->states_size ) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    state *state_aux = NULL;

    for (int i = 0; i < afd->states_size; i++) {
        fgets(file_line, 50, afd_file);
        state_aux = createState(state_aux, file_line);
    }
    afd->states = *state_aux;
}

void setAlphabet( afd_struct *afd, FILE *afd_file) {
    char file_line[50];

    fgets(file_line, 50, afd_file);
    afd->alphabet_size = atoi(file_line);

    if (!afd->alphabet_size ) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    for (int i = 0; i < afd->alphabet_size; i++) {
        fgets(file_line, 50, afd_file);
        strncpy(afd->alphabet[i], file_line, 50);
    }
}

struct afd_struct construct (char *input_file, char *output_file) {

    FILE *afd_file = fopen(input_file, "r");
    char file_line[50];

    struct afd_struct afd;

    setStates(&afd, afd_file);
    setAlphabet(&afd, afd_file);

    fclose(afd_file);

    return afd;
}





