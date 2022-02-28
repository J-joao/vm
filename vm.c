#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vm.h"

int main(int argc, const char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    char string[6];
    int i = 0;

    if (!fp) {
        exit(1);
    }

    /* allocate input file's content into array */
    while(fgets(string, 6, fp)) {
        program[i] = (int)strtol(string, NULL, 16);
        i++;
    }
    
    run();
    return 0;
}

