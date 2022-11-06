#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

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