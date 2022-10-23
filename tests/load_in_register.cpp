#include "load_in_register.hpp"

#include "util.hpp"

#include <catch2/catch.hpp>

uint32_t test(CPU &cpu, Memory &mem, const opcode_type opcode) {
	switch (opcode & 0b11) {
		case 0b01:
			switch ((opcode >> 2) & 0b11) {}
			break;
		case 0b10: break;
		case 0b00: break;
	}
	return {};
}

uint32_t test_immediate(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	mem[0xFFFD] = value;

	return cpu.execute();
}

uint32_t test_zero_page(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	mem[0xFFFD] = 0xAF;
	mem[0xAF] = value;

	return cpu.execute();
}

uint32_t test_zero_page_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	constexpr uint8_t value_x = 0x02;

	cpu.X = value_x;
	mem[0xFFFD] = 0xAF;
	mem[0xAF + value_x] = value;

	return cpu.execute();
}

uint32_t test_zero_page_X_wrap(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	constexpr uint8_t value_x = 0xFF;

	cpu.X = value_x;
	mem[0xFFFD] = 0x80;
	mem[0xFF & (0x080 + value_x)] = value;

	return cpu.execute();
}

uint32_t test_zero_page_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	constexpr uint8_t value_y = 0x02;

	cpu.Y = value_y;
	mem[0xFFFD] = 0xAF;
	mem[0xAF + value_y] = value;

	return cpu.execute();
}

uint32_t test_zero_page_Y_wrap(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	constexpr uint8_t value_y = 0xFF;

	cpu.Y = value_y;
	mem[0xFFFD] = 0x80;
	mem[0xFF & (0x080 + value_y)] = value;

	return cpu.execute();
}

uint32_t test_absolute(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;

	mem[0xFFFD] = 0x34;
	mem[0xFFFE] = 0x12;
	mem[0x1234] = value;

	return cpu.execute();
}

std::pair<uint32_t, uint32_t> test_absolute_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE X") {
		constexpr uint32_t cycles = 4;
		constexpr uint8_t value_x = 0x02;

		cpu.X = value_x;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = value;
		const auto actual_cycles = cpu.execute();
		test_execution(value, cpu.)
	}

	SECTION("ABSOLUTE X PAGE CROSSED") {
		constexpr uint32_t cycles = 5;
		constexpr uint8_t value_x = 0xFF;

		cpu.X = value_x;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = value;

		return cpu.execute();
	}
}

std::pair<uint32_t, uint32_t> test_absolute_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value const uint8_t value_crossed
) {
	mem[0xFFFC] = opcode;

	SECTION("ABSOLUTE Y") {
		constexpr uint32_t cycles = 4;
		constexpr uint8_t value_y = 0x12;
		cpu.Y = value_y;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_y] = value;

		return cpu.execute();
	}

	SECTION("ABSOLUTE Y PAGE CROSSED") {
		constexpr uint32_t cycles = 5;
		constexpr uint8_t value_y = 0xFF;
		cpu.Y = value_y;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_y] = value;

		return cpu.execute();
	}
}

uint32_t test_indirect_X(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;

	SECTION("(INDIRECT,X)") {
		constexpr uint32_t cycles = 6;
		constexpr uint8_t value_x = 0xAA;
		constexpr uint16_t address = 0xAAFF;
		cpu.X = value_x;

		mem[0xFFFD] = 0x02;
		mem[0x02 + value_x] = 0xFF & address;
		mem[0x03 + value_x] = address >> 8;
		mem[address] = value;

		return cpu.execute();
	}
	SECTION("(INDIRECT,X) WRAP") {
		constexpr uint32_t cycles = 6;
		constexpr uint8_t value_x = 0xFF;
		constexpr uint16_t address = 0xAAFF;
		cpu.X = value_x;

		mem[0xFFFD] = 0x02;
		mem[0xFF & (0x02 + value_x)] = 0xFF & address;
		mem[0xFF & (0x03 + value_x)] = address >> 8;
		mem[address] = value;

		return cpu.execute();
	}
}

std::pair<uint32_t, uint32_t> test_indirect_Y(
	CPU &cpu,
	Memory &mem,
	const opcode_type opcode,
	const uint8_t value
) {
	mem[0xFFFC] = opcode;
	SECTION("(INDIRECT), Y") {
		constexpr uint32_t cycles = 5;
		constexpr uint8_t value_y = 0x02;
		constexpr uint16_t address = 0xAAFA;

		cpu.Y = value_y;
		mem[0xFFFD] = 0x03;
		mem[0x03] = 0xFF & address;
		mem[0x04] = address >> 8;
		mem[address + value_y] = value;

		return cpu.execute();
	}

	SECTION("(INDIRECT), Y PAGE CROSSED") {
		constexpr uint32_t cycles = 6;
		constexpr uint8_t value_y = 0xFF;
		constexpr uint16_t address = 0xAAFA;

		cpu.Y = value_y;
		mem[0xFFFD] = 0x03;
		mem[0x03] = 0xFF & address;
		mem[0x04] = address >> 8;
		mem[address + value_y] = value;

		return cpu.execute();
	}
}