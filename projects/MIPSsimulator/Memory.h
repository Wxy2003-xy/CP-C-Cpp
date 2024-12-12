#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <ctype.h>
#include "Register.h"

/**
 * Instruction_Memory and Data_Memory extend from Memory
 * Instruction_Memory:
 *      @instructions: (uint32_t*) a statically allocated block of memory reserved for instructions;
 * 
 *      @PCstart: (uint32_t) constant offset of the starting address, between the simulated instruction 
 *                           address and the actual physical address allocated.
 * 
 *      @virtual_PC: (uint32_t*) program counter in simulation;
 * 
 *      @physical_PC: (uint32_t*) program counter mapped to the actual physical address;
*/
class Memory {

};

class Instruction_Memory : public Memory {
    protected:
        /**
         * @param sim
        */
        int map_instruction_address(uint32_t* simulation_address, uint32_t* physical_address) {
            *simulation_address = *physical_address - this->PCstart;
            //TODO: exception handling
            return 0;
        }
        int reverse_map_instruction_address(uint32_t* simulation_address, uint32_t* physical_address) {
            *physical_address = *simulation_address + this->PCstart;
            //TODO: exception handling
            return 0;
        }
    public: 
        uint32_t* instructions;
        uint32_t PCstart;
        uint32_t* virtual_PC;
        uint32_t* physical_PC;  // const offset = PCstart between physical and virtual PC
        Instruction_Memory(int instruction_size) { // assign the real starting address of instruction memory in simulation 
            this->instructions = (uint32_t*) malloc(sizeof(uint32_t) * instruction_size);
            PCstart = *instructions;
        }

        int fetch_instruction_tmp_register(uint32_t* simulation_address, Register* instruction_register) {
            instruction_register->write_register_from_32bit_immd(&this->instructions[*simulation_address]);
            return 0;
        }

        
        int fetch_instruction_from_virtual_address(uint32_t* simulation_address, uint32_t* instruction_register) {
            *instruction_register = this->instructions[*simulation_address];
            return 0;
        }

        int fetch_instruction_from_physical_address(uint32_t* physical_address, uint32_t* instruction_register) {
            if (map_instruction_address(this->virtual_PC, physical_address)) {
                *instruction_register = this->instructions[*virtual_PC];
                return 0;
            }
            return 1;
        }

        int jump(uint32_t* new_address, uint32_t* instruction_register) {
            //TODO: exception handling
            return 0;
            
        }
};

class Data_Memory : public Memory {
    protected: 
        uint32_t* read_address;
        uint32_t* write_address;
        uint32_t* memory_pointer;
    public:
        uint32_t* data;
        Data_Memory(int data_size) {
            this->data = (uint32_t*) malloc(sizeof(uint32_t) * data_size);
        }
};
#endif