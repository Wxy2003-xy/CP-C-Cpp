#include <iostream>
#include <ctype.h>
int validate_instruction_format_string(char*);
int hex_to_binary(char* hex, uint32_t* bin);
int binary_to_hex(uint32_t* bin, char* hex);
int parse_instruction_type(char*);
int parse_R_instruction(uint32_t* input, uint8_t* rs, uint8_t* rt, uint8_t* rd, uint8_t* shamt, uint8_t* func);
int parse_I_instruction(uint32_t* input, uint8_t* opcode, uint8_t* rs, uint8_t* rt, uint16_t* immd);
int parse_J_instruction(uint32_t* input, uint32_t* addr);


int main() {
    return 0;
}

int validate_instruction_format_string(char* instr) {
    int len = sizeof(instr) / sizeof(char);
    return len == 32 ? 1 : 0;
}

int hex_to_binary(char* hex, uint32_t* bin) {
    
}
