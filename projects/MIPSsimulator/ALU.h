#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <ctype.h>
#include "Register.h"
class One_bit_ALU {
    protected:
    //TODO
    public:
        One_bit_ALU() {

        }

};

class ALU_32_bit {
    protected:
        bool add_with_overflow(uint32_t* result, uint32_t a, uint32_t b) {
            uint64_t temp = static_cast<uint64_t>(a) + b;
            *result = static_cast<uint32_t>(temp);
            return temp > UINT32_MAX; // Overflow if result exceeds 32 bits
        }

    public:
        ALU_32_bit() {

        }
        int compute(uint32_t* res, bool* is_zero, uint32_t* input_A, uint32_t* input_B, uint4_t* ALUctrl) {
            if (*ALUctrl == 0b0000) {   // and op
                *res = *input_A & *input_B;
            } else if (*ALUctrl == 0b0001) { // or op
                *res = *input_A | *input_B;

            } else if (*ALUctrl == 0b0010) { // add op
                *res = *input_A + *input_B;

            } else if (*ALUctrl == 0b0110) { // sub op
                *res = *input_A - *input_B;
                
            } else if (*ALUctrl == 0b0111) { // slt op
                *res = *input_A < *input_B;
                
            } else if (*ALUctrl == 0b1100) { // nor op
                *res = ~(*input_A | *input_B);
            }
            *is_zero = (*input_A == *input_B);
            return 0;
        }
        ~ALU_32_bit() {

        }
    friend class CPU;
};

#endif