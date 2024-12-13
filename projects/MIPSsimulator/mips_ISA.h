#ifndef MIPS_ISA_H
#define MIPS_ISA_H

#include <iostream>
#include <ctype.h>
#include <string.h>

enum INSTRUCTION_TYPE {
    r,
    i,
    j,
};

enum R_MNEMONIC {
    ADD,
    SUB,
    AND,
    OR,
    NOR,
    SLL,
    SRL,
    SLT,
};

enum I_MNEMONIC {
    ADDI,
    SUBI,
    ANDI,
    ORI,
    NORI,
    BEQ,
    BNE,
    LW,
    LUI,
    SW,
};

enum J_MNEMONIC {
    JUMP
};
// bitfield implemenation of uint5_t
struct uint5_t {
    uint8_t value : 5; // Use 5 bits from a uint8_t
    uint5_t(uint8_t val = 0) { 
        value = val & 0b11111; // Ensure the value fits in 5 bits
    }
    uint5_t& operator=(uint8_t val) {
        value = val & 0b11111;
        return *this;
    }
    operator uint8_t() const {
        return value;
    }
};
// uint6_t for opcode and func
struct uint6_t {
    uint8_t value : 6;
    uint6_t(uint8_t val = 0) { 
        value = val & 0b111111;
    }
    uint6_t& operator=(uint8_t val) {
        value = val & 0b111111;
        return *this;
    }
    operator uint8_t() const {
        return value;
    }
};
// uint2_t for aluop
struct uint2_t {
    uint8_t value : 2;
    uint2_t(uint8_t val = 0) { 
        value = val & 0b11;
    }
    uint2_t& operator=(uint8_t val) {
        value = val & 0b11;
        return *this;
    }
    operator uint8_t() const {
        return value;
    }
};
// uint4_t for alu_ctrl
struct uint4_t {
    uint8_t value : 4;
    uint4_t(uint8_t val = 0) { 
        value = val & 0b1111;
    }
    uint4_t& operator=(uint8_t val) {
        value = val & 0b1111;
        return *this;
    }
    operator uint8_t() const {
        return value;
    }
};
struct uint7_t {
    uint8_t value : 7;
    uint7_t(uint8_t val = 0) { 
        value = val & 0b1111111;
    }
    uint7_t& operator=(uint8_t val) {
        value = val & 0b1111111;
        return *this;
    }
    operator uint8_t() const {
        return value;
    }
};
int validate_instruction_format_string(char*);
int hex_to_binary(char* hex, uint32_t* bin);
int binary_to_hex(uint32_t* bin, char* hex);
INSTRUCTION_TYPE instruction_type(uint32_t* input);
int parse_R_instruction(uint32_t* input, uint5_t* rs, uint5_t* rt, uint5_t* rd, uint5_t* shamt, uint6_t* func);
int parse_I_instruction(uint32_t* input, uint6_t* opcode, uint5_t* rs, uint5_t* rt, uint16_t* immd);
int parse_I_instruction_load_upper(uint32_t* input, uint6_t* opcode, uint5_t* rs, uint5_t* rt, uint16_t* immd);
int parse_J_instruction(uint32_t* input, uint32_t* addr, uint32_t* PC);

int validate_instruction_format_string(char* instr) {
    int len = strlen(instr);
    return len == 32 ? 1 : 0;
}

int hex_to_binary(char* hex, uint32_t* bin) {
  //TODO   
  return 0;
}

int binary_to_hex(uint32_t* bin, char* hex) {
  //TODO
  return 0;
}

INSTRUCTION_TYPE instruction_type(uint32_t* instr) {
    if ((*instr & 0xFC000000) == 0x00000000)  // Example logic for R-type
        return r;
    else if ((*instr & 0xFC000000) == 0x0C000000)  // Example for J-type
        return i;
    else
        return j;
}

int parse_R_instruction(uint32_t* input, uint5_t* rs, uint5_t* rt, uint5_t* rd, uint5_t* shamt, uint6_t* func) {
    uint32_t instr_value = *input;
    *rs = instr_value >> 21;
    *rt = (instr_value & 0x001F0000) >> 16;
    *rd = (instr_value & 0x0000F800) >> 11;
    *shamt = (instr_value & 0x000007C0) >> 6;
    *func = instr_value & 0x0000003F;
    return 0;
}

int parse_I_instruction(uint32_t* input, uint6_t* opcode, uint5_t* rs, uint5_t* rt, uint16_t* immd) {
    uint32_t instr_value = *input;
    *opcode = instr_value >> 26;
    *rs =  (instr_value & 0x03E00000) >> 21;
    *rt = (instr_value & 0x001F0000) >> 16;
    *immd = instr_value & 0x0000FFFF;
    return 0;
}

int parse_J_instruction(uint32_t* input, uint32_t* addr, uint32_t* PC) {
    uint32_t instr_value = *input;
    uint32_t address_PC = *PC & 0xF0000000;
    uint32_t address_value = ((instr_value & 0x03FFFFFF) << 2) | address_PC;
    *addr = address_value;
    return 0;
}

// -----* parse R type instructions *-----


#endif
