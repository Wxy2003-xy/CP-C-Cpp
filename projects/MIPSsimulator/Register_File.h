#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <iostream>
#include <ctype.h>
#include "Register.h"
#include "Control.h"
#include "mips_ISA.h"
using namespace std;
class Register_File {
    private:
        /**
         * Address reference in CPU:
         *      RR1, RR2, RD1, RD2, WR, WD
         * 
        */
        Control* control;
        Register* registers[32];
        uint5_t* rr1_no;
        uint5_t* rr2_no;
        uint5_t* wr_no;

        Register* RR1;
        Register* RR2;
        Register* WR;
        uint32_t* RD1;
        uint32_t* RD2;
        uint32_t* WD;
        bool RegWrite;
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
        int set_RR1() {
            RR1 = registers[*this->rr1_no];
            return 0;
        }
        int set_RR2() {
            RR2 = registers[*this->rr2_no];
            return 0;
        }
        int set_WR() {
            WR = registers[*this->wr_no];
            return 0;
        }
        int read_RR1() {
            *this->RD1 = this->RR1->read_register();
        }
        int read_RR2() {
            *this->RD2 = this->RR2->read_register();
        }

        int write_back_data(uint32_t* wb) {
            *this->WD = *wb;
            return 0;
        }
        int write_back_register() {
            if (!this->control->_reg_write()) {
                return 1;
            }
            this->WR->write_register_from_32bit_immd(WD);
            return 0;
        }

        ~Register_File() {
            cout << "Register_file has been destructed." << endl;
        }
    friend class CPU;
};

#endif
