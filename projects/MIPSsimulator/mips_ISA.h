#ifndef MIPS_ISA_H
#define MIPS_ISA_H

#include <iostream>
#include <ctype.h>

enum INSTRUCTION_TYPE {
    R,
    I,
    J,
};

int validate_instruction_format_string(char*);
int hex_to_binary(char* hex, uint32_t* bin);
int binary_to_hex(uint32_t* bin, char* hex);
INSTRUCTION_TYPE instruction_type(uint32_t* input);
int parse_R_instruction(uint32_t* input, uint8_t* rs, uint8_t* rt, uint8_t* rd, uint8_t* shamt, uint8_t* func);
int parse_I_instruction(uint32_t* input, uint8_t* opcode, uint8_t* rs, uint8_t* rt, uint16_t* immd);
int parse_I_instruction_load_upper(uint32_t* input, uint8_t* opcode, uint8_t* rs, uint8_t* rt, uint16_t* immd);
int parse_J_instruction(uint32_t* input, uint32_t* addr, uint32_t* PC);



int main() {
    return 0;
}

int validate_instruction_format_string(char* instr) {
    int len = sizeof(instr) / sizeof(char);
    return len == 32 ? 1 : 0;
}

int hex_to_binary(char* hex, uint32_t* bin) {
  //TODO   
}

int binary_to_hex(uint32_t* bin, char* hex) {
  //TODO
}

INSTRUCTION_TYPE instruction_type(uint32_t* instr) {
    if ((*instr & 0xFC000000) == 0x00000000)  // Example logic for R-type
        return R;
    else if ((*instr & 0xFC000000) == 0x0C000000)  // Example for J-type
        return J;
    else
        return I;
}

int parse_R_instruction(uint32_t* input, uint8_t* rs, uint8_t* rt, uint8_t* rd, uint8_t* shamt, uint8_t* func) {
    uint32_t instr_value = *input;
    *rs = instr_value >> 21;
    *rt = instr_value & 0x001F0000 >> 16;
    *rd = instr_value & 0x0000F800 >> 11;
    *shamt = instr_value & 0x000007C0 >> 6;
    *func = instr_value & 0x0000003F;
    return 0;
}

int parse_I_instruction(uint32_t* input, uint8_t* opcode, uint8_t* rs, uint8_t* rt, uint16_t* immd) {
    uint32_t instr_value = *input;
    *opcode = instr_value >> 26;
    *rs =  instr_value & 0x03E00000 >> 21;
    *rt = instr_value & 0x001F0000 >> 16;
    *immd = instr_value & 0x0000FFFF;
    return 0;
}

int parse_I_instruction_load_upper(uint32_t* input, uint8_t* opcode, uint8_t* rs, uint8_t* rt, uint16_t* immd) {
    uint32_t instr_value = *input;
    *opcode = instr_value >> 26;
    *rs =  instr_value & 0x03E00000 >> 21;
    *rt = instr_value & 0x001F0000 >> 16;
    *immd = instr_value << 16;
    return 0;
}

int parse_J_instruction(uint32_t* input, uint32_t* addr, uint32_t* PC) {
    uint32_t instr_value = *input;
    uint32_t address_PC = *PC & 0xF0000000;
    uint32_t address_value = instr_value & 0x03FFFFFF << 2 | address_PC;
    return 0;
}

#endif
