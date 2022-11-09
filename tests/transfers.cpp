#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

TEST_CASE("TAX") {
	SECTION("TAX IMPLIED") {
		INIT_TEST_ONCE(0xAB, 2)
		cpu.A = value;
		mem[0xFFFC] = TAX;

		const auto actual_cycles = cpu.execute();
		test_execution(value, cpu.X, cycles, actual_cycles);
		test_ZN_flags(value, flags, cpu.flags);
	}
}

TEST_CASE("TAY") {
	SECTION("TAY IMPLIED") {
		INIT_TEST_ONCE(0xA2, 2)
		cpu.A = value;
		mem[0xFFFC] = TAY;

		const auto actual_cycles = cpu.execute();
		test_execution(value, cpu.Y, cycles, actual_cycles);
		test_ZN_flags(value, flags, cpu.flags);
	}
}

TEST_CASE("TXA") {
	SECTION("TXA IMPLIED") {
		INIT_TEST_ONCE(0x01, 2)
		cpu.X = value;
		mem[0xFFFC] = TXA;

		const auto actual_cycles = cpu.execute();
		test_execution(value, cpu.A, cycles, actual_cycles);
		test_ZN_flags(value, flags, cpu.flags);
	}
}

TEST_CASE("TYA") {
	SECTION("TYA IMPLIED") {
		INIT_TEST_ONCE(0x05, 2)
		cpu.Y = value;
		mem[0xFFFC] = TYA;

		const auto actual_cycles = cpu.execute();
		test_execution(value, cpu.A, cycles, actual_cycles);
		test_ZN_flags(value, flags, cpu.flags);
	}
}