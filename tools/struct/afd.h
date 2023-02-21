#ifndef CONSTRUCT
#define CONSTRUCT

typedef struct state {
    int is_final;
    int is_start;
    char identifier[50];
    struct state *next;
} state;

typedef struct transition {
    char symbols[50][50];
    int symbols_size;
    char origin_id[50];
    char destiny_id[50];
    struct transition *next;
} transition;

typedef struct afd_struct {
    int states_size;
    int alphabet_size;
    int transitions_size;
    char alphabet[50][50];
    struct state *states;
    struct transition *transitions;
} afd_struct;

struct afd_struct construct (char *input_file, char *output_file) ;
state *createState(state *next_state, char *identifier, int is_start, int is_final);
void setStates(afd_struct *afd, char states[][50], int stts_size, char i_state[50], char f_states[][50], int f_states_size);


#endif
