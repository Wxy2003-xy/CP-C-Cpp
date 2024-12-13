#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <ctype.h>
#include <vector>
#include "mips_ISA.h"

using namespace std;

class Control {
    private:
        uint2_t alu_op;
        uint4_t alu_ctrl;
        // MSB -> LSB
        // RegDst, ALUSrc, MemToReg, RegWrite, MemRead, MemWrite, Branch
        uint7_t ctrl;
        bool R_instruction_AND(bool* opcode_bits) {
            bool res = true;
            for (int i = 0; i < 6; i++) {
                res = res & (~opcode_bits[i]);
            }
            return res;
        }
        bool lw_instruction_AND(bool* opcode_bits) {
            return opcode_bits[0] & opcode_bits[1]
                       & (~opcode_bits[2]) & (~opcode_bits[3])
                       & (~opcode_bits[4]) & opcode_bits[5];
        }
        bool sw_instruction_AND(bool* opcode_bits) {
            return opcode_bits[0] & opcode_bits[1]
                       & (~opcode_bits[2]) & opcode_bits[3]
                       & (~opcode_bits[4]) & opcode_bits[5];
        }
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
        uint4_t generate_ALU_control(uint6_t* func, uint2_t* alu_op) {
            bool f0 = (*func & 0b1);
            bool f1 = (*func >> 1) & 1;
            bool f2 = (*func >> 2) & 1;
            bool f3 = (*func >> 3) & 1;
            
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
        int generate_control_signals(uint6_t* opcode, uint6_t* func,
                                     uint2_t* alu_op, uint7_t* control, uint4_t* alu_ctrl) {
            if (!opcode || !func || !alu_op || !control || !alu_ctrl) {
                return -1;  // Error code for invalid inputs
            }
            uint6_t opcode_value = *opcode;
            bool opcode_bits[6];
            for (int i = 0; i < 6; i++) {
                opcode_bits[i] = (opcode_value >> i) & 1;   
            }
            // alu_op
            *alu_op = 0;
            *alu_op = (R_instruction_AND(opcode_bits) << 1) | beq_instruction_AND(opcode_bits);
            // ctrl
            bool R_instr = R_instruction_AND(opcode_bits);
            bool lw_instr = lw_instruction_AND(opcode_bits);
            bool sw_instr = sw_instruction_AND(opcode_bits);
            bool beq_instr = beq_instruction_AND(opcode_bits);
            *control = 0;
            // Combine the control signals step-by-step
            *control = (*control << 1) | R_instr;                    // Add R_instr to bit 0
            *control = (*control << 1) | (lw_instr | sw_instr);      // Add lw_instr OR sw_instr to bit 1
            *control = (*control << 1) | lw_instr;                   // Add lw_instr to bit 2
            *control = (*control << 1) | (R_instr | lw_instr);       // Add R_instr OR lw_instr to bit 3
            *control = (*control << 1) | lw_instr;                   // Add lw_instr to bit 4
            *control = (*control << 1) | sw_instr;                   // Add sw_instr to bit 5
            *control = (*control << 1) | beq_instr;   
            // alu ctrl
            *alu_ctrl = generate_ALU_control(func, alu_op);
            return 0;
        }
        // getters
        // RegDst, ALUSrc, MemToReg, RegWrite, MemRead, MemWrite, Branch
        bool _reg_dst() {
            return this->ctrl.value >> 6;
        }
        bool _alu_src() {
            return (this->ctrl.value >> 5) & 1;
        }
        bool _mem_to_reg() {
            return (this->ctrl.value >> 4) & 1;
        }
        bool _reg_write() {
            return (this->ctrl.value >> 3) & 1;
        }
        bool _mem_read() {
            return (this->ctrl.value >> 2) & 1;
        }
        bool _mem_write() {
            return (this->ctrl.value >> 1) & 1;
        }
        bool _branch() {
            return this->ctrl.value & 1;
        }
        friend class CPU;
        friend class Register_File;
};

#endif