#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

#define TEST_AND(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value &cpu.A, cycles); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

#define TEST_AND_PAGE_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value &cpu.A, cycles, true); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

TEST_CASE("AND") {
	TEST_AND(0x19, 2, test_immediate, AND_IMMEDIATE, "AND IMMEDIATE")
	TEST_AND(0x71, 3, test_zero_page, AND_ZERO_PAGE, "AND ZERO PAGE");
	TEST_AND(0x73, 4, test_zero_page_X, AND_ZERO_PAGE_X, "AND ZERO PAGE X");
	TEST_AND(0x92, 4, test_absolute, AND_ABSOLUTE, "AND ABSOLUTE");
	TEST_AND_PAGE_CROSS(
		0xFB, 4, test_absolute_X, AND_ABSOLUTE_X, "AND ABSOLUTE X"
	);
	TEST_AND_PAGE_CROSS(
		0x16, 4, test_absolute_Y, AND_ABSOLUTE_Y, "AND ABSOLUTE Y"
	);
	TEST_AND(0XB8, 6, test_indirect_X, AND_INDIRECT_X, "AND INDIRECT X")
	TEST_AND_PAGE_CROSS(
		0X29, 5, test_indirect_Y, AND_INDIRECT_Y, "AND INDIRECT Y"
	);
}

#define TEST_EOR(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value ^ cpu.A, cycles); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

#define TEST_EOR_PAGE_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value ^ cpu.A, cycles, true); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

TEST_CASE("EOR") {
	TEST_EOR(0x19, 2, test_immediate, EOR_IMMEDIATE, "EOR IMMEDIATE")
	TEST_EOR(0x71, 3, test_zero_page, EOR_ZERO_PAGE, "EOR ZERO PAGE");
	TEST_EOR(0x73, 4, test_zero_page_X, EOR_ZERO_PAGE_X, "EOR ZERO PAGE X");
	TEST_EOR(0x92, 4, test_absolute, EOR_ABSOLUTE, "EOR ABSOLUTE");
	TEST_EOR_PAGE_CROSS(
		0xFB, 4, test_absolute_X, EOR_ABSOLUTE_X, "EOR ABSOLUTE X"
	);
	TEST_EOR_PAGE_CROSS(
		0x16, 4, test_absolute_Y, EOR_ABSOLUTE_Y, "EOR ABSOLUTE Y"
	);
	TEST_EOR(0XB8, 6, test_indirect_X, EOR_INDIRECT_X, "EOR INDIRECT X")
	TEST_EOR_PAGE_CROSS(
		0X29, 5, test_indirect_Y, EOR_INDIRECT_Y, "EOR INDIRECT Y"
	);
}

#define TEST_ORA(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value | cpu.A, cycles); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

#define TEST_ORA_PAGE_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST; \
		function(cpu, opcode, &cpu.A, value, value | cpu.A, cycles, true); \
		test_ZN_flags(cpu.A, flags, cpu.flags); \
	}

TEST_CASE("ORA") {
	TEST_ORA(0x19, 2, test_immediate, ORA_IMMEDIATE, "ORA IMMEDIATE")
	TEST_ORA(0x71, 3, test_zero_page, ORA_ZERO_PAGE, "ORA ZERO PAGE");
	TEST_ORA(0x73, 4, test_zero_page_X, ORA_ZERO_PAGE_X, "ORA ZERO PAGE X");
	TEST_ORA(0x92, 4, test_absolute, ORA_ABSOLUTE, "ORA ABSOLUTE");
	TEST_ORA_PAGE_CROSS(
		0xFB, 4, test_absolute_X, ORA_ABSOLUTE_X, "ORA ABSOLUTE X"
	);
	TEST_ORA_PAGE_CROSS(
		0x16, 4, test_absolute_Y, ORA_ABSOLUTE_Y, "ORA ABSOLUTE Y"
	);
	TEST_ORA(0XB8, 6, test_indirect_X, ORA_INDIRECT_X, "ORA INDIRECT X")
	TEST_ORA_PAGE_CROSS(
		0X29, 5, test_indirect_Y, ORA_INDIRECT_Y, "ORA INDIRECT Y"
	);
}

TEST_CASE("BIT") {
	SECTION("BIT ZERO PAGE") {
		INIT_TEST;
		cpu.A = 0xA2;
		test_zero_page(cpu, BIT_ZERO_PAGE, &cpu.flags, 0xB8, 0b10000010, 3);
		test_unchaged_flags(flags, cpu.flags, 0b0011101);
	}

	SECTION("BIT ABSOLUTE") {
		INIT_TEST;
		cpu.A = 0b01001100;
		test_zero_page(
			cpu, BIT_ABSOLUTE, &cpu.flags, 0b10110011, 0b10000000, 4
		);
		test_unchaged_flags(flags, cpu.flags, 0b0011101);
	}
}