#include <iostream>
#include <ctype.h>
#include "mips_ISA.h"
#include "Register.h"
#include "Register_File.h"
#include "ALU.h"
class CPU {
    protected:
        Register_File register_file;
        ALU_32_bit alu;
        Pipeline_Register if_id;
        Pipeline_Register id_ex;
        Pipeline_Register ex_mem;
        Pipeline_Register mem_wb;

        uint32_t instr;
        uint16_t ctrl_signals; // only the least significant 9 bits used
    public:
        CPU() {

        }

        void run() {

        }
};


int main() {
    return 0;
}
