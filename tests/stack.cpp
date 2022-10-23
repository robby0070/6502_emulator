#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("PHA", "[PUSH STACK]") {
	Memory mem {};
	CPU cpu { mem };
	auto flags = cpu.flags;
	constexpr uint32_t cycles = 3;
	constexpr uint8_t value = 0xAA;

	cpu.A = value;
	mem[0xFFFC] = PHA;

	const auto actual_cycles = cpu.execute();
	test_execution(cpu.A, mem[(cpu.SP + 1) | 0x0100], cycles, actual_cycles);
	test_unchaged_flags(flags, cpu.flags, 0xFF);
}

TEST_CASE("PHP", "[PUSH STACK]") {
	Memory mem {};
	CPU cpu { mem };
	constexpr uint32_t cycles = 3;
	cpu.flags = 0xAB;

	mem[0xFFFC] = PHP;
	const auto actual_cycles = cpu.execute();
	test_execution(
		cpu.flags, mem[(cpu.SP + 1) | 0x0100], cycles, actual_cycles);
}

TEST_CASE("PLA", "[PULL STACK]") {
	Memory mem {};
	CPU cpu { mem };
	const auto flags = cpu.flags;
	constexpr uint32_t cycles = 4;
	constexpr uint8_t value = 0x11;
	cpu.A = value;
	mem[0xFFFC] = PHA;
	cpu.execute();

	cpu.A = 0x00;
	mem[0xFFFD] = PLA;
	const auto actual_cycles = cpu.execute();

	test_execution(value, cpu.A, cycles, actual_cycles);
	test_ZN_flags(cpu.A, flags, cpu.flags);
}

TEST_CASE("PLP", "[PULL STACK]") {
	Memory mem {};
	CPU cpu { mem };
	constexpr uint32_t cycles = 4;
	constexpr uint8_t value = 0x22;

	cpu.flags = value;
	mem[0xFFFC] = PHP;
	cpu.execute();

	cpu.flags = 0x00;
	mem[0xFFFD] = PLP;

	const auto actual_cycles = cpu.execute();
	test_execution(value, cpu.flags, cycles, actual_cycles);
}

TEST_CASE("RTI", "[PULL STACK]") {
	Memory mem {};
	CPU cpu { mem };
	constexpr uint32_t cycles = 6;
	constexpr uint8_t value_flags = 0x11;
	constexpr uint8_t value_PC = 0x22;

	cpu.A = value_PC;
	mem[0xFFFC] = PHA;
	cpu.execute();

	cpu.A = value_flags;
	mem[0xFFFD] = PHA;
	cpu.execute();

	mem[0xFFFE] = RTI;

	const auto actual_cycles = cpu.execute();
	REQUIRE(cpu.PC == value_PC);
	test_execution(value_flags, cpu.flags, cycles, actual_cycles);
}

TEST_CASE("RTS", "[PULL STACK]") {
	Memory mem {};
	CPU cpu { mem };
	constexpr uint32_t cycles = 6;
	constexpr uint8_t value = 0x70;

	cpu.A = value;
	mem[0xFFFC] = PHA;
	cpu.execute();

	mem[0xFFFD] = RTS;

	const auto actual_cycles = cpu.execute();
	test_execution(value - 1, cpu.PC, cycles, actual_cycles);
}