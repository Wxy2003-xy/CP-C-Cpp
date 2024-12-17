#ifndef REGISTER_H
#define REGISTER_H
#include <ctype.h>
#include <iostream>

/**
 * @brief Base class for all registers in the CPU.
 * 
 * This class provides common methods for reading from and writing to registers.
 * It is meant to be inherited by specific register types.
 */
class Register {
    protected:
        uint32_t* register_content; ///< Pointer to the actual register content (32-bit value).
    
    public:
        /**
         * @brief Reads the content of the register.
         * 
         * @return The 32-bit content of the register.
         */
        virtual uint32_t read_register() {
            return *this->register_content;
        }

        /**
         * @brief Writes a 32-bit immediate value into the register.
         * 
         * @param full_register_content A pointer to the 32-bit value to be written into the register.
         * @return 0 if successful, 1 if an error occurs.
         */
        virtual int write_register_from_32bit_immd(uint32_t* full_register_content) {
            *this->register_content = *full_register_content;
            return 0;
        }

        friend class CPU; ///< Allows the `CPU` class to access the private members of `Register`.
        friend class Register_File; ///< Allows the `Register_File` class to access the private members of `Register`.
};

/**
 * @brief Class for general-purpose registers in the CPU.
 * 
 * Inherits from the `Register` class, and represents registers used for general computation and data storage.
 */
class General_Register : public Register {
    protected:
        uint8_t register_no; ///< The number of the general register (e.g., $t0, $t1, etc.).

    public:
        /**
         * @brief Constructs a general-purpose register with the given register number.
         * 
         * @param register_no The number of the register (e.g., 0 for $t0).
         */
        General_Register(uint8_t register_no) {
            this->register_no = register_no;
            this->register_content = 0x00000000; // Initialized to 0
        }

        /**
         * @brief Gets the register number of the general register.
         * 
         * @return The register number.
         */
        uint8_t get_register_no() {
            return this->register_no;
        }

        /**
         * @brief Writes the value from another register into this register.
         * 
         * @param source_register A pointer to the source register.
         * @return 0 if successful, 1 if an error occurs.
         */
        int write_register_from_register(Register* source_register) {
            if (!source_register) {
                return 1;
            }
            uint32_t source_value = source_register->read_register();
            *this->register_content = source_value;
            return 0;
        }

        /**
         * @brief Loads the upper 16 bits of the register with the provided value.
         * 
         * @param upper A pointer to a 16-bit value to load into the upper 16 bits.
         * @return 0 if successful, 1 if an error occurs.
         */
        int load_upper(uint16_t* upper) {
            if (!upper) {
                return 1;
            }
            uint16_t upper_value = *upper;
            uint32_t shifted_value = static_cast<uint32_t>(upper_value) << 16;
            *this->register_content = *this->register_content & 0x0000FFFF; // Clear upper 16 bits
            *this->register_content = *this->register_content | shifted_value; // Set upper 16 bits
            return 0;
        }

        /**
         * @brief Loads the lower 16 bits of the register with the provided value.
         * 
         * @param lower A pointer to a 16-bit value to load into the lower 16 bits.
         * @return 0 if successful, 1 if an error occurs.
         */
        int load_lower(uint16_t* lower) {
            if (!lower) {
                return 1;
            }
            uint16_t lower_value = *lower;
            uint32_t shifted_value = static_cast<uint32_t>(lower_value);
            *this->register_content = *this->register_content & 0xFFFF0000; // Clear lower 16 bits
            *this->register_content = *this->register_content | shifted_value; // Set lower 16 bits
            return 0;
        }

        friend class CPU; ///< Allows the `CPU` class to access the private members of `General_Register`.
        friend class Register_File; ///< Allows the `Register_File` class to access the private members of `General_Register`.
        friend class Register; ///< Allows the `Register` class to access the private members of `General_Register`.
};

/**
 * @brief Class for the zero register in the CPU.
 * 
 * This register always reads as 0, as it is a special register in many CPU architectures.
 */
class Zero_Register : public Register {
    public:
        /**
         * @brief Always returns 0 when reading from this register.
         * 
         * @return Always returns 0.
         */
        uint32_t read_register() {
            return 0x00000000;
        }
};

/**
 * @brief Class for the assembler temporary register in the CPU.
 * 
 * This register is typically used by the assembler to store temporary values.
 */
class Assembler_Temporary_Register : public Register {
    public:
        /**
         * @brief Always returns 0xFFFFFFFF when reading from this register.
         * 
         * @return Always returns 0xFFFFFFFF.
         */
        uint32_t read_register() {
            return 0xFFFFFFFF;
        }
};

/**
 * @brief Class for the function evaluation register in the CPU.
 * 
 * This register is used to hold intermediate values during function evaluations.
 */
class Value_for_Function_eval_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for the argument registers in the CPU.
 * 
 * These registers are used to store function arguments in many CPU architectures.
 */
class Arguement_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for temporary registers in the CPU.
 * 
 * These are general-purpose registers used temporarily during computations.
 */
class Temporary_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for saved temporary registers in the CPU.
 * 
 * These registers are typically used to save temporary values that need to be restored later.
 */
class Saved_Temporary_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for kernel registers in the CPU.
 * 
 * These registers are used in kernel mode for system-level operations.
 */
class Kernel_Register : public Register {
    private:
    public:
};

/**
 * @brief Base class for pointer registers in the CPU.
 * 
 * This class serves as a base for various pointer-related registers, such as the stack pointer, frame pointer, etc.
 */
class Pointer_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for the global pointer register in the CPU.
 * 
 * This register typically points to global variables or memory used across the program.
 */
class Global_Pointer_Register : public Pointer_Register {
    private:
    public:
};

/**
 * @brief Class for the stack pointer register in the CPU.
 * 
 * This register points to the current position on the stack.
 */
class Stack_Pointer_Register : public Pointer_Register {
    private:
    public:
};

/**
 * @brief Class for the frame pointer register in the CPU.
 * 
 * This register is used to point to the current stack frame in function calls.
 */
class Frame_Pointer_Register : public Pointer_Register {
    private:
    public:
};

/**
 * @brief Class for the return address register in the CPU.
 * 
 * This register typically stores the return address for function calls.
 */
class Return_Address_Register : public Register {
    private:
    public:
};

/**
 * @brief Class for pipeline registers in the CPU.
 * 
 * These registers hold intermediate values between pipeline stages in a CPU.
 */
class Pipeline_Register : public Register {
};

#endif
