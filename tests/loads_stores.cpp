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
#define TEST_LDA_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		function(cpu, opcode, &cpu.A, value, value, cycles, true); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

TEST_CASE("LDA") {
	TEST_LDA(0xDE, 2, test_immediate, LDA_IMMEDIATE, "LDA IMMEDIATE");
	TEST_LDA(0xAF, 3, test_zero_page, LDA_ZERO_PAGE, "LDA ZERO PAGE");
	TEST_LDA(0x0E, 4, test_zero_page_X, LDA_ZERO_PAGE_X, "LDA ZERO PAGE X");
	TEST_LDA(0xFF, 4, test_absolute, LDA_ABSOLUTE, "LDA ABSOLUTE");
	TEST_LDA_CROSS(0x01, 4, test_absolute_X, LDA_ABSOLUTE_X, "LDA ABSOLUTE X");
	TEST_LDA_CROSS(0x04, 4, test_absolute_Y, LDA_ABSOLUTE_Y, "LDA ABSOLUTE Y");
	TEST_LDA(0x07, 6, test_indirect_X, LDA_INDIRECT_X, "LDA INDIRECT X");
	TEST_LDA_CROSS(0x07, 5, test_indirect_Y, LDA_INDIRECT_Y, "LDA INDIRECT Y");
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

#define TEST_STA(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		cpu.A = value; \
		function(cpu, opcode, nullptr, value, value, cycles); \
		test_unchaged_flags(flags, cpu.flags, 0xFF); \
	}
TEST_CASE("STA") {
	TEST_STA(0x72, 3, test_zero_page, STA_ZERO_PAGE, "STA ZERO PAGE");
	TEST_STA(0x39, 4, test_zero_page_X, STA_ZERO_PAGE_X, "STA ZERO PAGE X");
	TEST_STA(0x31, 4, test_absolute, STA_ABSOLUTE, "STA ABSOLUTE");
	TEST_STA(0x99, 5, test_absolute_X, STA_ABSOLUTE_X, "STA ABSOLUTE X");
	TEST_STA(0xF1, 5, test_absolute_Y, STA_ABSOLUTE_Y, "STA ABSOLUTE Y");
	TEST_STA(0x2D, 6, test_indirect_X, STA_INDIRECT_X, "STA INDIRECT X");
	TEST_STA(0xA1, 6, test_indirect_Y, STA_INDIRECT_Y, "STA INDIRECT Y");
}

#define TEST_STX(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		cpu.X = value; \
		function(cpu, opcode, nullptr, value, value, cycles); \
		test_unchaged_flags(flags, cpu.flags, 0xFF); \
	}
TEST_CASE("STX") {
	TEST_STX(0x27, 3, test_zero_page, STX_ZERO_PAGE, "STX ZERO PAGE");
	TEST_STX(0x93, 4, test_zero_page_Y, STX_ZERO_PAGE_Y, "STX ZERO PAGE X");
	TEST_STX(0x12, 4, test_absolute, STX_ABSOLUTE, "STX ABSOLUTE");
}

#define TEST_STY(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		cpu.Y = value; \
		function(cpu, opcode, nullptr, value, value, cycles); \
		test_unchaged_flags(flags, cpu.flags, 0xFF); \
	}
TEST_CASE("STY") {
	TEST_STY(0x72, 3, test_zero_page, STY_ZERO_PAGE, "STX ZERO PAGE");
	TEST_STY(0x39, 4, test_zero_page_X, STY_ZERO_PAGE_X, "STX ZERO PAGE X");
	TEST_STY(0x21, 4, test_absolute, STY_ABSOLUTE, "STX ABSOLUTE");
}
