#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "../struct/afd.h"

/*
    Funções para criar o arquivo .dot a partir do arquivo de entrada
*/

void write_final_states (afd_struct afd, FILE *afd_file) {
    fprintf(afd_file, "\tnode [shape = doublecircle];");
    for (int i = 0; i < afd.states_size; i++) {
        if (afd.states[i].is_final) {
            fprintf(afd_file, " %s", afd.states[i].identifier);
        }
    }
    fprintf(afd_file, ";\n");
}

void write_transitions (afd_struct afd, FILE *afd_file) {

    printf("Transições: \n");
    struct afd_struct state_aux = afd;
    for (int i = 0; i < state_aux.states_size; i++) {
        for (int j = 0; j < state_aux.alphabet_size; j++) {
            if (state_aux.transitions[i][j] != -1) {
                fprintf(afd_file, "\t%s -> %s [label = \"%c\"];\n", afd.states[i].identifier, afd.states[afd.transitions[i][j]].identifier, afd.alphabet[j].identifier);
                printf("%d - %d = %d\n", i, j, state_aux.transitions[i][j]);
            }
        }
    }
}

int view (char *input_file, char *output_file) {

    struct afd_struct afd = construct(input_file, output_file);
    FILE *afd_file = fopen(output_file, "w");

    if (afd_file == NULL) {
        printf("Erro ao exportar o arquivo .dot");
        exit(-1);
    }

    fprintf(afd_file, "digraph finite_state_machine {\n");
    fprintf(afd_file, "\tfontname=\"Helvetica,Arial,sans-serif\";\n");
    
    fprintf(afd_file, "\tnode [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(afd_file, "\tedge [fontname=\"Helvetica,Arial,sans-serif\"]\n");
    fprintf(afd_file, "\trankdir=LR;\n");

    write_final_states(afd, afd_file);

    fprintf(afd_file, "\tnode [shape = circle];\n");
    write_transitions(afd, afd_file);    
    fprintf(afd_file, "}");

    fclose(afd_file);
    printf("Arquivo .dot exportado com sucesso!\n"); 
   
    return 0;
}