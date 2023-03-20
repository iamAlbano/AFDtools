#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recognize.h"
#include "../struct/afd.h"

int recognizeWord (struct afd_struct afd, char *word) {
    
    int current_state_index = getStartStateIndex(afd);
    int word_size = strlen(word);
    int symbol_index = -1;
    int next_state_index = -1;

    for (int i = 0; i < word_size; i++) {
        symbol_index = getSymbolIndex(afd, word[i]);
        if (symbol_index == -1)
            return 0;
        next_state_index = afd.transitions[current_state_index][symbol_index];
        if (next_state_index == -1)
            return 0;
        current_state_index = next_state_index;
    }

    return (afd.states[current_state_index].is_final);
}

void recognize (char *afd_file, char *words_file, char *output_file) {

    struct afd_struct afd = construct(afd_file);

    FILE *words = fopen(words_file, "r");
    FILE *output = fopen(output_file, "w");

    if (output == NULL) {
        printf("Erro ao abrir arquivo");
        exit(-1);
    }

    char word[50];

    while (!feof(words)) {
        fscanf(words, "%s", word);
        fprintf(output, "%d\n", recognizeWord(afd, word));
    }

}