#ifndef MIPS_PARSER_H
#define MIPS_PARSER_H

#include<iostream>
#include<ctype.h>
#include<string.h>
#include<sstream>
#include<unordered_map>
#include"mips_ISA.h"
using namespace std;
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

// example: 
// [indented]add $17, $9, $8

int read_initial_address(uint32_t* PC_start, char* address) {
    if (!PC_start || !address) {
        return -1;
    }
    uint32_t address_value;
    stringstream ss;
    ss << hex << &address;
    ss >> address_value;
    *PC_start = static_cast<uint32_t>(address_value); 
    return 0;
}

int read_label(unordered_map<string, uint32_t> instr_addr_map) {

}

int parse_instruction(uint32_t* dest, string instruction) {
    if (!dest) {
        return -1;
    }
    unordered_map<string, R_MNEMONIC> r_mnemonic_map = {
        {"add", ADD}, {"sub", SUB}, {"and", AND}, {"or", OR},
        {"nor", NOR}, {"sll", SLL}, {"srl", SRL}, {"slt", SLT}
    };
    unordered_map<string, I_MNEMONIC> i_mnemonic_map = {
        {"addi", ADDI}, {"subi", SUBI}, {"andi", ANDI}, {"ori", ORI},
        {"nori", NORI}, {"beq", BEQ}, {"bne", BNE}, {"lw", LW},
        {"lui", LUI}, {"sw", SW}
    };
    unordered_map<string, J_MNEMONIC> j_mnemonic_map = {
        {"j", JUMP}
    };

    size_t colon_pos = instruction.find(':');
    if (colon_pos == string::npos) {
        
    }


}

#endif