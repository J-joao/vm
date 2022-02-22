#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, const char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    char string[10];
    int i = 0;

    if (!fp) {
        exit(1);
    }

    /* allocate input file's content into array */
    while(fgets(string, 10, fp)) {
        program[i] = (int)strtol(string, NULL, 0);
        i++;
    }
    
    run();
    return 0;
}

