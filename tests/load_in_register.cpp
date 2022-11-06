#include "load_in_register.hpp"

#include "util.hpp"

#include <catch2/catch.hpp>

void test_accumulator(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	cpu.A = start_value;
	cpu.mem[0xFFFC] = opcode;

	const auto actual_cycles = cpu.execute();
	test_execution(expected_value, *reg, expected_cycles, actual_cycles);
}

void test_immediate(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("IMMEDIATE") {
		cpu.mem[0xFFFC] = opcode;
		cpu.mem[0xFFFD] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(expected_value, *reg, expected_cycles, actual_cycles);
	}
}

void test_zero_page(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ZERO PAGE") {
		const uint32_t address = 0xAF;
		cpu.mem[0xFFFC] = opcode;
		cpu.mem[0xFFFD] = 0xAF;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
}

void test_zero_page_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	cpu.mem[0xFFFC] = opcode;
	SECTION("ZERO PAGE X NORMAL") {
		constexpr uint8_t value_x = 0x02;
		constexpr uint32_t address = 0xAF + value_x;

		cpu.X = value_x;
		cpu.mem[0xFFFD] = 0xAF;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
	SECTION("ZERO PAGE X WRAP") {
		constexpr uint8_t value_x = 0xFF;
		constexpr uint32_t address = 0xFF & (0x080 + value_x);

		cpu.X = value_x;
		cpu.mem[0xFFFD] = 0x80;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
}

void test_zero_page_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	cpu.mem[0xFFFC] = opcode;
	SECTION("ZERO PAGE Y NORMAL") {
		constexpr uint8_t value_y = 0x02;
		constexpr uint32_t address = 0xAF + value_y;

		cpu.Y = value_y;
		cpu.mem[0xFFFD] = 0xAF;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
	SECTION("ZERO PAGE Y WRAP") {
		constexpr uint8_t value_y = 0xFF;
		constexpr uint32_t address = 0xFF & (0x080 + value_y);

		cpu.Y = value_y;
		cpu.mem[0xFFFD] = 0x80;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
}

void test_absolute(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	SECTION("ABSOLUTE") {
		constexpr uint32_t address = 0x1234;
		cpu.mem[0xFFFC] = opcode;
		cpu.mem[0xFFFD] = 0x34;
		cpu.mem[0xFFFE] = 0x12;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
}

void test_absolute_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read
) {
	cpu.mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE X") {
		constexpr uint8_t value_x = 0x02;
		constexpr uint32_t address = 0x1234 + value_x;

		cpu.X = value_x;
		cpu.mem[0xFFFD] = 0x34;
		cpu.mem[0xFFFE] = 0x12;
		cpu.mem[address] = start_value;
		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
	if (read) {
		SECTION("ABSOLUTE X PAGE CROSSED") {
			constexpr uint8_t value_x = 0xFF;
			constexpr uint32_t address = 0x1234 + value_x;

			cpu.X = value_x;
			cpu.mem[0xFFFD] = 0x34;
			cpu.mem[0xFFFE] = 0x12;
			cpu.mem[address] = start_value;

			const auto actual_cycles = cpu.execute();
			test_execution(
				expected_value,
				reg ? *reg : cpu.mem[address],
				expected_cycles + 1,
				actual_cycles
			);
		}
	}
}

void test_absolute_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read
) {
	cpu.mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE Y NORMAL") {
		constexpr uint8_t value_y = 0x12;
		constexpr uint32_t address = 0x1234 + value_y;

		cpu.Y = value_y;
		cpu.mem[0xFFFD] = 0x34;
		cpu.mem[0xFFFE] = 0x12;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
	if (read) {
		SECTION("ABSOLUTE Y PAGE CROSSED") {
			constexpr uint8_t value_y = 0xFF;
			constexpr uint32_t address = 0x1234 + value_y;
			cpu.Y = value_y;
			cpu.mem[0xFFFD] = 0x34;
			cpu.mem[0xFFFE] = 0x12;
			cpu.mem[address] = start_value;

			const auto actual_cycles = cpu.execute();
			test_execution(
				expected_value,
				reg ? *reg : cpu.mem[address],
				expected_cycles + 1,
				actual_cycles
			);
		}
	}
}

void test_indirect_X(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles
) {
	CAPTURE(opcode);
	cpu.mem[0xFFFC] = opcode;

	SECTION("INDIRECT X NORMAL") {
		constexpr uint8_t value_x = 0xAA;
		constexpr uint16_t address = 0xAAFF;
		cpu.X = value_x;

		cpu.mem[0xFFFD] = 0x02;
		cpu.mem[0x02 + value_x] = 0xFF & address;
		cpu.mem[0x03 + value_x] = address >> 8;
		cpu.mem[address] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}
}

void test_indirect_Y(
	CPU &cpu,
	const opcode_type opcode,
	const reg_t *reg,
	const uint8_t start_value,
	const uint8_t expected_value,
	const uint32_t expected_cycles,
	bool read
) {
	cpu.mem[0xFFFC] = opcode;
	SECTION("INDIRECT Y NORMAL") {
		constexpr uint8_t value_y = 0x02;
		constexpr uint16_t address = 0xAAFA;

		cpu.Y = value_y;
		cpu.mem[0xFFFD] = 0x03;
		cpu.mem[0x03] = 0xFF & address;
		cpu.mem[0x04] = address >> 8;
		cpu.mem[address + value_y] = start_value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			expected_value,
			reg ? *reg : cpu.mem[address],
			expected_cycles,
			actual_cycles
		);
	}

	if (read) {
		SECTION("INDIRECT Y PAGE CROSSED") {
			constexpr uint8_t value_y = 0xFF;
			constexpr uint16_t address = 0xAAFA;

			cpu.Y = value_y;
			CAPTURE(hex_to_string(cpu.Y));
			cpu.mem[0xFFFD] = 0x03;
			cpu.mem[0x03] = 0xFF & address;
			cpu.mem[0x04] = address >> 8;
			cpu.mem[address + value_y] = start_value;

			const auto actual_cycles = cpu.execute();
			test_execution(
				expected_value,
				reg ? *reg : cpu.mem[address],
				expected_cycles + 1,
				actual_cycles
			);
		}
	}
}