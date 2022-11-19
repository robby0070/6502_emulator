#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

#define TEST_ADC(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		const uint16_t new_value = cpu.A + value + (cpu.flags & CPU::C_M); \
		const auto carry = new_value > 0xFF; \
		function(cpu, opcode, &cpu.A, value, new_value, cycles); \
		test_ZNC_flags(flags, cpu.flags, cpu.A, carry); \
	}

#define TEST_ADC_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		const uint16_t new_value = cpu.A + value + (cpu.flags & CPU::C_M); \
		const auto carry = new_value > 0xFF; \
		function(cpu, opcode, &cpu.A, value, new_value, cycles, true); \
		test_ZNC_flags(flags, cpu.flags, cpu.A, carry); \
	}

TEST_CASE("ADC") {
	TEST_ADC(0xDE, 2, test_immediate, ADC_IMMEDIATE, "ADC IMMEDIATE");
	TEST_ADC(0xAF, 3, test_zero_page, ADC_ZERO_PAGE, "ADC ZERO PAGE");
	TEST_ADC(0x0E, 4, test_zero_page_X, ADC_ZERO_PAGE_X, "ADC ZERO PAGE X");
	TEST_ADC(0xFF, 4, test_absolute, ADC_ABSOLUTE, "ADC ABSOLUTE");
	TEST_ADC_CROSS(0x01, 4, test_absolute_X, ADC_ABSOLUTE_X, "ADC ABSOLUTE X");
	TEST_ADC_CROSS(0x04, 4, test_absolute_Y, ADC_ABSOLUTE_Y, "ADC ABSOLUTE Y");
	TEST_ADC(0x07, 6, test_indirect_X, ADC_INDIRECT_X, "ADC INDIRECT X");
	TEST_ADC_CROSS(0x07, 5, test_indirect_Y, ADC_INDIRECT_Y, "ADC INDIRECT Y");
}

#define TEST_SBC(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		const uint16_t new_value = \
			cpu.A - value - (1 - (cpu.flags & CPU::C_M)); \
		const auto carry = new_value > 0xFF; \
		function(cpu, opcode, &cpu.A, value, new_value, cycles); \
		test_ZNC_flags(flags, cpu.flags, cpu.A, carry); \
	}

#define TEST_SBC_CROSS(value, cycles, function, opcode, section_name) \
	SECTION(section_name) { \
		INIT_TEST \
		const uint16_t new_value = \
			cpu.A - value - (1 - (cpu.flags & CPU::C_M)); \
		const auto carry = new_value > 0xFF; \
		function(cpu, opcode, &cpu.A, value, new_value, cycles, true); \
		test_ZNC_flags(flags, cpu.flags, cpu.A, carry); \
	}

TEST_CASE("SBC") {
	TEST_SBC(0xDE, 2, test_immediate, SBC_IMMEDIATE, "SBC IMMEDIATE");
	TEST_SBC(0xAF, 3, test_zero_page, SBC_ZERO_PAGE, "SBC ZERO PAGE");
	TEST_SBC(0x0E, 4, test_zero_page_X, SBC_ZERO_PAGE_X, "SBC ZERO PAGE X");
	TEST_SBC(0xFF, 4, test_absolute, SBC_ABSOLUTE, "SBC ABSOLUTE");
	TEST_SBC_CROSS(0x01, 4, test_absolute_X, SBC_ABSOLUTE_X, "SBC ABSOLUTE X");
	TEST_SBC_CROSS(0x04, 4, test_absolute_Y, SBC_ABSOLUTE_Y, "SBC ABSOLUTE Y");
	TEST_SBC(0x07, 6, test_indirect_X, SBC_INDIRECT_X, "SBC INDIRECT X");
	TEST_SBC_CROSS(0x07, 5, test_indirect_Y, SBC_INDIRECT_Y, "SBC INDIRECT Y");
}
