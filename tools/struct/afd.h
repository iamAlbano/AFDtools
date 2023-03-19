#ifndef CONSTRUCT
#define CONSTRUCT

typedef struct state {
    int is_final;
    int is_start;
    int index;
    char identifier[50];
} state;

typedef struct symbol {
    int index;
    char identifier;
} symbol;

typedef struct afd_struct {
    int states_size;
    int alphabet_size;
    int transitions_size;
    int final_states_size;

    state *states;
    symbol *alphabet;
    int **transitions;
} afd_struct;

/* 
Exemplo de estados
estado[0] = {
    int is_final = 1;
    int is_start = 0;
    int index = 0;
    char 'par';
}

estado[1] = {
    int is_final = 0;
    int is_start = 1;
    int index = 1;
    char 'impar';
} */

/* symbol[0] = {
    int index = 0;
    char identifier = '0';
} symbol;

symbol[1] = {
    int index = 1;
    char identifier = '1';
} symbol;

transicao[estado_indice][simbolo_indice]
transicao[0][0] = 1 <-- retorna o indice do estado que é resultado da transicao */

struct afd_struct construct (char *input_file);
int getStartStateIndex (afd_struct afd);
int getSymbolIndex (afd_struct afd, char symbol);

#endif
