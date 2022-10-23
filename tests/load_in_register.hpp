#ifndef LOAD_IN_REGISTER_H
#define LOAD_IN_REGISTER_H
#include "../src/cpu.hpp"

#include <utility>

uint32_t test_immediate(CPU &, Memory &, opcode_type, uint8_t);

uint32_t test_zero_page(CPU &, Memory &, opcode_type, uint8_t);

uint32_t test_zero_page_X(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_zero_page_X_wrap(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_zero_page_Y(CPU &, Memory &, opcode_type, uint8_t);

uint32_t test_absolute(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_absolute_X(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_absolute_Y(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_indirect_X(CPU &, Memory &, opcode_type, uint8_t);
uint32_t test_indirect_Y(CPU &, Memory &, opcode_type, uint8_t);
#endif
