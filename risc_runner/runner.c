#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Defining COVERAGE generates an instruciton coverage report */
//#define COVERAGE

/* Maxiumum memory (in int32_t */
#define MAX_MEM 8192
#define MAX_MEM_BYTES (MAX_MEM * 4)

typedef enum Opcode {
  Invalid,
  MOV,  /* ra := rb                      */
  ADD,  /* ra := rb + rc                 */
  SUB,  /* ra := rb - rc                 */
  MUL,  /* ra := rb * rc                 */
  DIV,  /* ra := rb / rc                 */
  MOD,  /* ra := rb % rc                 */
  LSL,  /* ra := rb << rc                */
  ASR,  /* ra := rb >> rc                */
  AND,  /* ra := rb & rc                 */
  OR,   /* ra := rb | rc                 */
  XOR,  /* ra := rb ^ rc                 */
  ANN,  /* ra := rb & ~n                 */
  CMP,  /* rb - rc, affects conditions   */
  MOVI, /* ra := offset                  */
  ADDI, /* ra := rb + offset             */
  SUBI, /* ra := rb - offset             */
  MULI, /* ra := rb * offset             */
  DIVI, /* ra := rb / offset             */
  MODI, /* ra := rb % offset             */
  LSLI, /* ra := rb << immediate         */
  ASRI, /* ra := rb >> immediate         */
  ANDI, /* ra := rb & immediate          */
  ORI,  /* ra := rb | immediate          */
  XORI, /* ra := rb ^ immediate          */
  ANNI, /* ra := rb & ~immediate         */
  CMPI, /* rb - offset                   */
  LDW,  /* ra := Mem[rb + offset] (word) */
  LDB,  /* ra := Mem[rb + offset] (byte) */
  STW,  /* Mem[rb + offset] := ra (word) */
  STB,  /* Mem[rb + offset] := ra (byte) */
  CJP,  /* Case jump (offset)            */
  BL,   /* LR := PC + 1, PC := offset    */
  BLr,  /* LR := PC + 1, PC := rc        */
  Br,   /* PC := ra (usually LR)         */
  B,    /* branch always                 */
  BF,   /* branch never, basically NOP   */
  BEQ,
  BNE,
  BLT,
  BGE,
  BLE,
  BGT,
  BHI,

  HALT,
} Opcode;

const char *INSTR_NAMES[] = {
    "Invalid", "MOV",  "ADD",  "SUB",  "MUL",  "DIV",  "MOD",  "LSL",  "ASR",
    "AND",     "OR",   "XOR",  "ANN",  "CMP",  "MOVI", "ADDI", "SUBI", "MULI",
    "DIVI",    "MODI", "LSLI", "ASRI", "ANDI", "ORI",  "XORI", "ANNI", "CMPI",
    "LDW",     "LDB",  "STW",  "STB",  "CJP",  "BL",   "BLr",  "Br",   "B",
    "BF",      "BEQ",  "BNE",  "BLT",  "BGE",  "BLE",  "BGT",  "BHI",

    "HALT",
};

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

const char *REG_NAMES[] = {
    "R0", "R1", "R2",  "R3",  "R4",  "R5", "R6", "R7",
    "R8", "R9", "R10", "R11", "R12", "GB", "SP", "LR",
};

typedef struct Instruction {
  Opcode opcode;
  Register ra;
  Register rb;
  Register rc;
  int offset;
} Instruction;

#include "risc_code.txt"

#ifdef COVERAGE
uint32_t visited_ip[(sizeof(PROGRAM) / sizeof(Instruction)) / 32 + 1];
#endif

void line(const char *reg0, int32_t r0, const char *reg1, int32_t r1,
          int32_t mem, uint8_t *contents) {
  printf(
      "%s %08x  %s %08x    %04x: %02x %02x %02x %02x  %02x %02x %02x %02x  "
      "%02x %02x %02x %02x  %02x %02x %02x %02x\n",
      reg0, r0, reg1, r1, mem, contents[0], contents[1], contents[2],
      contents[3], contents[4], contents[5], contents[6], contents[7],
      contents[8], contents[9], contents[10], contents[11], contents[12],
      contents[13], contents[14], contents[15]);
}

