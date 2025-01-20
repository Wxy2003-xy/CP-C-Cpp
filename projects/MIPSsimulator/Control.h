#ifndef CONTROL_H
#define CONTROL_H
#include <bitset>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "mips_ISA.h"

using namespace std;

/**
 * @class Control
 * @brief A class that generates control signals for the MIPS processor.
 *
 * This class is responsible for generating the appropriate control signals based
 * on the opcode and function codes for various MIPS instructions. These control
 * signals determine how the processor executes instructions (e.g., which registers
 * to write to, which ALU operation to perform, whether to access memory, etc.).
 */
class Control {
    private:
        uint2_t alu_op;     /**< ALU operation type */
        uint4_t alu_ctrl;   /**< ALU control signal */
        uint7_t ctrl;       /**< Control signal for various operations (RegDst, ALUSrc, MemToReg, etc.) */

        /**
         * @brief Determines if the instruction is an R-type (Register) instruction.
         * @param opcode_bits Array of 6 bits representing the opcode.
         * @return True if it's an R-type instruction, false otherwise.
         */
        bool R_instruction_AND(bool* opcode_bits) {
            bool res = true;
            for (int i = 0; i < 6; i++) {
                res = res & (~opcode_bits[i]);
            }
            return res;
        }

        /**
         * @brief Determines if the instruction is a load word (lw) instruction.
         * @param opcode_bits Array of 6 bits representing the opcode.
         * @return True if it's a lw instruction, false otherwise.
         */
        bool lw_instruction_AND(bool* opcode_bits) {
            return opcode_bits[0] & opcode_bits[1]
                       & (~opcode_bits[2]) & (~opcode_bits[3])
                       & (~opcode_bits[4]) & opcode_bits[5];
        }

        /**
         * @brief Determines if the instruction is a store word (sw) instruction.
         * @param opcode_bits Array of 6 bits representing the opcode.
         * @return True if it's a sw instruction, false otherwise.
         */
        bool sw_instruction_AND(bool* opcode_bits) {
            return opcode_bits[0] & opcode_bits[1]
                       & (~opcode_bits[2]) & opcode_bits[3]
                       & (~opcode_bits[4]) & opcode_bits[5];
        }

        /**
         * @brief Determines if the instruction is a branch equal (beq) instruction.
         * @param opcode_bits Array of 6 bits representing the opcode.
         * @return True if it's a beq instruction, false otherwise.
         */
        bool beq_instruction_AND(bool* opcode_bits) {
            bool res = true;
            for (int i = 0; i < 6; i++) {
                if (i == 2) {
                    res = res & opcode_bits[i];
                } else {
                    res = res & (~opcode_bits[i]);
                }
            }
            return res;
        }

        /**
         * @brief Generates the ALU control signals based on the function code and ALU operation.
         * @param func Function code (6 bits).
         * @param alu_op ALU operation code (2 bits).
         * @return 4-bit ALU control signal.
         */
        uint4_t generate_ALU_control(const uint6_t& func, uint2_t* alu_op) {
            bool f0 = (func & 0b1);
            bool f1 = (func >> 1) & 1;
            bool f2 = (func >> 2) & 1;
            bool f3 = (func >> 3) & 1;
            
            bool alu_op0 = (*alu_op & 1);
            bool alu_op1 = (*alu_op >> 1) & 1;
            bool alu_ctrl0 = alu_op1 & (f0 | f3);
            bool alu_ctrl1 = (~alu_op1) | (~f2);
            bool alu_ctrl2 = alu_op0 | (alu_ctrl1 & f1);
            uint4_t alu_ctrl = 0;
            alu_ctrl = alu_ctrl2 << 1;
            alu_ctrl = (alu_ctrl | alu_ctrl1) << 1;
            alu_ctrl = alu_ctrl | alu_ctrl0;
            return alu_ctrl;
        }

        /**
         * @brief Generates control signals for various instructions based on opcode and function codes.
         * @param opcode 6-bit opcode.
         * @param func 6-bit function code.
         * @param alu_op ALU operation (2 bits).
         * @param control 7-bit control signal (RegDst, ALUSrc, etc.).
         * @param alu_ctrl 4-bit ALU control signal.
         * @return 0 on success, -1 if inputs are invalid.
         */
        int generate_control_signals(const uint6_t& opcode, const uint6_t& func,
                                     uint2_t* alu_op, uint7_t* control, uint4_t* alu_ctrl) {
            if (!alu_op || !control || !alu_ctrl) {
                return -1;  // Error code for invalid inputs
            }
            // R-type: 000000, xxxxxx
            // lw:  100011
            // sw:  101011
            // beq: 000100
            // assign 2-bit alu_op from opcode 
            *alu_op = (opcode == 0);
            *alu_op = (*alu_op << 1) | (opcode == 0b000100);
            // assign 7-bit control 
            *control = 0;   // unused msb
            *control = (*control << 1) | (opcode == 0); // RegDest
            *control = (*control << 1) | ((opcode == 0b100011) | (opcode == 0b101011)); // ALUSrc
            *control = (*control << 1) | (opcode == 0b100011); // MemToReg
            *control = (*control << 1) | ((opcode == 0) | (opcode == 0b100011)); // RegWrite
            *control = (*control << 1) | (opcode == 0b100011); // MemRead
            *control = (*control << 1) | (opcode == 0b101011); // MemWrite 
            *control = (*control << 1) | (opcode == 0b000100); // Branch 

            // assign 4-bit ALU control signal
            *alu_ctrl = generate_ALU_control(func, alu_op);
            return 0;
        }

        // Getter methods for individual control signals
        inline bool get_bit(uint8_t value, int bit_position) {
            return (value >> bit_position) & 1;
        }
        /**
         * @brief Retrieves the RegDst control signal.
         * @return True if RegDst is enabled, false otherwise.
         */
        bool _reg_dst() {
            return get_bit(this->ctrl.value, 6);
        }

        /**
         * @brief Retrieves the ALUSrc control signal.
         * @return True if ALUSrc is enabled, false otherwise.
         */
        bool _alu_src() {
            return get_bit(this->ctrl.value, 5);
        }

        /**
         * @brief Retrieves the MemToReg control signal.
         * @return True if MemToReg is enabled, false otherwise.
         */
        bool _mem_to_reg() {
            return get_bit(this->ctrl.value, 4);
        }

        /**
         * @brief Retrieves the RegWrite control signal.
         * @return True if RegWrite is enabled, false otherwise.
         */
        bool _reg_write() {
            return get_bit(this->ctrl.value, 3);
        }

        /**
         * @brief Retrieves the MemRead control signal.
         * @return True if MemRead is enabled, false otherwise.
         */
        bool _mem_read() {
            return get_bit(this->ctrl.value, 2);
        }

        /**
         * @brief Retrieves the MemWrite control signal.
         * @return True if MemWrite is enabled, false otherwise.
         */
        bool _mem_write() {
            return get_bit(this->ctrl.value, 1);
        }

        /**
         * @brief Retrieves the Branch control signal.
         * @return True if Branch is enabled, false otherwise.
         */
        bool _branch() {
            get_bit(this->ctrl.value, 0);
        }

        friend class CPU;            /**< A friend class that can access private members of Control. */
        friend class Register_File;  /**< A friend class that can access private members of Control. */
};

#endif
