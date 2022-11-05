#include "../src/cpu.hpp"
#include "load_in_register.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("LSR", "[BITWISE]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;

	SECTION("LSR") {
		constexpr uint8_t value = 0x02;
		constexpr uint32_t cycles = 2;

		cpu.A = value;
		mem[0XFFFC] = LSR;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, false, flags, cpu.flags);
		test_execution(value >> 1, cpu.A, cycles, actual_cycles);
	}
	SECTION("LSR ZERO PAGE") {
		constexpr uint8_t value = 0x05;
		constexpr uint32_t cycles = 5;
		constexpr uint8_t address = 0xAA;

		mem[0xFFFC] = LSR_ZERO_PAGE;
		mem[0xFFFD] = address;
		mem[address] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, true, flags, cpu.flags);
		test_execution(value >> 1, mem[address], cycles, actual_cycles);
	}
	SECTION("LSR ZERO PAGE X") {
		constexpr uint8_t value = 0xAA;
		constexpr uint8_t value_x = 0x04;
		constexpr uint32_t cycles = 6;

		cpu.X = value_x;
		mem[0xFFFC] = LSR_ZERO_PAGE_X;
		mem[0xFFFD] = 0xAA;
		mem[0xAA + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, false, flags, cpu.flags);
		test_execution(value >> 1, mem[0xAA + value_x], cycles, actual_cycles);
	}
	SECTION("LSR ABSOLUTE") {
		constexpr uint8_t value = 0xAB;
		constexpr uint32_t cycles = 6;

		mem[0xFFFC] = LSR_ABSOLUTE;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, true, flags, cpu.flags);
		test_execution(value >> 1, mem[0x1234], cycles, actual_cycles);
	}
	SECTION("LSR ABSOLUTE X") {
		constexpr uint8_t value = 0x04;
		constexpr uint32_t cycles = 7;
		constexpr uint8_t value_x = 0xAB;

		cpu.X = value_x;
		mem[0xFFFC] = LSR_ABSOLUTE_X;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, false, flags, cpu.flags);
		test_execution(
			value >> 1, mem[0x1234 + value_x], cycles, actual_cycles
		);
	}
}

TEST_CASE("ORA IMMEDIATE", "[ORA]") {
	Memory mem {};
	CPU cpu { mem };

	cpu.A = 0x11;
	test_immediate(cpu, mem, cpu.A, ORA_IMMEDIATE, 0xAA, 0xAA | cpu.A, 2);
}

TEST_CASE("ORA ZERO PAGE", "[ORA]") {
	Memory mem {};
	CPU cpu(mem);

	cpu.A = 0x01;
	test_zero_page(cpu, mem, cpu.A, ORA_ZERO_PAGE, 0x0C, 0x0C | cpu.A, 3);
	test_zero_page_X(cpu, mem, cpu.A, ORA_ZERO_PAGE_X, 0x0D, 0x0D | cpu.A, 4);
}

TEST_CASE("ORA ABSOLUTE", "[ORA]") {
	Memory mem {};
	CPU cpu { mem };

	cpu.A = 0xAB;
	test_absolute(cpu, mem, cpu.A, ORA_ABSOLUTE, 0xE1, 0xE1 | 0xAB, 4);
	cpu.A = 0x12;
	test_absolute_X(
		cpu, mem, cpu.A, ORA_ABSOLUTE_X, 0xA2, 0xA2 | cpu.A, 4, true
	);
	cpu.A = 0x11;
	test_absolute_Y(
		cpu, mem, cpu.A, ORA_ABSOLUTE_Y, 0xDA, 0xDA | cpu.A, 4, true
	);
}

TEST_CASE("ORA INDIRECT") {
	Memory mem {};
	CPU cpu { mem };
	cpu.A = 0xA1;
	test_indirect_X(cpu, mem, cpu.A, ORA_INDIRECT_X, 0xAA, 0xAA | cpu.A, 6);
	cpu.A = 0x41;
	test_indirect_Y(cpu, mem, cpu.A, ORA_INDIRECT_Y, 0xBA, 0xBA | cpu.A, 5);
}

