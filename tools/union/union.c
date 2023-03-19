#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "union.h"
#include "../view/view.h"
#include "../struct/afd.h"

void exportUnion (char *input_file1, char *input_file2, char *output_file) {

    struct afd_struct afd1 = construct(input_file1);

    struct afd_struct afd2 = construct(input_file2);

    int states_size = 0;
    int alphabet_size = 0;
    int final_states_size = 0;
    int afd1_start_index = -1;
    int afd2_start_index = -1;
    char id_start[100]; /* ID do estado inicial */
    char alphabet[50]; /* União do alfabeto dos dois AFDs */


    /* Procura estado inicial de ambos AFDs e cria o id do estado inicial da união*/

    afd1_start_index = getStartStateIndex(afd1);
    afd2_start_index = getStartStateIndex(afd2);
    strncpy(id_start, afd1.states[afd1_start_index].identifier, 49);
    strncat(id_start, ",", 2); 
    strncat(id_start, afd2.states[afd2_start_index].identifier, 49);
    states_size ++;

    /* Cria o alfabeto da união */
    for (int i = 0; i < afd1.alphabet_size; i++) {
        alphabet[i] = afd1.alphabet[i].identifier;
    }
    alphabet_size = afd1.alphabet_size;
    for (int i = 0; i < afd2.alphabet_size; i++) {
        alphabet[alphabet_size] = afd2.alphabet[i].identifier;
        alphabet_size++;
    }

    /* Remove símbolos duplicados */
    for (int i = 0; i < alphabet_size; i++) {
        for (int j = i + 1; j < alphabet_size; j++) {
            if (alphabet[i] == alphabet[j]) {
                for (int k = j; k < alphabet_size; k++) {
                    alphabet[k] = alphabet[k + 1];
                }
                alphabet_size--;
                j--;
            }
        }
    }

    for (int i = 0; i < alphabet_size; i++) {
        printf("%c", alphabet[i]);
    }
    printf("\n----------------\n");


    /* puts(id_start);
    puts(alphabet); */

    return;
}