#include <stdio.h>
#include <stdlib.h>

#include "complement.h"
#include "../view/view.h"
#include "../struct/afd.h"

struct afd_struct getComplement (struct afd_struct *afd) {

    afd->final_states_size = 0;
    for (int i = 0; i < afd->states_size; i++) {

        if (afd->states[i].is_final == 1){ 
            afd->states[i].is_final = 0; 
        } else {
            afd->states[i].is_final = 1;
            afd->final_states_size++;
        }

    }

}

void handleExportFile (afd_struct afd, char *output_file) {

    char file_extension[5];

    for (int i = 0; i < 4; i++) {
        file_extension[i] = output_file[(strlen(output_file) - 4) + i];
    }

    if (strcmp(file_extension,".dot") == 0)
        createDotFile(afd, output_file);
    else if (strcmp(file_extension,".txt") == 0)
        createTxtFile(afd, output_file); 
    else
        printf("Extensão de arquivo inválida.\n");
}

struct afd_struct exportComplement (char *input_file, char *output_file) {

    struct afd_struct afd = construct(input_file);

    getComplement(&afd);

    handleExportFile(afd, output_file);

    return afd;
    
}