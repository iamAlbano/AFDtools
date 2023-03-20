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

struct afd_struct construct (char *input_file);
int getStartStateIndex (afd_struct afd);
int getSymbolIndex (afd_struct afd, char symbol);

#endif