void dumpstate(int pc, int32_t *regs, uint8_t *mem) {
  line("R0", regs[0], " R8", regs[8], 0 * 16, mem);
  line("R1", regs[1], " R9", regs[9], 1 * 16, mem + 1 * 16);
  line("R2", regs[2], "R10", regs[10], 2 * 16, mem + 2 * 16);
  line("R3", regs[3], "R11", regs[11], 3 * 16, mem + 3 * 16);
  line("R4", regs[4], "R12", regs[12], MAX_MEM_BYTES - 4 * 16,
       mem + MAX_MEM_BYTES - 4 * 16);
  line("R5", regs[5], " GB", regs[GB], MAX_MEM_BYTES - 3 * 16,
       mem + MAX_MEM_BYTES - 3 * 16);
  line("R6", regs[6], " SP", regs[SP], MAX_MEM_BYTES - 2 * 16,
       mem + MAX_MEM_BYTES - 2 * 16);
  line("R7", regs[8], " LR", regs[LR], MAX_MEM_BYTES - 1 * 16,
       mem + MAX_MEM_BYTES - 1 * 16);
  if (pc < 0) {
    printf("TRAP %d\n", pc);
  } else {
    for (int instr = ((pc - 8) < 0) ? 0 : (pc - 8); instr <= pc; instr++) {
      Opcode op = PROGRAM[instr].opcode;
      Register a = PROGRAM[instr].ra;
      Register b = PROGRAM[instr].rb;
      Register c = PROGRAM[instr].rc;
      int offset = PROGRAM[instr].offset;
      printf("%5d: %s %s, %s, %s, #%d\n", instr, INSTR_NAMES[op], REG_NAMES[a],
             REG_NAMES[b], REG_NAMES[c], offset);
    }
  }
}

void do_trap(int pc, int32_t *regs, int32_t *mem) {
  if (pc == -1) {
    fputs("NIL derefernce\n", stderr);
    pc = regs[LR];
    dumpstate(pc, regs, (uint8_t *)mem);
    exit(1);
  } else if (pc == -2) {
    fputs("Array index out of bounds\n", stderr);
    pc = regs[LR];
    dumpstate(pc, regs, (uint8_t *)mem);
    exit(1);
  } else if (pc == -3) {
    fputs("ASSERT failure\n", stderr);
    pc = regs[LR];
    dumpstate(pc, regs, (uint8_t *)mem);
    exit(1);
  } else if (pc == -10) {
    /* Out.Int */
    printf("%d", regs[0]);
  } else if (pc == -12) {
    /* Out.Char */
    putchar(regs[0] & 0xff);
  } else if (pc == -13) {
    /* Out.Str */
    fputs(((const char *)mem) + regs[0], stdout);
  } else if (pc == -15) {
    /* Out.Ln */
    putchar('\n');
  } else {
    fprintf(stderr, "Bad trap %d, %d", pc, mem[0]);
    pc = regs[LR];
    dumpstate(pc, regs, (uint8_t *)mem);
    exit(1);
  }
}

void copy_strings_to_mem(uint8_t *mem) {
  for (size_t i = 0; i < sizeof(STRING_POOL); i++) {
    mem[i + STRING_POOL_START] = STRING_POOL[i];
  }
}

#ifdef COVERAGE
void set_visited(int pc) {
  int loc = pc / 32;
  int bitLoc = pc % 32;
  visited_ip[loc] |= 1 << bitLoc;
}

void print_unvisited(void) {
  printf("Unvisted instructions:\n");
  for (size_t pc = 0; pc < (sizeof(PROGRAM) / sizeof(Instruction)); pc++) {
    if ((visited_ip[pc / 32] & (1 << pc % 32)) == 0) {
      printf("%d\n", pc);
    }
  }
}
#endif

