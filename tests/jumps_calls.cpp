#include "../src/cpu.hpp"
#include "util.hpp"

#include <catch2/catch.hpp>

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