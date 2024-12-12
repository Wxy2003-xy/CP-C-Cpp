#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <ctype.h>
class Memory {

};

class Instruction_Memory : public Memory {
    protected:
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
        const uint32_t PCstart;
        uint32_t* virtual_PC;
        uint32_t* physical_PC;  // const offset = PCstart between physical and virtual PC
        Instruction_Memory(int instruction_size) :  PCstart(*instructions) { // assign the real starting address of instruction memory in simulation 
            this->instructions = (uint32_t*) malloc(sizeof(uint32_t) * instruction_size);
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
            
        }
};

class Data_Memory : public Memory {

};
#endif