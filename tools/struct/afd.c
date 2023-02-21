#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "afd.h"

state *createState(state *next_state, char *identifier, int is_start, int is_final)
{
    state *new_state = (state *)malloc(sizeof(state));
    
    strcpy(new_state->identifier, identifier);
    new_state->is_final = is_start;
    new_state->is_final = is_final;
    new_state->next = next_state;

    return new_state;
}

void setStates(afd_struct *afd, char states[][50], int stts_size, char i_state[50], char f_states[][50], int f_states_size) {
    
    state *state_aux = NULL;
    for (int i = 0; i < stts_size; i++) {

        int is_start = strcmp(states[i], i_state) == 0 ? 1 : 0;

        int is_final = 0;
        for (int j = 0; j < f_states_size; j++) {
            if (strcmp(states[i], f_states[j]) == 0) {
                is_final = 1;
                break;
            }
        }
        
        state_aux = createState(state_aux, states[i], is_start, is_final);
    }
    afd->states = state_aux; 
}

void printAFD (afd_struct afd) {
    printf("Estados: \n");
    struct afd_struct state_aux = afd;
    while (state_aux.states != NULL) {
        puts(state_aux.states->identifier);
        puts(state_aux.states->is_start == 1 ? "É inicial" : "Não é inicial");
        puts(state_aux.states->is_final == 1 ? "É final" : "Não é final");
        printf("------------------\n");
        state_aux.states = state_aux.states->next;
    }
}


struct afd_struct construct (char *input_file, char *output_file) {

    FILE *afd_file = fopen(input_file, "r");

    /* linhas do arquivo */
    char file_line[50];

    /* lê a quantidade de estados */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int states_size = atoi(file_line);

    /* cria array contendo todos os estados */
    char states_arr[states_size][50];

    for (int i = 0; i < states_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        strcpy(states_arr[i], file_line);
    }

    /* lê a quantidade de símbolos */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int symbols_size = atoi(file_line);

    /* cria array contendo todos os simbolos */
    char symbols_arr[symbols_size];

    for (int i = 0; i < symbols_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        symbols_arr[i] = file_line[0];
    }

    /* lê a quantidade de transicoes */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int transitions_size = atoi(file_line);

    /* cria array contendo todas transicoes */
    char transitions_arr[states_size][50];

    for (int i = 0; i < transitions_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        strcpy(transitions_arr[i], file_line);
    }

    /* lê o estado inicial */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    char initial_state[50];
    strncpy(initial_state, file_line, 50);

    /* lê a quantidade de estados finais */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int final_states_size = atoi(file_line);

    /* cria array contendo todos os estados finais */
    char final_states_arr[final_states_size][50];

    for (int i = 0; i < final_states_size; i++) {
        fgets(file_line, 50, afd_file);
        file_line[strcspn(file_line, "\n")] = 0;
        strcpy(final_states_arr[i], file_line);
    }


    
    struct afd_struct afd;

    setStates(&afd, states_arr, states_size, initial_state, final_states_arr, final_states_size);

    printAFD(afd);

    fclose(afd_file);

    return afd;
}





