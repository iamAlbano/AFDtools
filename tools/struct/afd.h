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

#endif
