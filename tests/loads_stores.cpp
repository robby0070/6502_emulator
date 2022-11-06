#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

#define TEST_LDA(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		function(cpu, opcode, &cpu.A, value, value, cycles); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

TEST_CASE("LDA") {
	TEST_LDA(0xDE, 2, test_immediate, LDA_IMMEDIATE, "LDA IMMEDIATE");
	TEST_LDA(0xAF, 3, test_zero_page, LDA_ZERO_PAGE, "LDA ZERO PAGE");
	TEST_LDA(0x0E, 4, test_zero_page_X, LDA_ZERO_PAGE_X, "LDA ZERO PAGE X");
	TEST_LDA(0xFF, 4, test_absolute, LDA_ABSOLUTE, "LDA ABSOLUTE");
	TEST_LDA(0x01, 4, test_absolute_X, LDA_ABSOLUTE_X, "LDA ABSOLUTE X");
	TEST_LDA(0x04, 4, test_absolute_Y, LDA_ABSOLUTE_Y, "LDA ABSOLUTE Y");
	TEST_LDA(0x07, 6, test_indirect_X, LDA_INDIRECT_X, "LDA INDIRECT X");
	TEST_LDA(0x07, 5, test_indirect_Y, LDA_INDIRECT_Y, "LDA INDIRECT Y");
}

#define TEST_LDX(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		function(cpu, opcode, &cpu.X, value, value, cycles); \
		test_ZN_flags(cpu.X, flags, cpu.flags); \
	}

TEST_CASE("LDX") {
	TEST_LDX(0xEE, 2, test_immediate, LDX_IMMEDIATE, "LDX IMMEDIATE");
	TEST_LDX(0x44, 3, test_zero_page, LDX_ZERO_PAGE, "LDX ZERO PAGE");
	TEST_LDX(0x64, 4, test_zero_page_Y, LDX_ZERO_PAGE_Y, "LDX ZERO PAGE Y");
	TEST_LDX(0x12, 4, test_absolute, LDX_ABSOLUTE, "LDX ABSOLUTE");
	TEST_LDX(0x18, 4, test_absolute_Y, LDX_ABSOLUTE_Y, "LDX ABSOLUTE Y");
}

#define TEST_LDY(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		function(cpu, opcode, &cpu.Y, value, value, cycles); \
		test_ZN_flags(cpu.Y, flags, cpu.flags); \
	}

TEST_CASE("LDY") {
	TEST_LDY(0x99, 2, test_immediate, LDY_IMMEDIATE, "LDY IMMEDIATE");
	TEST_LDY(0x73, 3, test_zero_page, LDY_ZERO_PAGE, "LDY ZERO PAGE");
	TEST_LDY(0xEE, 4, test_zero_page_X, LDY_ZERO_PAGE_X, "LDY ZERO PAGE X");
	TEST_LDY(0xAF, 4, test_absolute, LDY_ABSOLUTE, "LDY ABSOLUTE");
	TEST_LDY(0xFF, 4, test_absolute_X, LDY_ABSOLUTE_X, "LDY ABSOLUTE X");
}

// TEST_CASE("JSR", "[CPU]") {
// 	cpu.reset(0xFF00);
// 	mem[0xFF00] = JSR;
// 	mem[0xFF01] = 0x34;
// 	mem[0xFF02] = 0x12;
// 	CPU cpu_copy = cpu;

// 	const auto actual_cycles = cpu.execute(6);

// 	REQUIRE(actual_cycles == 6);
// 	REQUIRE(cpu.SP == cpu_copy.SP - 2);
// 	REQUIRE(cpu.PC == 0x1234);
// }