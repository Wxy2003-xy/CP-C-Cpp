#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <iostream>
#include <ctype.h>
#include "Register.h"
#include "Control.h"
class Register_File {
    protected:
        Control* control;

        Register* registers[32];
        Register* RR1;
        Register* RR2;
        Register* WR;
        uint32_t WD;
        bool RegWrite;
    public:
        Register_File() {
            this->registers[0] = new Zero_Register(); // assign Zero_Register to $0
            this->registers[1] = new Assembler_Temporary_Register(); // assign assembler_temporary_register to $1
            this->registers[2] = new Value_for_Function_eval_Register();
            this->registers[3] = new Value_for_Function_eval_Register(); // v0-v2 
            int i, j, k, l;
            for (int i = 4; i <= 7; i++) {
                this->registers[i] = new Arguement_Register(); // a0-a3
            }
            for (int j = 8; j <= 15; j++) {
                this->registers[j] = new Temporary_Register(); // t0-t7
            }
            for (int k = 16; k <= 23; k++) {
                this->registers[j] = new Saved_Temporary_Register(); // s0-s7
            }
            for (int l = 24; l <= 25; l++) {
                this->registers[l] = new Temporary_Register(); // t8-t9
            }
            this->registers[26] = new Kernel_Register();
            this->registers[27] = new Kernel_Register();
            this->registers[28] = new Global_Pointer_Register();
            this->registers[29] = new Stack_Pointer_Register();
            this->registers[30] = new Frame_Pointer_Register();
            this->registers[31] = new Return_Address_Register();
        }

        int write_back_data(uint32_t* wb) {
            this->WD = *wb;
            return 0;
        }
        int write_back_register() {
            this->WR->write_register_from_32bit_immd(&WD);
            return 0;
        }
};

#endif