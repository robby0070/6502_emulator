#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("PHA") {
	SECTION("PHA IMPLIED") {
		INIT_TEST_ONCE(0xAA, 3)
		cpu.A = value;
		mem[0xFFFC] = PHA;

		const auto actual_cycles = cpu.execute();
		test_execution(
			cpu.A, mem[(cpu.SP + 1) | 0x0100], cycles, actual_cycles
		);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
	}
}

TEST_CASE("PHP") {
	SECTION("PHP IMPLIED") {
		Memory mem {};
		CPU cpu { mem };
		cpu.flags = 0xAB;
		const auto flags = cpu.flags;
		mem[0xFFFC] = PHP;

		const auto actual_cycles = cpu.execute();
		test_execution(cpu.flags, mem[(cpu.SP + 1) | 0x0100], 3, actual_cycles);
		test_unchaged_flags(flags, cpu.flags, 0xFF);
	}
}

TEST_CASE("PLA") {
	SECTION("PLA IMPLIED") {
		INIT_TEST_ONCE(0x11, 4);
		cpu.A = value;
		mem[0xFFFC] = PHA;
		cpu.execute();

		cpu.A = 0x00;
		mem[0xFFFD] = PLA;
		const auto actual_cycles = cpu.execute();

		test_execution(value, cpu.A, cycles, actual_cycles);
		test_ZN_flags(cpu.A, flags, cpu.flags);
	}
}

TEST_CASE("PLP") {
	SECTION("PLP IMPLIED") {
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
}

TEST_CASE("RTI") {
	SECTION("RTI IMPLIED") {
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
}

TEST_CASE("RTS", "[PULL STACK]") {
	SECTION("RTS IMPLIED") {
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
}