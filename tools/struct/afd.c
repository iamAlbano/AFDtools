#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "afd.h"

struct symbol *createSymbol (char *identifier, int index) {
    symbol *new_symbol = (symbol *)malloc(sizeof(symbol));

    new_symbol->identifier = identifier;
    new_symbol->index = index;

    return new_symbol;
}
struct state *createState(char *identifier, int is_start, int is_final, int index)
{
    state *new_state = (state *)malloc(sizeof(state));

    strcpy(new_state->identifier, identifier);
    new_state->is_start = is_start;
    new_state->is_final = is_final;
    new_state->index = index;

    return new_state;
}

void setStates(afd_struct *afd, char states[][50], int stts_size, char i_state[50], char f_states[][50], int f_states_size) {
    
    state *state_aux = NULL;
    afd->states_size = 0;
    afd->states = malloc(sizeof(state) * stts_size);
    for (int i = 0; i < stts_size; i++) {
        int is_start = strcmp(states[i], i_state) == 0 ? 1 : 0;

        int is_final = 0;
        for (int j = 0; j < f_states_size; j++) {
            if (strcmp(states[i], f_states[j]) == 0) {
                is_final = 1;
                break;
            }
        }
        
        state_aux = createState(states[i], is_start, is_final, i);
        afd->states[i] = *state_aux; 
        afd->states_size++;
    }
}

int geStateIndex (afd_struct afd, char *identifier) {
    for (int i = 0; i < afd.states_size; i++) {
        if (strcmp(afd.states[i].identifier, identifier) == 0)
            return i;
    }
    return -1;
}

int getSymbolIndex (afd_struct afd, char identifier) {
    for (int i = 0; i < afd.alphabet_size; i++) {
        if (afd.alphabet[i].identifier == identifier)
            return i;
    }
    return -1;
}

void setTransitions (afd_struct *afd, char transitions[][50], int transitions_size) {
    char origin[50];
    char symbol[50];
    char destiny[50];

    /* Iniciando transições com matriz vazia*/

    afd->transitions_size = 0;
    afd->transitions = malloc(sizeof(int*) * afd->states_size);

    for (int i = 0; i < transitions_size; i++) {
        afd->transitions[i] = malloc(sizeof(int));
        for (int j = 0; j < afd->alphabet_size; j++) {
            afd->transitions[i][j] = NULL;
        }
    }

    /* 
        Definindo matriz de transições com o indice da origem, símbolo 
        e o resultado como indice do destino 
    */
    for (int i = 0; i < transitions_size; i++) {
        
        sscanf(transitions[i], "%s %s %s", origin, symbol, destiny);

        int destiny_id = geStateIndex(*afd, destiny);
        int origin_id = geStateIndex(*afd, origin);
        int symbol_id = getSymbolIndex(*afd, symbol[0]);

        if (origin_id != -1 && symbol_id != -1 && destiny_id != -1) {
            afd->transitions[origin_id][symbol_id] = destiny_id;
            afd->transitions_size++;
        }
    }
    
}

void setAlphabet (afd_struct *afd, char alphabet[], int alphabet_size) {
    symbol *symbol_aux = NULL;
    afd->alphabet = malloc(sizeof(symbol) * alphabet_size);
    afd->alphabet_size = 0;

    for (int i = 0; i < alphabet_size; i++) {
        symbol_aux = createSymbol(alphabet[i], i);
        afd->alphabet[i] = *symbol_aux;
        afd->alphabet_size++;
    }
}

void printAFD (afd_struct afd) {
    struct afd_struct state_aux = afd;

    printf("Estados: \n");
    for (int i = 0; i < state_aux.states_size; i++) {
        printf("%s", state_aux.states[i].identifier);
        printf(" | %s ",state_aux.states[i].is_start == 1 ? "É inicial" : "Não é inicial");
        printf(" | %s ", state_aux.states[i].is_final == 1 ? "É final" : "Não é final");
        printf("\n----------------------------------\n");
    }

    printf("Alfabeto: ");
    for (int i = 0; i < state_aux.alphabet_size; i++) {
        state_aux.alphabet[i].index = i;
        printf("%c - ", state_aux.alphabet[i].identifier);
    }
    printf("\n------------------\n");


    printf("Transições: \n");

    for (int i = 0; i < state_aux.states_size; i++) {
        for (int j = 0; j < state_aux.alphabet_size; j++) {
            printf("%d - %d = %d\n", i, j, state_aux.transitions[i][j]);
        }
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
        symbols_arr[i] = file_line[0];
    }

    /* lê a quantidade de transicoes */
    fgets(file_line, 50, afd_file);
    file_line[strcspn(file_line, "\n")] = 0;
    int transitions_size = atoi(file_line);

    /* cria array contendo todas transicoes */
    char transitions_arr[transitions_size][50];

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
    setAlphabet(&afd, symbols_arr, symbols_size); 

    setTransitions(&afd, transitions_arr, transitions_size);

    printAFD(afd);   

    /* fclose(afd_file); */

    return afd; 
}





