#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

#define TEST_ASL_FLAGS \
	test_ZNC_flags(flags, cpu.flags, reg_t(value << 1), !!(value & 1U << 7));

#define TEST_ASL(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		const reg_t new_val = reg_t(value << 1); \
		function(cpu, opcode, nullptr, value, new_val, cycles); \
		test_ZNC_flags(flags, cpu.flags, new_val, !!(value & 1U << 7)); \
	}

TEST_CASE("ASL") {
	SECTION("ASL ACCUMULATOR") {
		INIT_TEST_ONCE(0x02, 2);
		test_accumulator(cpu, ASL, &cpu.A, value, value << 1, cycles);
		TEST_ASL_FLAGS
	}
	TEST_ASL(0xA4, 5, test_zero_page, ASL_ZERO_PAGE, "ASL ZERO PAGE");
	TEST_ASL(0xA5, 6, test_zero_page_X, ASL_ZERO_PAGE_X, "ASL ZERO PAGE X");
	TEST_ASL(0xDE, 6, test_absolute, ASL_ABSOLUTE, "ASL ABSOLUTE");
	TEST_ASL(0x11, 7, test_absolute_X, ASL_ABSOLUTE_X, "ASL ABSOLUTE X");
}

#define TEST_LSR_FLAGS \
	test_ZNC_flags(flags, cpu.flags, value >> 1, !!(value & 1U));

#define TEST_LSR(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, nullptr, value, value >> 1, cycles); \
		test_ZNC_flags(flags, cpu.flags, value >> 1, !!(value & 1U)); \
	}

TEST_CASE("LSR") {
	SECTION("LSR ACCUMULATOR") {
		INIT_TEST_ONCE(0x02, 2);
		test_accumulator(cpu, LSR, &cpu.A, value, value >> 1, cycles);
		TEST_LSR_FLAGS
	}
	TEST_LSR(0xA4, 5, test_zero_page, LSR_ZERO_PAGE, "LSR ZERO PAGE");
	TEST_LSR(0xA5, 6, test_zero_page_X, LSR_ZERO_PAGE_X, "LSR ZERO PAGE X");
	TEST_LSR(0xDE, 6, test_absolute, LSR_ABSOLUTE, "LSR ABSOLUTE");
	TEST_LSR(0x11, 7, test_absolute_X, LSR_ABSOLUTE_X, "LSR ABSOLUTE X");
}

uint8_t rol(uint8_t value, flag_t flags) {
	return uint8_t(value << 1) | !!(flags & CPU::C_M);
}

#define TEST_ROL_FLAGS \
	test_ZNC_flags(flags, cpu.flags, new_value, !!(value & 1 << 7));

#define TEST_ROL(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		const uint8_t new_value = rol(value, cpu.flags); \
		function(cpu, opcode, nullptr, value, new_value, cycles); \
		test_ZNC_flags(flags, cpu.flags, new_value, !!(value & 1 << 7)); \
	}

TEST_CASE("ROL") {
	// TODO: implement accumulator
	SECTION("ROL ACCUMULATOR") {
		INIT_TEST_ONCE(0x0B, 2);

		const auto new_value = rol(value, cpu.flags);
		test_accumulator(cpu, ROL, &cpu.A, value, new_value, cycles);
		TEST_ROL_FLAGS
	}
	TEST_ROL(0xC0, 5, test_zero_page, ROL_ZERO_PAGE, "ROL ZERO PAGE");
	TEST_ROL(0x04, 6, test_zero_page_X, ROL_ZERO_PAGE_X, "ROL ZERO PAGE X");
	TEST_ROL(0x21, 6, test_absolute, ROL_ABSOLUTE, "ROL ABSOLUTE");
	TEST_ROL(0x21, 7, test_absolute_X, ROL_ABSOLUTE_X, "ROL ABSOLUTE X");
}

constexpr uint8_t ror(const uint8_t value, flag_t flags) {
	return uint8_t(value >> 1) | (!!(flags & CPU::C_M) << 7);
}
#define TEST_ROR(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		const uint8_t new_value = ror(value, cpu.flags); \
		function(cpu, opcode, nullptr, value, new_value, cycles); \
		test_ZNC_flags(flags, cpu.flags, new_value, !!(value & 1)); \
	}

TEST_CASE("ROR") {
	SECTION("LSR ACCUMULATOR") {
		INIT_TEST_ONCE(0x0B, 2);
		test_accumulator(
			cpu, ROR, &cpu.A, value, ror(value, cpu.flags), cycles
		);
		TEST_LSR_FLAGS
	}
	TEST_ROR(0XBB, 5, test_zero_page, ROR_ZERO_PAGE, "ROR ZERO PAGE");
	TEST_ROR(0X32, 6, test_zero_page_X, ROR_ZERO_PAGE_X, "ROR ZERO PAGE X");
	TEST_ROR(0X37, 6, test_absolute, ROR_ABSOLUTE, "ROR ABSOLUTE");
	TEST_ROR(0XB6, 7, test_absolute_X, ROR_ABSOLUTE_X, "ROR ABSOLUTE X");
}