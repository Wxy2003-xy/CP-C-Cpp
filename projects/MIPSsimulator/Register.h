#ifndef REGISTER_H
#define REGISTER_H
#include <ctype.h>
#include <iostream>

class Register {
    protected:
        uint32_t register_content;
    public:
        virtual uint32_t read_register() {
            return this->register_content;
        }
        virtual int write_register_from_32bit_immd(uint32_t* full_register_content) {
            this->register_content = *full_register_content;
            return 0;
        }
};

class General_Register : Register {
    protected:
        uint8_t register_no;
    public: 
        General_Register(uint8_t register_no) {
            this->register_no = register_no;
            this->register_content = 0x00000000; // initialized to 0;
        }
        uint8_t get_register_no() {
            return this->register_no;
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

class Pipeline_Register : public Register {

};

#endif
