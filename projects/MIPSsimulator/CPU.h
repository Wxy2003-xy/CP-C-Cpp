#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <ctype.h>
#include "mips_ISA.h"
#include "Register.h"
#include "Register_File.h"
#include "ALU.h"
#include "Memory.h"
using namespace std;
// simple MUX implememtation that suports up to 4 sources
class MUX {
    
};

class MUX_2_1 : public MUX {
    private: 
        uint32_t* source1;
        uint32_t* source2;
        bool* signal;
        
        MUX_2_1(uint32_t* source1, uint32_t* source2, bool* signal) {
            this->source1 = source1;
            this->source2 = source2;
            this->signal = signal;
        }
        uint32_t output() {
            if (*signal == 0) {
                return *source1;
            }
            if (*signal == 1) {
                return *source2;
            }
        }
        friend class CPU;
};

class MUX_2_1_5_bit : public MUX {
    private:
        uint5_t* source1;
        uint5_t* source2;
        bool* signal;
        
        MUX_2_1_5_bit(uint5_t* source1, uint5_t* source2, bool* signal) {
            this->source1 = source1;
            this->source2 = source2;
            this->signal = signal;
        }
        uint5_t output() {
            if (*signal == 0) {
                return *source1;
            }
            if (*signal == 1) {
                return *source2;
            }
        }
        friend class CPU;
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

class CPU {
    protected:
        // register file for general purpose registers
        Register_File register_file;

        // 32-bit ALU 
        ALU_32_bit alu;

        // pipeline registers
        Pipeline_Register* if_id;
        Pipeline_Register* id_ex;
        Pipeline_Register* ex_mem;
        Pipeline_Register* mem_wb;
        // tmp instruction register
        Register* tmp_instr_register;


        // Memory, reference, as memory are separately instantiated.
        unique_ptr<Instruction_Memory> instruction_memory;
        unique_ptr<Data_Memory> data_memory;

        // Program counter
        uint32_t PC;
        uint32_t next_PC;
        uint32_t branch_address;

        // control 
        Control control;
        bool reg_dst;
        bool alu_src;
        bool mem_to_reg;
        bool reg_write;
        bool mem_read;
        bool mem_write;
        bool branch;

        // Utility components
        MUX_2_1_5_bit* reg_dst_MUX;
        MUX_2_1* alu_src_MUX;
        MUX_2_1* PC_src_MUX;
        MUX_2_1* mem_to_reg_MUX;
        // temporary values
        uint32_t alu_result;
        uint32_t extended_value;
        uint32_t extended_shifted_value;
        uint5_t rt; //[20:16]
        uint5_t rd; //[15:11]
    public:
        CPU(int instruction_size, int data_size) 
            : instruction_memory(std::make_unique<Instruction_Memory>(instruction_size)),
              data_memory(std::make_unique<Data_Memory>(data_size)),
              PC(*instruction_memory->virtual_PC) {
            // component instantiation:
            reg_dst_MUX = new MUX_2_1_5_bit(&rt, &rd, &reg_dst);
            alu_src_MUX = new MUX_2_1(this->register_file.RD2, &extended_value, &alu_src);
            PC_src_MUX = new MUX_2_1(&next_PC, &branch_address, &branch);
            mem_to_reg_MUX = new MUX_2_1(&alu_result, this->data_memory->memory_read, &mem_to_reg);
        }
        int __instruction_fetch() {
            uint32_t* current_instruction = this->instruction_memory->virtual_PC;
            this->instruction_memory->fetch_instruction_tmp_register(current_instruction, this->tmp_instr_register);


            return 0;
            
        }
        int __instruction_decode() {
            return 0;

        }
        int __execute_alu() {
            return 0;

        }
        int __memory() {
            return 0;

        }
        int __write_back() {
            return 0;

        }
};

#endif
