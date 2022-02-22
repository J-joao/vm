#ifndef _VM_H
#define _VM_H

#define REG_COUNT 4
#define GRN "\e[1;32m"
#define RST "\e[0m"

bool running = 1;
int iID = 0;    // instruction ID
int pc  = 0;    // program counter
int imm = 0;    // immediate value
int r1  = 0;
int r2  = 0;
int r3  = 0;
unsigned regs[REG_COUNT];
int program[] = {};

int fetch() {
    return program[pc++];
}

void decode(int instr) {
    iID  = (instr & 0xF000) >> 12; // 1111 0000 0000 0000
    r1   = (instr & 0x0F00) >>  8; // 0000 1111 0000 0000
    r2   = (instr & 0x00F0) >>  4; // 0000 0000 1111 0000
    r3   = (instr & 0x000F);       // 0000 0000 0000 1111
    imm  = (instr & 0x00FF);       // 0000 0000 1111 1111
}

/* evaluate the last decoded instruction */
void eval() {
    switch(iID) {
    case 0:
        /* halt */
        printf("halt\n");
        running = 0;
        break;
    case 1:
        /* loadi */
        printf("loadi r%d $%d\n", r1, imm);
        regs[r1] = imm;
        break;
    case 2:
        /* add */
        printf("add r%d r%d r%d\n", r1, r2, r3);
        regs[r1] = regs[r2] + regs[r3];
        break;
    case 3:
        /* sub */
        printf("sub r%d r%d r%d\n", r1, r2, r3);
        regs[r1] = regs[r2] - regs[r3];
        break;
    case 4:
        /* mul */
        printf("mul r%d r%d r%d\n", r1, r2, r3);
        regs[r1] = regs[r2] * regs[r3];
        break;
    case 5:
        /* div */
        printf("div r%d r%d r%d\n", r1, r2, r3);
        regs[r1] = regs[r2] / regs[r3];
        break;
    }
}

void status() {
    printf(GRN"status"RST": ");
    for(int i = 0; i < REG_COUNT; i++) {
        printf("r%d(%04X) ", i, regs[i]);
    }
    printf("\n");
}

void run() {
    while(running) {
        status();
        int instr = fetch();
        decode(instr);
        eval();
    }
    status();
}

#endif