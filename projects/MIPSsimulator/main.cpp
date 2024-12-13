#include <iostream>
#include <ctype.h>
#include "mips_ISA.h"
#include "Register.h"
#include "Register_File.h"
#include "ALU.h"
#include "Memory.h"
#include "CPU.h"
#include "MIPS_Parser.h"

/**
 * Compile using 
 *      g++ -std=c++14 -o main main.cpp
 * 
*/

int main() {
    CPU* cpu = new CPU(1024, 1024);

    return 0;
}