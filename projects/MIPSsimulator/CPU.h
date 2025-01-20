#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <ctype.h>
#include "mips_ISA.h"
#include "Register.h"
#include "Register_File.h"
#include "ALU.h"
#include "Memory.h"
#include "Components.h"
using namespace std;

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
        int instruction_memory_size;
        int data_memory_size;

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
        bool is_zero;

        // Utility components
        MUX<uint5_t>* reg_dst_MUX;
        MUX<uint32_t>* alu_src_MUX;
        MUX<uint32_t>* PC_src_MUX;
        MUX<uint32_t>* mem_to_reg_MUX;
        // temporary values
        uint32_t alu_result;
        uint32_t extended_value;
        uint32_t extended_shifted_value;
        uint32_t alu_src_source2;
        uint6_t opcode; //[26:31]
        uint5_t rs; //[25:21]
        uint5_t rt; //[20:16]
        uint5_t rd; //[15:11]
        uint5_t shamt; //[10:6]
        uint6_t func; //[5:0]
        uint16_t immd; //[15:0]
        uint32_t tmp_data_read;
    public:
        CPU(int instruction_size, int data_size) 
            : instruction_memory(make_unique<Instruction_Memory>(instruction_size)),
              data_memory(make_unique<Data_Memory>(data_size)),
              PC(*instruction_memory->virtual_PC) {
            // component instantiation:
            this->instruction_memory_size = instruction_size;
            this->data_memory_size = data_size;
            reg_dst_MUX = new MUX<uint5_t>(&rt, &rd, &reg_dst, this->register_file.wr_no);
            alu_src_MUX = new MUX<uint32_t>(this->register_file.RD2, &extended_value, &alu_src, &alu_src_source2);
            PC_src_MUX = new MUX<uint32_t>(&next_PC, &branch_address, &branch, &next_PC);
            mem_to_reg_MUX = new MUX<uint32_t>(&alu_result, this->data_memory->memory_read, &mem_to_reg, this->register_file.WD);
        }
        int _instruction_fetch() {
            uint32_t* current_instruction = this->instruction_memory->virtual_PC;
            this->instruction_memory->fetch_instruction_tmp_register(current_instruction, this->tmp_instr_register);
            return 0;

        }
        int _instruction_decode() {
            uint32_t instruction_value = this->tmp_instr_register->read_register();
            INSTRUCTION_TYPE type = instruction_type(&instruction_value);
            if (type == r) {
                parse_R_instruction(&instruction_value, &rs, &rt, &rd, &shamt, &func);
            }
            if (type == i) {
                parse_I_instruction(&instruction_value, &opcode, &rs, &rt, &immd);
            }
            if (type == j) {
                parse_J_instruction(&instruction_value, &branch_address, &PC);
            }
            return 0;
        }
        int _execute_alu() {
            this->alu.compute(&alu_result, &is_zero, this->register_file.RD1,
                              &alu_src_source2, &this->control.alu_ctrl);
            // TODO: forwarding pipeline
            return 0;
        }
        int _memory() {
            return 0;
        }
        int _write_back() {
            this->register_file.write_back_register();
            return 0;
        }
};

#endif
