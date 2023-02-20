#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    file_line[strcspn(file_line, "\n")] = 0;
    afd->states_size = atoi(file_line);

    if (!afd->states_size ) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    state *state_aux = NULL;

    for (int i = 0; i < afd->states_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        state_aux = createState(state_aux, file_line);
    }
    afd->states = *state_aux;
}

void setAlphabet( afd_struct *afd, FILE *afd_file) {
    char file_line[50];

    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    afd->alphabet_size = atoi(file_line);

    if (!afd->alphabet_size ) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    for (int i = 0; i < afd->alphabet_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        strncpy(afd->alphabet[i], file_line, 50);
    }
}

void *createTransition (transition *transition, char *symbol, state *origin, state *destiny) {
    struct transition *transition_aux = malloc(sizeof(transition));

    strcpy(transition_aux->symbols[0], symbol);
    transition_aux->symbols_size = 1;
    transition_aux->origin = origin;
    transition_aux->destiny = destiny;
    transition_aux->next = transition;

    return transition;
}

void setTransitions( afd_struct *afd, FILE *afd_file) {
    char file_line[50];

    fgets(file_line, 50, afd_file);
    int size = atoi(file_line);

    if (!size) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    char origin_id[50];
    char symbol[50];
    char destiny_id[50];
    int transitions_size = 0;

    transition *transition_aux = NULL;

    for (int i = 0; i < size; i++) {

        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;

        sscanf(file_line, "%s %s %s", origin_id, symbol, destiny_id);

        afd_struct afd_origin = *afd;
        afd_struct afd_destiny = *afd;

        state *origin = NULL;
        state *destiny = NULL;
    
        for (int i = 0; i < afd_origin.states_size; i++) {  
            if (!origin && strncmp(afd_origin.states.identifier, origin_id, 50) == 0) {
                origin = &afd_origin.states;
                break;
            }
            
            afd_origin.states = *afd_origin.states.next;
        }

        for (int j = 0; j < afd_destiny.states_size; j++) {  
            if (!destiny && strncmp(afd_destiny.states.identifier, destiny_id, 50) == 0) {
                destiny = &afd_destiny.states;
                break;
            }
            
            afd_destiny.states = *afd_destiny.states.next;
        }

        afd_struct afd_transitions = *afd;

        for (int k = 0; k < afd_transitions.transitions_size; k++) {
            puts(afd_transitions.transitions->origin->identifier);
        }

        transition_aux = createTransition(transition_aux, symbol, origin, destiny);
        printf("------------------\n"); 
        transitions_size++;

    }
    afd->transitions_size = transitions_size;
    afd->transitions = transition_aux;  
}

void printAFD (afd_struct afd) {
    struct afd_struct afd_aux = afd;

    printf("Estados: \n");
    for (int i = 0; i < afd_aux.states_size; i++) {
        printf("%s\n", afd_aux.states.identifier);

        if (i != afd_aux.states_size-1)
            afd_aux.states = *afd_aux.states.next;
    }

    printf("Alfabeto: \n");
    for (int i = 0; i < afd_aux.alphabet_size; i++) {
        printf("%s\n", afd_aux.alphabet[i]);
    }

    struct afd_struct transition_afd = afd;

    printf("Transições: \n"); 

    /* for (int i = 0; i < afd.transitions_size; i++) {
        puts(transition_afd.transitions->symbols_size);
    } */
}

struct afd_struct construct (char *input_file, char *output_file) {

    FILE *afd_file = fopen(input_file, "r");

    struct afd_struct afd;

    setStates(&afd, afd_file);
    setAlphabet(&afd, afd_file);
    setTransitions(&afd, afd_file);

    printAFD(afd);  

    fclose(afd_file);

    return afd;
}





