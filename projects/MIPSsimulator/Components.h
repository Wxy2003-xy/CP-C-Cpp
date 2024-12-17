#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <iostream>
#include "CPU.h"
#include "mips_ISA.h"

/**
 * @brief MUX (Multiplexer) class that selects one of two input sources
 *        based on a control signal and outputs the selected value.
 *
 * @tparam T The type of data being passed (e.g., uint32_t, uint16_t, etc.)
 */
template <typename T>
class MUX {
    private:
        T* source1;   ///< First source input.
        T* source2;   ///< Second source input.
        bool* signal; ///< Control signal determining which source to select.
        T* output;    ///< Output selected value based on the control signal.
    
    public:
        /**
         * @brief Constructs a MUX object.
         * 
         * @param src1 First input source.
         * @param src2 Second input source.
         * @param sig Control signal to choose between src1 and src2.
         * @param out Output to store the selected value.
         */
        MUX(T* src1, T* src2, bool* sig, T* out)
            : source1(src1), source2(src2), signal(sig), output(out) {}
        
        /**
         * @brief Computes the output based on the control signal.
         * 
         * If the signal is true, select source2, else select source1.
         */
        void compute() {
            *output = (*signal) ? *source2 : *source1;
        }
};

/**
 * @brief Sign extension module that extends a 16-bit value to a 32-bit value.
 *
 * This class uses 2's complement representation to extend a 16-bit value to
 * a 32-bit value. The 16-bit input is sign-extended by replicating its 
 * most significant bit (MSB) to fill the upper 16 bits.
 */
class Sign_extension {
    private:
        // Private constructor to ensure that the class can only be accessed via the CPU class.
        Sign_extension() {}

        /**
         * @brief Sign-extends a 16-bit input to a 32-bit output.
         * 
         * @param input A pointer to a 16-bit signed input value.
         * @return The sign-extended 32-bit value.
         */
        uint32_t sign_extend(uint16_t* input) {
            uint32_t output = *input;
            if (output >> 15) {
                output |= 0xFFFF0000;  // Set the upper 16 bits to 1 if the sign bit is 1.
            }
            return output;
        }

        friend class CPU; ///< Allows the CPU class to access the private methods of Sign_extension.
};

/**
 * @brief Bit shift module that shifts a 32-bit input left by 2 positions.
 *
 * This class implements a simple left shift operation on a 32-bit value,
 * which is commonly used in MIPS to handle word-aligned memory addresses.
 */
class Bit_Shifter {
    private:
        // Private constructor to ensure that the class can only be accessed via the CPU class.
        Bit_Shifter() {}

        /**
         * @brief Shifts a 32-bit input left by 2 positions.
         * 
         * @param input A 32-bit input value.
         * @return The 32-bit value after shifting it left by 2 positions.
         */
        uint32_t bit_shift(uint32_t input) {
            return input << 2;  // Shift left by 2 bits (equivalent to multiplying by 4).
        }

        friend class CPU; ///< Allows the CPU class to access the private methods of Bit_Shifter.
};

#endif