// TODO: refactor and check carry
TEST_CASE("ROL", "[BITWISE]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;

	SECTION("ROL") {
		constexpr uint8_t value = 0x02;
		constexpr uint32_t cycles = 2;

		cpu.A = value;
		mem[0XFFFC] = ROL;

		const auto actual_cycles = cpu.execute();
		test_execution(0xFF & (value << 1), cpu.A, cycles, actual_cycles);
		test_ZNC_flags(false, false, false, flags, cpu.flags);
	}
	SECTION("ROL ZERO PAGE") {
		constexpr uint8_t value = 0xAB;
		constexpr uint32_t cycles = 5;

		mem[0xFFFC] = ROL_ZERO_PAGE;
		mem[0xFFFD] = 0xAA;
		mem[0xAA] = value;

		const auto actual_cycles = cpu.execute();
		test_execution(0xFF & (value << 1), mem[0xAA], cycles, actual_cycles);
		test_ZNC_flags(false, false, true, flags, cpu.flags);
	}
	SECTION("ROL ZERO PAGE X") {
		constexpr uint8_t value = 0x0A;
		constexpr uint8_t value_x = 0x04;
		constexpr uint32_t cycles = 6;

		cpu.X = value_x;
		mem[0xFFFC] = ROL_ZERO_PAGE_X;
		mem[0xFFFD] = 0xAA;

		mem[0xAA + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_execution(
			0xFF & (value << 1), mem[0xAA + value_x], cycles, actual_cycles
		);
		test_ZNC_flags(false, false, false, flags, cpu.flags);
	}
	SECTION("ROL ABSOLUTE") {
		constexpr uint8_t value = 0xCD;
		constexpr uint32_t cycles = 6;

		mem[0xFFFC] = ROL_ABSOLUTE;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, true, true, flags, cpu.flags);
		test_execution(0xFF & (value << 1), mem[0x1234], cycles, actual_cycles);
	}
	SECTION("ROL ABSOLUTE X") {
		constexpr uint8_t value = 0x04;
		constexpr uint32_t cycles = 7;
		constexpr uint8_t value_x = 0xAB;

		cpu.X = value_x;
		mem[0xFFFC] = ROL_ABSOLUTE_X;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, false, flags, cpu.flags);
		test_execution(
			0xFF & (value << 1), mem[0x1234 + value_x], cycles, actual_cycles
		);
	}
}

TEST_CASE("ROR", "[BITWISE]") {
	Memory mem {};
	CPU cpu(mem);
	const auto flags = cpu.flags;

	SECTION("ROR") {
		constexpr uint8_t value = 0x02;
		constexpr uint32_t cycles = 2;

		cpu.A = value;
		mem[0XFFFC] = ROR;

		const auto actual_cycles = cpu.execute();
		test_execution(value >> 1, cpu.A, cycles, actual_cycles);
		test_ZNC_flags(false, false, false, flags, cpu.flags);
	}
	SECTION("ROR ZERO PAGE") {
		constexpr uint8_t value = 0xAB;
		constexpr uint32_t cycles = 5;

		mem[0xFFFC] = ROR_ZERO_PAGE;
		mem[0xFFFD] = 0xAA;
		mem[0xAA] = value;

		const auto actual_cycles = cpu.execute();
		test_execution(value >> 1, mem[0xAA], cycles, actual_cycles);
		test_ZNC_flags(false, false, true, flags, cpu.flags);
	}
	SECTION("ROR ZERO PAGE X") {
		constexpr uint8_t value = 0x0A;
		constexpr uint8_t value_x = 0x04;
		constexpr uint32_t cycles = 6;

		cpu.X = value_x;
		mem[0xFFFC] = ROR_ZERO_PAGE_X;
		mem[0xFFFD] = 0xAA;
		mem[0xAA + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_execution(value >> 1, mem[0xAA + value_x], cycles, actual_cycles);
		test_ZNC_flags(false, false, false, flags, cpu.flags);
	}
	SECTION("ROR ABSOLUTE") {
		constexpr uint8_t value = 0xCD;
		constexpr uint32_t cycles = 6;

		mem[0xFFFC] = ROR_ABSOLUTE;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, true, flags, cpu.flags);
		test_execution(value >> 1, mem[0x1234], cycles, actual_cycles);
	}
	SECTION("ROR ABSOLUTE X") {
		constexpr uint8_t value = 0x04;
		constexpr uint32_t cycles = 7;
		constexpr uint8_t value_x = 0xAB;

		cpu.X = value_x;
		mem[0xFFFC] = ROR_ABSOLUTE_X;
		mem[0xFFFD] = 0x34;
		mem[0xFFFE] = 0x12;
		mem[0x1234 + value_x] = value;

		const auto actual_cycles = cpu.execute();
		test_ZNC_flags(false, false, false, flags, cpu.flags);
		test_execution(
			value >> 1, mem[0x1234 + value_x], cycles, actual_cycles
		);
	}
}
