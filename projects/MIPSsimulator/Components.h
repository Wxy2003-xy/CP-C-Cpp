#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <iostream>
#include "CPU.h"
#include "mips_ISA.h"
template <typename T>
class MUX {
    private:
        T* source1;
        T* source2;
        bool* signal;
        T* output;
    public:
        MUX(T* src1, T* src2, bool* sig, T* out)
            : source1(src1), source2(src2), signal(sig), output(out) {}
        void compute() {
            *output = (*signal) ? *source2 : *source1;
        }
};

// sign extension module based on 2's complement number representation
class Sign_extension {
    private: 
        Sign_extension() {

        }
        uint32_t sign_extend(uint16_t* input) {
            uint32_t output = *input;
            if (output >> 15) {
                output |= 0xFFFF0000;
            }
            return output;
        }
        friend class CPU;
};

class Bit_Shifter {
    private:
        Bit_Shifter() {

        }
        uint32_t bit_shift(uint32_t input) {
            return input << 2;
        }
        friend class CPU;
};
#endif
