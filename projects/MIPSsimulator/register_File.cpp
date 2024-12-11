#include <iostream>
#include <ctype.h>

class Register {
    protected:
        uint32_t register_content;
    public:
        virtual uint32_t read_register() {
            return this->register_content;
        }
};

class General_Register : Register {
    private:
        uint8_t register_no;
    public: 
        General_Register(uint8_t register_no) {
            this->register_no = register_no;
            this->register_content = 0x00000000; // initialized to 0;
        }
        uint8_t get_register_no() {
            return this->register_no;
        }

        int write_register_from_32bit_immd(uint32_t* full_register_content) {
            this->register_content = *full_register_content;
            return 0;
        }
        int write_register_from_register(Register* source_register) {
            if (!source_register) {
                return 1;
            }
            uint32_t source_value = source_register->read_register();
            this->register_content = source_value;
            return 0;
        }
        int load_upper(uint16_t* upper) {
            if (!upper) {
                return 1;
            }
            uint16_t upper_value = *upper;
            uint32_t shifted_value = static_cast<uint32_t>(upper_value) << 16;
            this->register_content = this->register_content & 0x0000FFFF;
            this->register_content = this->register_content | shifted_value;
            return 0;
        }
        int load_lower(uint16_t* lower) {
            if (!lower) {
                return 1;
            }
            uint16_t lower_value = *lower;
            uint32_t shifted_value = static_cast<uint32_t>(lower_value);
            this->register_content = this->register_content & 0xFFFF0000;
            this->register_content = this->register_content | shifted_value;
            return 0;
        }
};

class Zero_Register : public Register {
    private:
    public:
        uint32_t read_register() {
            return 0x00000000;
        }
};

class Assembler_Temporary_Register : public Register {
    private:
    public:
        uint32_t read_register() {
            return 0xFFFFFFFF;
        }
};

class Value_for_Function_eval_Register : public Register {
    private:
    public:
};

class Arguement_Register : public Register {
    private:
    public:
};

class Temporary_Register : public Register {
    private:
    public:
};

class Saved_Temporary_Register : public Register {
    private:
    public:
};

class Kernel_Register : public Register {
    private:
    public:
};

class Pointer_Register : public Register {
    private:
    public:
};

class Global_Pointer_Register : public Pointer_Register {
    private:
    public:
};
class Stack_Pointer_Register : public Pointer_Register {
    private:
    public:
};
class Frame_Pointer_Register : public Pointer_Register {
    private:
    public:
};

class Return_Address_Register : public Register {
    private:
    public:
};
class Register_File {
    private:
        Register* registers[32];
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
};

int main() {
    
    return 0;
}