#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum Opcode {
  Invalid,
  MOV,  /* ra := rb                      */
  ADD,  /* ra := rb + rc                 */
  SUB,  /* ra := rb - rc                 */
  MUL,  /* ra := rb * rc                 */
  DIV,  /* ra := rb / rc                 */
  MOD,  /* ra := rb % rc                 */
  CMP,  /* rb - rc, affects conditions   */
  MOVI, /* ra := offset                  */
  ADDI, /* ra := rb + offset             */
  SUBI, /* ra := rb - offset             */
  MULI, /* ra := rb * offset             */
  DIVI, /* ra := rb / offset             */
  MODI, /* ra := rb % offset             */
  CMPI, /* rb - offset                   */
  LDW,  /* ra := Mem[rb + offset] (word) */
  LDB,  /* ra := Mem[rb + offset] (byte) */
  STW,  /* Mem[rb + offset] := ra (word) */
  STB,  /* Mem[rb + offset] := ra (byte) */
  BL,   /* LR := PC + 1, PC := offset    */
  Br,   /* PC := ra (usually LR)         */
  B,    /* branch always                 */
  BF,   /* branch never, basically NOP   */
  BEQ,
  BNE,
  BLT,
  BGE,
  BLE,
  BGT,

  HALT,
} Opcode;

typedef enum Register {
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  GB,
  SP,
  LR,
} Register;

typedef struct Instruction {
  Opcode opcode;
  Register ra;
  Register rb;
  Register rc;
  int offset;
} Instruction;

#include "risc_code.txt"

void do_trap(int pc, int32_t *regs, int32_t *mem) {
  if (pc == -10) {
    /* Out.Int */
    printf("%d", regs[0]);
  } else if (pc == -12) {
    /* Out.Char */
    putchar(regs[0] & 0xff);
  } else if (pc == -15) {
    /* Out.Ln */
    putchar('\n');
  } else {
    fprintf(stderr, "Bad trap %d, %d", pc, mem[0]);
    exit(1);
  }
  pc = regs[LR];
}

void interpret(void) {
  int pc = START_PC;
  int32_t r[16];
  int32_t mem[8192];

  r[GB] = 0;
  r[SP] = 8191;
  for (int i = 0; i < 8192; i++) {
    mem[i] = 0;
  }
  int left = 0; /* previous compare */
  int right = 0;
  while (1) {
    Opcode op = PROGRAM[pc].opcode;
    Register a = PROGRAM[pc].ra;
    Register b = PROGRAM[pc].rb;
    Register c = PROGRAM[pc].rc;
    int offset = PROGRAM[pc].offset;
#if 0
    printf("pc: %d op: %d a: %d b: %d c: %d offset: %d\n", pc, op, a, b, c, offset);
    for (int i=0; i < 16; i++) {
      printf("%04x ", r[i]);
    }
    putchar('\n');
#endif
    pc++;
    switch (op) {
      case MOV:
        r[a] = r[b];
        break;
      case ADD:
        r[a] = r[b] + r[c];
        break;
      case SUB:
        r[a] = r[b] - r[c];
        break;
      case MUL:
        r[a] = r[b] * r[c];
        break;
      case DIV:
        r[a] = r[b] / r[c];
        break;
      case MOD:
        r[a] = r[b] % r[c];
        break;
      case CMP:
        left = r[b];
        right = r[c];
        break;
      case MOVI:
        r[a] = offset;
        break;
      case ADDI:
        r[a] = r[b] + offset;
        break;
      case SUBI:
        r[a] = r[b] - offset;
        break;
      case MULI:
        r[a] = r[b] * offset;
        break;
      case DIVI:
        r[a] = r[b] / offset;
        break;
      case MODI:
        r[a] = r[b] % offset;
        break;
      case CMPI:
        left = r[b];
        right = offset;
        break;
      case LDW: {
        int address = r[b] + offset;
        if (address >= 0) {
          r[a] = mem[address / 4];
        } else if (address == -1) {
          scanf("%d", &r[a]);
        }
        break;
      }
      case LDB:
        r[a] = mem[r[b] + offset];
        break;
      case STW: {
        int address = r[b] + offset;
        if (address >= 0) {
          mem[address / 4] = r[a];
        } else if (address == -1) {
          printf("%4d", r[a]);
        } else if (address == -2) {
          putchar(r[a] & 0xff);
        } else if (address == -3) {
          putchar('\n');
        }
        break;
      }
      case STB:
        mem[r[b] + offset] = r[a];
        break;
      case BL:
        r[LR] = pc;
        pc = offset;
        if (pc <= -10) {
          do_trap(pc, r, mem);
        }
        break;
      case Br:
        pc = r[a];
        break;
      case B:
        pc = offset;
        break;
      case BF:
        break;
      case BEQ:
        if (left == right) {
          pc = offset;
        }
        break;
      case BNE:
        if (left != right) {
          pc = offset;
        }
        break;
      case BLT:
        if (left < right) {
          pc = offset;
        }
        break;
      case BLE:
        if (left <= right) {
          pc = offset;
        }
        break;
      case BGT:
        if (left > right) {
          pc = offset;
        }
        break;
      case BGE:
        if (left >= right) {
          pc = offset;
        }
        break;
      case Invalid:
        return;
      case HALT:
        return;
    }
  }
}

int main(int argc, char **argv) {
  printf("%s(%d): %d %d\n", argv[0], argc, PROGRAM[0].opcode,
         sizeof(PROGRAM) / sizeof(Instruction));
  interpret();
  return 0;
}
