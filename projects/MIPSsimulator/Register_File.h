#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <iostream>
#include <ctype.h>
#include "Register.h"
#include "Control.h"
#include "mips_ISA.h"
using namespace std;

/**
 * @brief Class representing the register file of the CPU.
 * 
 * The register file stores the 32 general-purpose registers and provides methods to read from and write to them.
 * It also manages the control logic for reading and writing specific registers during instruction execution.
 */
class Register_File {
    private:
        /**
         * @brief Control unit to manage register operations.
         * 
         * The control unit is used to manage the signals that control register reading and writing operations.
         */
        Control* control;

        /**
         * @brief Array holding the 32 registers in the CPU.
         * 
         * Each index represents a register, with special registers like the zero register at index 0.
         */
        Register* registers[32];

        /**
         * @brief Pointers to register numbers for reading and writing.
         * 
         * These pointers hold the register numbers for operands and destination registers.
         */
        uint5_t* rr1_no; ///< Register number for the first operand (RR1).
        uint5_t* rr2_no; ///< Register number for the second operand (RR2).
        uint5_t* wr_no;  ///< Register number for the destination register (WR).

        /**
         * @brief Pointers to the registers and their corresponding data.
         * 
         * These pointers hold the values and references for the register operands and destination.
         */
        Register* RR1;    ///< First operand register.
        Register* RR2;    ///< Second operand register.
        Register* WR;     ///< Write-back register.
        uint32_t* RD1;    ///< Data for the first operand (RD1).
        uint32_t* RD2;    ///< Data for the second operand (RD2).
        uint32_t* WD;     ///< Write-back data (WD).

        /**
         * @brief RegWrite control signal.
         * 
         * This boolean flag determines whether a write operation to the register file should occur.
         */
        bool RegWrite;

        /**
         * @brief Constructor for the Register_File.
         * 
         * Initializes the registers and assigns them to the appropriate slots. The first few registers are 
         * initialized to special-purpose registers (like Zero_Register, Assembler_Temporary_Register).
         */
        Register_File() {
            this->registers[0] = new Zero_Register(); // assign Zero_Register to $0
            this->registers[1] = new Assembler_Temporary_Register(); // assign assembler_temporary_register to $1
            this->registers[2] = new Value_for_Function_eval_Register();
            this->registers[3] = new Value_for_Function_eval_Register(); // v0-v2 
            
            // Initialize argument registers a0-a3
            for (int i = 4; i <= 7; i++) {
                this->registers[i] = new Arguement_Register();
            }

            // Initialize temporary registers t0-t7
            for (int j = 8; j <= 15; j++) {
                this->registers[j] = new Temporary_Register();
            }

            // Initialize saved temporary registers s0-s7
            for (int k = 16; k <= 23; k++) {
                this->registers[k] = new Saved_Temporary_Register();
            }

            // Initialize additional temporary registers t8-t9
            for (int l = 24; l <= 25; l++) {
                this->registers[l] = new Temporary_Register();
            }

            // Initialize kernel, pointer, and other special registers
            this->registers[26] = new Kernel_Register();
            this->registers[27] = new Kernel_Register();
            this->registers[28] = new Global_Pointer_Register();
            this->registers[29] = new Stack_Pointer_Register();
            this->registers[30] = new Frame_Pointer_Register();
            this->registers[31] = new Return_Address_Register();
        }

        /**
         * @brief Sets the register reference for RR1 (first operand).
         * 
         * This function sets the RR1 register to the value pointed to by `rr1_no`.
         * 
         * @return 0 on success, 1 if an error occurs.
         */
        int set_RR1() {
            RR1 = registers[*this->rr1_no];
            return 0;
        }

        /**
         * @brief Sets the register reference for RR2 (second operand).
         * 
         * This function sets the RR2 register to the value pointed to by `rr2_no`.
         * 
         * @return 0 on success, 1 if an error occurs.
         */
        int set_RR2() {
            RR2 = registers[*this->rr2_no];
            return 0;
        }

        /**
         * @brief Sets the register reference for WR (write-back register).
         * 
         * This function sets the WR register to the value pointed to by `wr_no`.
         * 
         * @return 0 on success, 1 if an error occurs.
         */
        int set_WR() {
            WR = registers[*this->wr_no];
            return 0;
        }

        /**
         * @brief Reads the value from the RR1 register into RD1.
         * 
         * This function reads the value of RR1 and stores it in RD1.
         * 
         * @return 0 on success, 1 if an error occurs.
         */
        int read_RR1() {
            *this->RD1 = this->RR1->read_register();
            return 0;
        }

        /**
         * @brief Reads the value from the RR2 register into RD2.
         * 
         * This function reads the value of RR2 and stores it in RD2.
         * 
         * @return 0 on success, 1 if an error occurs.
         */
        int read_RR2() {
            *this->RD2 = this->RR2->read_register();
            return 0;
        }

        /**
         * @brief Writes the data to the WD register for write-back.
         * 
         * This function sets the value of WD to the provided write-back data.
         * 
         * @param wb A pointer to the data to be written back.
         * @return 0 on success, 1 if an error occurs.
         */
        int write_back_data(uint32_t* wb) {
            *this->WD = *wb;
            return 0;
        }

        /**
         * @brief Writes the data from the WD register to the write-back register (WR).
         * 
         * This function performs the actual write-back operation, writing the value from WD to WR.
         * It checks the RegWrite control signal to decide whether to perform the write.
         * 
         * @return 0 if successful, 1 if an error occurs.
         */
        int write_back_register() {
            if (!this->control->_reg_write()) {
                return 1; // No write if RegWrite signal is off
            }
            this->WR->write_register_from_32bit_immd(WD);
            return 0;
        }

        /**
         * @brief Destructor for the Register_File class.
         * 
         * The destructor cleans up dynamically allocated memory and prints a message for debugging.
         */
        ~Register_File() {
            cout << "Register_file has been destructed." << endl;
        }

    friend class CPU; ///< Allows the `CPU` class to access the private members of `Register_File`.
};

#endif
