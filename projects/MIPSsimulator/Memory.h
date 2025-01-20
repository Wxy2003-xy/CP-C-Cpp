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
    public: 
        int get_physical_address(uint32_t* simulation_address, uint32_t* physical_address) {

        }
};

/** 
 * @class Instruction_memory
 * @brief This class emulate a fixed sized instruction memory block, containing one consecutive block of physical memory
 *          allocated upon initialization. 
 * @param PCStart the memory address of the starting byte in instruction memory block, finalized upon initialization, used
 *          as the offset to compute physical address from virtual address used by the CPU simulation.
 *          * updated every cycle
*/

class Instruction_Memory : public Memory {
    protected:
        /**
         * @param simulation_address virtual address referred by the CPU simulation
         * @param physical_address actual address referred by instruction memory component 
         * @brief this function maps virtual address referred by the CPU simulation to the actual 
         *          physical address to be used in the memory component
        */
        int get_physical_address(uint32_t* simulation_address, uint32_t* physical_address) {
            *simulation_address = *physical_address + this->PCstart;
            //TODO: exception handling
            return 0;
        }
        /**
         * @param simulation_address virtual address referred by the CPU simulation
         * @param physical_address actual address referred by instruction memory component 
         * @brief this function get the virtual memory address from the physical address to pass to the CPU simulation
        */
        int reverse_map_instruction_address(uint32_t* simulation_address, uint32_t* physical_address) {
            if (*simulation_address < PCstart) {
                return -1;
            }
            *physical_address = *simulation_address - this->PCstart;
            return 0;
        }
    public: 
        int max_instruction_size; // unmodifiable instruciton memory size 
        uint32_t* instruction_memory;  // Array of instructions to store
        uint32_t PCstart; // Offset 
        uint32_t* virtual_PC;   // virtual_PC counter 
        uint32_t* physical_PC;  // const offset = PCstart between physical and virtual PC
        Instruction_Memory(int instruction_size) { // assign the real starting address of instruction memory in simulation 
            this->max_instruction_size = instruction_size;
            this->instruction_memory = (uint32_t*) malloc(sizeof(uint32_t) * max_instruction_size);
            PCstart = *instruction_memory; // set offset to the starting address of memory block
            *physical_PC = PCstart;
            *virtual_PC = 0;
        }

        int fetch_instruction_tmp_register(uint32_t* simulation_address, Register* instruction_register) {
            // update program counters
            *virtual_PC = *simulation_address;
            *physical_PC = *virtual_PC + PCstart;
            // fetch instruction
            instruction_register->write_register_from_32bit_immd(&this->instruction_memory[*virtual_PC]);
            return 0;
        }

        /**
         * @param instruction_register instruction fetch destination 
         * @brief a short hand function to fetch next instruction that is not affected by jump 
        */

        int get_next_instruction(Register* instruction_register) {
            physical_PC++;
            virtual_PC++;
            instruction_register->write_register_from_32bit_immd(&this->instruction_memory[*virtual_PC]);
        }
        
        int fetch_instruction_from_physical_address(uint32_t* physical_address, uint32_t* instruction_register) {
            if (get_physical_address(this->virtual_PC, physical_address)) {
                *instruction_register = this->instruction_memory[*virtual_PC];
                return 0;
            }
            return 1;
        }

        int jump(uint32_t* new_address, uint32_t* instruction_register) {
            //TODO: exception handling
            return 0;
            
        }
        ~Instruction_Memory() {

        }
    friend class CPU;
};

class Data_Memory : public Memory {
    protected: 
        uint32_t* read_address;
        uint32_t* write_address;
        uint32_t* memory_pointer;
        uint32_t* memory_read;
    public:
        uint32_t* data;
        Data_Memory(int data_size) {
            this->data = (uint32_t*) malloc(sizeof(uint32_t) * data_size);
        }

        int read_memory(uint32_t* data_address, Register* data_register) {
            data_register->write_register_from_32bit_immd(&this->data[*data_address]);
        }
    friend class CPU;
};
#endif