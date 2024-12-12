#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <ctype.h>
#include "mips_ISA.h"
#include "Register.h"
#include "Register_File.h"
#include "ALU.h"
#include "Memory.h"
class CPU {
    protected:
        Register_File* register_file;
        ALU_32_bit* alu;
        Pipeline_Register* if_id;
        Pipeline_Register* id_ex;
        Pipeline_Register* ex_mem;
        Pipeline_Register* mem_wb;
        Register* tmp_instr_register;

        Instruction_Memory* instruction_memory;
        Data_Memory* data_memory;

        uint32_t* PC;

        uint16_t ctrl_signals; // only the least significant 9 bits used
    public:
        CPU(int instruction_size, int data_size) {
            this->instruction_memory = new Instruction_Memory(instruction_size);
            this->data_memory = new Data_Memory(data_size);
            this->PC = instruction_memory->virtual_PC;
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