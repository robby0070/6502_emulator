#ifndef LOAD_IN_REGISTER_H
#define LOAD_IN_REGISTER_H
#include "../src/cpu.hpp"

#include <utility>

void test_immediate(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);

void test_zero_page(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);
void test_zero_page_X(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);
void test_zero_page_Y(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);

void test_absolute(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);
void test_absolute_X(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t,
	bool
);
void test_absolute_Y(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t,
	bool
);

void test_indirect_X(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);
void test_indirect_Y(
	CPU &,
	Memory &,
	opcode_type,
	const reg_t &,
	uint8_t,
	uint8_t,
	uint32_t
);

#endif
