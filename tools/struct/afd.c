#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "afd.h"

state *createState(state *next_state, char *identifier)
{
    state *new_state = (state *)malloc(sizeof(state));
    
    strcpy(new_state->identifier, identifier);
    new_state->is_final = 0;
    new_state->is_final = 0;
    new_state->next = next_state;

    return new_state;
}

void setStates( afd_struct *afd, FILE *afd_file) {
    char file_line[50];

    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int size = atoi(file_line);
    afd->states_size = size; 

    if (!afd->states_size ) {
        printf("Arquivo de formato inválido!\n"); 
        exit(-1);
    }

    state *state_aux = NULL;

    for (int i = 0; i < size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        state_aux = createState(state_aux, file_line);
    }
    afd->states = state_aux;
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

void *createTransition (transition *next_transition, char *symbol, char *origin, char *destiny) {
    transition *new_transition = (transition *)malloc(sizeof(transition));
    
    strcpy(new_transition->symbols[0], symbol);
    new_transition->symbols_size = 1;
    strcpy(new_transition->origin_id, origin);
    strcpy(new_transition->destiny_id , destiny);
    new_transition->next = next_transition;

    return new_transition;
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

        transition_aux = createTransition(transition_aux, symbol, origin_id, destiny_id); 
        transitions_size++;

    }
    afd->transitions_size = transitions_size;
    afd->transitions = transition_aux;  
}

void printAFD (afd_struct afd) {
    struct afd_struct afd_aux = afd;

    printf("Estados: \n");
    for (int i = 0; i < afd_aux.states_size; i++) {
        printf("%s\n", afd_aux.states->identifier);

        if (i != afd_aux.states_size-1)
            afd_aux.states = afd_aux.states->next;
    }

    printf("Alfabeto: \n");
    for (int i = 0; i < afd_aux.alphabet_size; i++) {
        printf("%s\n", afd_aux.alphabet[i]);
    }

    struct afd_struct transition_afd = afd;

    printf("Transições: \n"); 

    for(int i = 0; i < transition_afd.transitions_size; i++) {
        puts(transition_afd.transitions->origin_id);
        puts(transition_afd.transitions->symbols[0]);
        puts(transition_afd.transitions->destiny_id);
        printf("------------------------\n");
        if (i != transition_afd.transitions_size-1)
            transition_afd.transitions = transition_afd.transitions->next;
    
    }
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





