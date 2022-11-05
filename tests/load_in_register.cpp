#include "load_in_register.hpp"

#include "util.hpp"

#include <catch2/catch.hpp>

void test_immediate(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("IMMEDIATE") {
		mem[0xFFFC] = opcode;
		mem[0xFFFD] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_zero_page(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ZERO PAGE") {
		mem[0xFFFC] = opcode;
		mem[0xFFFD] = 0xAF;
		mem[0xAF] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_zero_page_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ZERO PAGE X NORMAL") {
		mem[0xFFFC] = opcode;
		constexpr uint8_t value_x = 0x02;

		cpu.X = value_x;
		mem[0xFFFD] = 0xAF;
		mem[0xAF + value_x] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
	SECTION("ZERO PAGE X WRAP") {
		mem[0xFFFC] = opcode;
		constexpr uint8_t value_x = 0xFF;

		cpu.X = value_x;
		mem[0xFFFD] = 0x80;
		mem[0xFF & (0x080 + value_x)] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_zero_page_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ZERO PAGE Y NORMAL") {
		mem[0xFFFC] = opcode;
		constexpr uint8_t value_y = 0x02;

		cpu.Y = value_y;
		mem[0xFFFD] = 0xAF;
		mem[0xAF + value_y] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
	SECTION("ZERO PAGE Y WRAP") {
		mem[0xFFFC] = opcode;
		constexpr uint8_t value_y = 0xFF;

		cpu.Y = value_y;
		mem[0xFFFD] = 0x80;
		mem[0xFF & (0x080 + value_y)] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_absolute(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ABSOLUTE") {
		mem[0xFFFC] = opcode;

		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_absolute_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read
) {
	mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE X") {
		constexpr uint8_t value_x = 0x02;

		cpu.X = value_x;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = start_value;
		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
	if (read) {
		SECTION("ABSOLUTE X PAGE CROSSED") {
			constexpr uint8_t value_x = 0xFF;

			cpu.X = value_x;
			mem[0xFFFD] = 0x34;
			mem[0xFFFE] = 0x12;
			mem[0x1234 + value_x] = start_value;

			const auto actual_cycles = cpu.execute();
			test_execution(
				expected_value, reg, expected_cycles + 1, actual_cycles
			);
		}
	}
}

void test_absolute_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read
) {
	mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE Y NORMAL") {
		constexpr uint8_t value_y = 0x12;
		cpu.Y = value_y;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_y] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
	if (read) {
		SECTION("ABSOLUTE Y PAGE CROSSED") {
			constexpr uint8_t value_y = 0xFF;
			cpu.Y = value_y;
			mem[0xFFFD] = 0x34;
			mem[0xFFFE] = 0x12;
			mem[0x1234 + value_y] = start_value;

			const auto actual_cycles = cpu.execute();
			test_execution(
				expected_value, reg, expected_cycles + 1, actual_cycles
			);
		}
	}
}

void test_indirect_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	CAPTURE(opcode);
	mem[0xFFFC] = opcode;

	SECTION("INDIRECT X NORMAL") {
		constexpr uint8_t value_x = 0xAA;
		constexpr uint16_t address = 0xAAFF;
		cpu.X = value_x;

		mem[0xFFFD] = 0x02;
		mem[0x02 + value_x] = 0xFF & address;
		mem[0x03 + value_x] = address >> 8;
		mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}
}

void test_indirect_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const reg_t &reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	mem[0xFFFC] = opcode;
	SECTION("INDIRECT Y NORMAL") {
		constexpr uint8_t value_y = 0x02;
		constexpr uint16_t address = 0xAAFA;

		cpu.Y = value_y;
		mem[0xFFFD] = 0x03;
		mem[0x03] = 0xFF & address;
		mem[0x04] = address >> 8;
		mem[address + value_y] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles, actual_cycles);
	}

	SECTION("INDIRECT Y PAGE CROSSED") {
		constexpr uint8_t value_y = 0xFF;
		constexpr uint16_t address = 0xAAFA;

		cpu.Y = value_y;
		CAPTURE(hex_to_string(cpu.Y));
		mem[0xFFFD] = 0x03;
		mem[0x03] = 0xFF & address;
		mem[0x04] = address >> 8;
		mem[address + value_y] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, reg, expected_cycles + 1, actual_cycles);
	}
}