#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "instructions/instructions.h"

#define GRN "\e[1;32m"
#define BLU "\e[1;34m"
#define RST "\e[0m"

int64_t regs[4] = {0};
bool running = 1;

void vm_halt() {
    running = 0;
}

void vm_add(int dest, int mode, int64_t src) {
    if (mode == 0) {
        regs[dest] += src;
        printf("add r%d, 0x%lX\n", dest, src);
    }
    else {
        regs[dest] += regs[src];
        printf("add r%d, r%ld\n", dest, src);
    }
}

void vm_sub(int dest, int mode, int64_t src) {
    if (mode == 0) {
        regs[dest] -= src;
        printf("sub r%d, 0x%lX\n", dest, src);
    }
    else {
        regs[dest] -= regs[src];
        printf("sub r%d, r%ld\n", dest, src);
    }
}

void vm_mul(int dest, int mode, int64_t src) {
    if (mode == 0) {
        regs[dest] *= src;
        printf("mul r%d, 0x%lX\n", dest, src);
    }
    else {
        regs[dest] *= regs[src];
        printf("mul r%d, r%ld\n", dest, src);
    }
}

void vm_div(int dest, int mode, int64_t src) {
    if (mode == 0) {
        regs[dest] /= src;
        printf("div r%d, 0x%lX\n", dest, src);
    }
    else {
        regs[dest] /= regs[src];
        printf("div r%d, r%ld\n", dest, src);
    }
}

void vm_load(int dest, int mode, int64_t src) {
    if (mode == 0) {
        regs[dest] = src;
        printf("load r%d, 0x%lX\n", dest, src);
    }
    else {
        regs[dest] = regs[src];
        printf("load r%d, r%ld\n", dest, src);
    }
}

void regs_status() {
    for (int i = 0; i < 4; i++)
        printf(GRN"r%d"RST" [%lX]  ", i, regs[i]);
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    int id, dest, mode;
    int64_t src;

    if (!fp) {
        fprintf(stderr, "file \"%s\" was not found!\n", argv[1]);
        exit(1);
    }

    while(running && fscanf(fp, "%i %i %i %lX", &id, &dest, &mode, &src) == 4) {
        printf(BLU"OPCODE:   "RST"%i %i %i %lX\n", id, dest, mode, src);

        if (ferror(fp)) {
            fprintf(stderr, "ferror() occurance!\n");
            exit(1);
        }

        printf(BLU"ASSEMBLY: "RST);
        switch (id) {
            case 0:
                vm_halt(); break;
            case 1:
                vm_add(dest, mode, src); break;
            case 2:
                vm_sub(dest, mode, src); break;
            case 3:
                vm_mul(dest, mode, src); break;
            case 4:
                vm_div(dest, mode, src); break;
            case 5:
                vm_load(dest, mode, src); break;
        }
        regs_status();
    }

    fclose(fp);
    return 0;
}
