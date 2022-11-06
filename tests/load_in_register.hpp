#ifndef LOAD_IN_REGISTER_H
#define LOAD_IN_REGISTER_H
#include "../src/cpu.hpp"

#include <optional>
#include <utility>

void test_immediate(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);

void test_zero_page(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);
void test_zero_page_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);
void test_zero_page_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);

void test_absolute(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);
void test_absolute_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read = false
);
void test_absolute_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read = false
);

void test_indirect_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
);
void test_indirect_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read = false
);

#endif
