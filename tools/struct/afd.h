#ifndef CONSTRUCT
#define CONSTRUCT

typedef struct state {
    char identifier[50];
    int is_final;
    int is_start;
    struct state *next;
} state;

typedef struct transition {
    char identifier[50];
    struct state *next;
} transition;

typedef struct afd_struct {
    state states;
    int states_size;
    char alphabet[50][50];
    int alphabet_size;
} afd_struct;

struct afd_struct construct (char *input_file, char *output_file) ;

#endif