void interpret(void) {
  int pc = START_PC;
  int32_t r[16];
  int32_t mem[MAX_MEM];
  bool zFlag;

#ifdef COVERAGE
  for (size_t ip = 0; ip < (sizeof(visited_ip) / sizeof(uint32_t)); ip++) {
    visited_ip[ip] = 0;
  }
#endif
  zFlag = false;
  r[GB] = 0;
  r[SP] = MAX_MEM_BYTES - 4;
  for (int i = 0; i < MAX_MEM; i++) {
    mem[i] = 0;
  }
  copy_strings_to_mem((uint8_t *)mem);
  int left = 0; /* previous compare */
  int right = 0;
  while (1) {
#ifdef COVERAGE
    set_visited(pc);
#endif
    if (pc < 0) {
      do_trap(pc, r, mem);
      pc = r[LR];
      continue;
    }
    Opcode op = PROGRAM[pc].opcode;
    Register a = PROGRAM[pc].ra;
    Register b = PROGRAM[pc].rb;
    Register c = PROGRAM[pc].rc;
    int offset = PROGRAM[pc].offset;
#if 0
    dumpstate(pc, r, (uint8_t *)mem);
#endif
    pc++;
    switch (op) {
      case MOV:
        r[a] = r[b];
        break;
      case ADD:
        r[a] = r[b] + r[c];
        zFlag = r[a] == 0;
        break;
      case SUB:
        left = r[b];
        right = r[c];
        r[a] = r[b] - r[c];
        zFlag = r[a] == 0;
        break;
      case MUL:
        r[a] = r[b] * r[c];
        zFlag = r[a] == 0;
        break;
      case DIV:
        r[a] = r[b] / r[c];
        zFlag = r[a] == 0;
        break;
      case MOD:
        r[a] = r[b] % r[c];
        zFlag = r[a] == 0;
        break;
      case LSL:
        r[a] = r[b] << r[c];
        zFlag = r[a] == 0;
        break;
      case ASR:
        r[a] = r[b] >> r[c];
        zFlag = r[a] == 0;
        break;
      case AND:
        r[a] = r[b] & r[c];
        zFlag = r[a] == 0;
        break;
      case OR:
        r[a] = r[b] | r[c];
        zFlag = r[a] == 0;
        break;
      case XOR:
        r[a] = r[b] ^ r[c];
        zFlag = r[a] == 0;
        break;
      case ANN:
        r[a] = r[b] & ~r[c];
        zFlag = r[a] == 0;
        break;
      case CMP:
        left = r[b];
        right = r[c];
        zFlag = left == right;
        break;
      case MOVI:
        r[a] = offset;
        break;
      case ADDI:
        r[a] = r[b] + offset;
        zFlag = r[a] == 0;
        break;
      case SUBI:
        left = r[b];
        right = offset;
        r[a] = r[b] - offset;
        zFlag = r[a] == 0;
        break;
      case MULI:
        r[a] = r[b] * offset;
        zFlag = r[a] == 0;
        break;
      case DIVI:
        r[a] = r[b] / offset;
        zFlag = r[a] == 0;
        break;
      case MODI:
        r[a] = r[b] % offset;
        zFlag = r[a] == 0;
        break;
      case LSLI:
        r[a] = r[b] << offset;
        zFlag = r[a] == 0;
        break;
      case ASRI:
        r[a] = r[b] >> offset;
        zFlag = r[a] == 0;
        break;
      case ANDI:
        r[a] = r[b] & offset;
        zFlag = r[a] == 0;
        break;
      case ORI:
        r[a] = r[b] | offset;
        zFlag = r[a] == 0;
        break;
      case XORI:
        r[a] = r[b] ^ offset;
        zFlag = r[a] == 0;
        break;
      case ANNI:
        r[a] = r[b] & ~offset;
        zFlag = r[a] == 0;
        break;
      case CMPI:
        left = r[b];
        right = offset;
        zFlag = left == right;
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
      case LDB: {
        int address = r[b] + offset;
        r[a] = mem[address / 4];
        r[a] = (r[a] >> ((address % 4) * 8)) & 0xff;
        break;
      }
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
      case STB: {
        int address = r[b] + offset;
        int current = mem[address / 4];
        int mask = 0xff << ((address % 4) * 8);
        current = current & (~mask);
        current = current | ((r[a] & 0xff) << ((address % 4) * 8));
        mem[address / 4] = current;
        break;
      }
      case CJP:
        pc = offset;
        break;
      case BL:
        r[LR] = pc;
        pc = offset;
        break;
      case BLr:
        r[LR] = pc;
        pc = r[c];
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
        if (zFlag) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BNE:
        if (!zFlag) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BLT:
        if (left < right) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BLE:
        if (left <= right) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BGT:
        if (left > right) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BGE:
        if (left >= right) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case BHI:
        /* used for array bounds checks. This corresponds to */
        /* CMP length, index                                 */
        /* BHI -2                                            */
        /* This could be accomplished with carry flags, but  */
        /* wanted to make sure it was correct in C.          */
        if ((right < 0) || (right >= left)) {
          if (a) {
            r[LR] = pc;
          }
          pc = offset;
        }
        break;
      case Invalid:
        return;
      case HALT:
#ifdef COVERAGE
        print_unvisited();
#endif
        return;
    }
  }
}

int main(int argc, char **argv) {
  /*
  printf("%s(%d): %d %zd\n", argv[0], argc, PROGRAM[0].opcode,
         sizeof(PROGRAM) / sizeof(Instruction));
  */
  if (argc && argv) {
    interpret();
  }
  return 0;
}
