#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "../struct/afd.h"

int view (char *input_file, char *output_file) {

    struct afd_struct a = construct(input_file, output_file);
   
    return 0;
}